#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

/*Имеется клеточное поле размера n × m, в некоторых позициях которого расставлены k чёрных фигур. Необходимо расставить минимальное число белых слонов, чтобы пробивались все свободные позиции.*/

struct v{
    int num;
    int count=0;
    int i;
    int j;
    v(int n,int c,int i1,int j1):num(n),count(c),i(i1),j(j1){};
};
std::vector<std::vector<int>> res;
int min=INT32_MAX;
int eleph=0;
std::vector<int>p;
int counter,x;
int visit=0;

void  Find(std::vector<std::vector<v>> d,v ver,int eleph,int counter){
    if(eleph>min)
        return;
    int j=ver.j;
    int i=ver.i;
    eleph++;
    int sum=0;
    // если наткнулись на черную фигуру
    if( d[i][j].count==-1)
        return;
     // если не посещена и неиспользована
    if(d[i][j].count!=3){
        counter++;
        sum+=1;
    }
    //омечаю как использованную
    d[i][j].count=5;
    //ход коня
    int line=i;
    int colum=j;
    while(colum>=0 && line>=0 ){
        if( d[line][colum].count==-1)
            break;
        if(d[line][colum].count!=3 && d[line][colum].count!=5) {
            d[line][colum].count = 3;
            counter++;
            sum+=1;
        }
        line--;
     colum--;
    }

    line=i;
    colum=j;
    while((colum<d[0].size() && line>=0)){
        if( d[line][colum].count==-1)
            break;
        if(d[line][colum].count!=3 && d[line][colum].count!=5 ) {
            d[line][colum].count = 3;
            counter++;
            sum+=1;
        }
        line--;
        colum++;
    }
    line=i;
    colum=j;
    while((colum<d[0].size() && line<d.size()) ){
        if( d[line][colum].count==-1)
            break;
        if(d[line][colum].count!=3 &&  d[line][colum].count!=5 ) {
            d[line][colum].count = 3;
            counter++;
            sum+=1;
        }
        line++;
        colum++;
    }
    line=i;
    colum=j;
    while((colum>=0 && line<d.size())  ){
        if( d[line][colum].count==-1) {
            break;
        }
        if(d[line][colum].count!=3 && d[line][colum].count!=5 ) {
            d[line][colum].count = 3;
             counter++;
            sum+=1;
        }
        line++;
        colum--;
    }

    if(sum>0)
        p.push_back(ver.num);
    else return;

    if(counter==d.size()*d[0].size())
    {
        if(min>eleph) {
            min = eleph;
            res.clear();
            res.push_back(p);
        }
        else if(min==eleph){
            res.push_back(p);
        }
        p.pop_back();
        return;
    }
    for(int s=j;s<d[i].size();s++) {
        if (d[i][s].count != -1 && d[i][s].count!=5 ) {
            Find(d, d[i][s], eleph, counter);
        }
    }
    for(int k=i+1;k<d.size();k++){
        for(int s=0;s<d[k].size();s++) {
            if (d[k][s].count != -1 && d[k][s].count!=5 ) {
                Find(d, d[k][s], eleph, counter);
            }
        }
    }
    p.pop_back();
}

void BFS(std::vector<std::vector<v>> d,std::vector<std::vector<bool>> &vis){
    std::queue<v> q;
    bool f=0;
    // запушить 1 клетку
    for(int i=0;i<d.size();i++) {
        for (int j = 0; j < d[0].size(); j++)
            if (!vis[i][j] && d[i][j].count != -1) {
                q.push(d[i][j]);
                d[i][j].count=100;
                f = 1;
                break;
            }
        if(f)
            break;
    }
    //поиск в ширину
    while (!q.empty()) {
        v cur = q.front();
        q.pop();
        int ix=cur.i,jx=cur.j;
        if(  d[ix][jx].count!=-1)
        {
            if (ix + 1 < d.size() && jx + 1 < d[0].size() && d[ix+1][jx+1].count!=-1 && d[ix+1][jx+1].count!=100 && !vis[ix+1][jx+1]){
                q.push(d[ix+1][jx+1]);
                d[ix+1][jx+1].count=100;
            }
            if (ix - 1 >=0  && jx + 1 < d[0].size() &&  d[ix-1][jx+1].count!=-1 && d[ix-1][jx+1].count!=100 && !vis[ix-1][jx+1] ){
                q.push(d[ix-1][jx+1]);
                d[ix-1][jx+1].count=100;
            }
            if (ix + 1 < d.size() && jx -1 >= 0 && d[ix+1][jx-1].count!=-1 && d[ix+1][jx-1].count!=100 &&  !vis[ix+1][jx-1]){
                q.push(d[ix+1][jx-1]);
                d[ix+1][jx-1].count=100;
            }
            if (ix -1 >=0 && jx-1 >= 0 && d[ix-1][jx-1].count!=-1 && d[ix-1][jx-1].count!=100  && !vis[ix-1][jx-1]){
                q.push(d[ix-1][jx-1]);
                d[ix-1][jx-1].count=100;
            }
        }
        vis[ix][jx]= true;
        visit++;
    }
    int s=0;
    for(int i=0;i<d.size();i++){
        for(int j=0;j<d[0].size();j++)
            if(d[i][j].count!=100 && d[i][j].count!=-1) {
                d[i][j].count = -1;
                s++;
            }

    }
    int end=d.size()*d[0].size()-s-x;
    for(int i=0;i<d.size();i++) {
        for(int j=0;j<d[i].size();j++) {
            if(end<=0)
                break;
            eleph=0;
            counter=x+s;
            if (d[i][j].count != -1 ) {
                end--;
                Find(d, d[i][j], eleph, counter);
            }
        }
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("input.txt");
    std::ofstream  out("output.txt");
    int n,m;
    in>>n>>m>>x;
    if(n*m==x){
        out<<0;
    } else {
        std::vector<std::vector<v>> d(n, std::vector<v>(m, {0, 0, 0, 0}));
        int k = 1;
        for (int i = 0; i < d.size(); i++) {
            for (int j = 0; j < d[i].size(); j++) {
                d[i][j] = {k, 0, i, j};
                k++;
            }
        }
        int s;
        for (int i = 0; i < x; i++) {
            in >> s;
            int l = std::floor(s / m);
            int j;
            if (s % m == 0) {
                j = m - 1;
                d[l - 1][j].count = -1;
            } else {
                j = s % m - 1;
                d[l][j].count = -1;
            }

        }
        std::vector<std::vector<bool>> vis(d.size(), std::vector<bool>(m));
        visit = x;
        std::vector<std::vector<int>> result;
        while (visit != n * m) {
            min = INT32_MAX;
            BFS(d, vis);
            if (!result.empty()) {
                int size = result.size();
                if (!res.empty()) {
                    for (int i = 0; i < size; i++) {
                        for (int k = 0; k < res.size() ; k++) {
                            auto pusher = result[i];
                            pusher.insert(pusher.end(),res[k].begin(),res[k].end());
                            result.push_back(pusher);
                            s++;
                        }

                    }
                    for (int i=0;i<size;++i) result.erase(result.begin());
                }
            } else {
                for (int i = 0; i < res.size(); i++) {
                    result.push_back(res[i]);
                }
            }

        }

        for (auto&x:result) std::sort(x.begin(),x.end());
        std::sort(result.begin(),result.end());

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[i].size(); ++j) {
                out << result[i][j] << " ";
            }
            out << "\n";
        }
        out << result.size();
    }
    return 0;
}
