#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <climits>
#include <cmath>

/*План города представляет собой множество перекрёстков, которые соединены дорогами (движение по дороге возможно в обоих направлениях). Перекрёстки обозначаются точками на плоскости с координатами (x1, y1), (x2, y2), …, (xn, yn), а дорогам соответствуют пары { i, j }, где i и j обозначают номера перекрёстков, которые эта дорога соединяет. Каждая дорогая является прямолинейным отрезком между соответствующими перекрёсткам точками.

Необходимо определить, можно ли проехать от перекрёстка с номером s до перекрёстка с номером f, не делая левых поворотов, т. е. двигаясь только прямо или вправо. Если да, то указать последовательность перекрёстков.

Замечания

    Если координаты стартовой точки (x, y), то направление движения в эту точку происходило из точки с координатами (x, y − 1).
    Разворачиваться на 180∘ в точке запрещено.
    Дороги пересекаются не обязательно под прямым углом. Например, некоторая дорога может соединять перекрёстки с координатами (1, 0) и (2, 2), а другая — перекрёстки с координатами (1, 0) и (1, 1). 
*/

struct CrossRoad {
    long long x;
    long long y;
    int num;
    CrossRoad *pred = nullptr;
    CrossRoad *next = nullptr;

    CrossRoad(long long x1, long long y1, long long num, CrossRoad *pred1, CrossRoad *next1) : x(x1), y(y1), num(num), pred(pred1),
                                                                             next(next1) {};
};

struct Road {
    CrossRoad *first;
    CrossRoad *second;

    Road(CrossRoad *f, CrossRoad *s) : first(f), second(s) {};
};


bool Visit(std::vector<std::vector<Road *>> &c, std::vector<std::vector<int>> &visit, CrossRoad *cur_next) {
    int count = 0;
    for (int i = 1; i < c[cur_next->num].size(); i++) {
        for (int j = 1; j < visit[cur_next->num].size(); j++)
            if (c[cur_next->num][i]->second->num == visit[cur_next->num][j])
                count++;
    }

    if (count == c[cur_next->num].size())
        return true;
    return false;
}
 bool func(long long x1, long long  y1, long long x2, long long y2,long long x3, long long y3){
    long long k;
     long long b;
    if(x1!=x2) {
        k=(y1 - y2) / (x1 - x2);
        b= y1-k*x1;
    }
     if(x1==x2 && y2<y1){
         if(x3<=x2) {
             if(x3==x2 && y3<y2)
             return true;
             if(x3==x2 && y3>y2)
                 return false;
             return true;
         }
         else return false;
     }
     if(x1==x2 && y2>y1){
         if(x3>=x2 ) {
             if(x3==x2 && y3>y2)
             return true;
             if(x3==x2 && y3<y2)
                 return false;
             return true;
         }
         else return false;
     }
     if(y1==y2 && x2<x1){
         if(y3>=y2){
             if(y3==y2 && x3>x2) return false;
             return true;
         }
         else return false;
     }
     if(y1==y2 && x2>x1){
         if(y3<=y2) {
             if(y3==y2 && x3<x2) return false;
             return true;
         }
         else return false;
     }

  if(x2<x1){
      if(y3>=(k*x3+b)) {
          if(y3==(k*x3+b) && x3<x2) return true;
          if(y3==(k*x3+b) && x3>x2) return false;
          return true;
      }
      else return false;
  }
  if(x2>x1){
      if(y3<=(k*x3+b)) {
          if(y3==(k*x3+b) && x3>x2) return true;
          if(y3==(k*x3+b) && x3<x2) return false;
          return true;
      }
      else return false;
  }


}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("input.txt");
    int n, m, i1, j2;
    std::ofstream out("output.txt");
    in >> n >> m;
    std::vector<std::vector<Road *>> cr(n + 1);
    long long x1, y1, x2, y2;
    for (int i = 0; i < m; i++) {
        in >> x1 >> y1 >> x2 >> y2 >> i1 >> j2;
        cr[i1].push_back(
                new Road(new CrossRoad(x1, y1, i1, nullptr, nullptr), new CrossRoad(x2, y2, j2, nullptr, nullptr)));
        cr[j2].push_back(
                new Road(new CrossRoad(x2, y2, j2, nullptr, nullptr), new CrossRoad(x1, y1, i1, nullptr, nullptr)));
    }
    std::vector<std::vector<int>> visit(n + 1);
    int start, end;
    in >> start >> end;
    std::list<std::pair<std::pair<int,int>, CrossRoad *>> st;
    std::vector<std::vector<CrossRoad *>> result(n + 1);
    CrossRoad *cur;
    st.push_back(std::make_pair(std::make_pair(cr[start][0]->first->x,cr[start][0]->first->y-1), cr[start][0]->first));
    bool f = false;
    CrossRoad *res;
    while (!st.empty()) {
        if (st.front().second->num == end) {
            res = st.front().second;
            f = true;
            result[st.front().second->num].push_back(res);
            break;
        }
        cur = st.front().second;
        long long xx=st.front().first.first,yy=st.front().first.second;
        st.pop_front();
        for (int i = 0; i < cr[cur->num].size(); i++) {
            if (cur->pred != NULL && cur->pred->num == cr[cur->num][i]->second->num) continue;
            if (func(xx,yy,cur->x,cur->y,cr[cur->num][i]->second->x,cr[cur->num][i]->second->y) &&
                !Visit(cr, visit, cur)) {
                st.push_back(std::make_pair(std::make_pair(cur->x,cur->y), cr[cur->num][i]->second));
                cr[cur->num][i]->second->pred = cr[cur->num][i]->first;
                cur->next = cr[cur->num][i]->second;
                CrossRoad *a = new CrossRoad(cur->x, cur->y, cur->num, cur->pred, cur->next);
                visit[cr[cur->num][i]->second->num].push_back(cur->num);
                result[cur->num].push_back(a);
            }
        }
    }

    if (f) {
        out << "Yes\n";
        std::string s = " ";
        s += std::to_string(res->num)+" ";
        int pred, next;
        while (res->pred != nullptr) {
            pred = res->pred->num;
            for (int i = 0; i < result[pred].size(); i++)
                if (result[pred][i]->next->num == res->num) {
                    s += std::to_string(res->pred->num)+" ";
                    res = result[res->pred->num][i];
                    break;;
                }
        }
        const char ss=' ';
        std::reverse(s.begin(), s.end());
        for (int i = 1; i < s.size(); i++)
            if(i+1!=s.length() && s[i]!=ss && s[i+1]!=ss) {
                out << s[i + 1] << s[i];
                i++;
            }
        else
            out  << s[i];
    } else {
        out << "No";
    }
    return 0;
}
