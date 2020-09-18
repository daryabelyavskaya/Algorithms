#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <set>

/*В городе имеется n автобусных остановок, обозначенных числами из множества N = { 1, 2, …, n }. Имеется r автобусных маршрутов, заданных последовательностями соседних остановок при движении автобуса в одном направлении:
M1 = (i1, 1, i1, 2, …, i1, m1), 
M2 = (i2, 1, i2, 2, …, i2, m2), 
…
Mr = (ir, 1, ir, 2, …, ir, mr),
где ij, k — натуральные числа. Число пунктов в каждом маршруте не превосходит 1000.

Внимание! Маршрут может через некоторую остановку проходить несколько раз:
1 → 2 → 3 → 4 → 5 → 6 → 3 → 7 → 8.
Тем не менее, общее число вхождений каждой остановки во все маршруты не превосходит 10.

Необходимо написать программу, которая по заданным номерам остановок i и j определяет наиболее быстрый способ перемещения пассажира из остановки i в остановку j с использованием имеющихся маршрутов автобусов при условии, что время движения между соседними остановками у всех маршрутов одинаково и в 3 раза меньше времени изменения маршрута (выход из автобуса также считается изменением маршрута). Известно, что автобусы могут двигаться в обоих направлениях.

Формат входных данных
В первой строке через пробел записаны число n остановок и число r автобусных маршрутов (1 ≤ n ≤ 1 000 000, 0 ≤ r ≤ 1000). Во второй строке также через пробел записаны номера конечной и начальной остановок. Далее в каждой из последующих r строк описывается один маршрут: сначала идёт число остановок, а затем через пробел номера остановок в порядке следования.
В первой строке через пробел записаны число n остановок и число r автобусных маршрутов (1 ≤ n ≤ 1 000 000, 0 ≤ r ≤ 1000). Во второй строке также через пробел записаны номера конечной и начальной остановок. Далее в каждой из последующих r строк описывается один маршрут: сначала идёт число остановок, а затем через пробел номера остановок в порядке следования.

Формат выходных данных
Если маршрута между заданными остановками не существует, то выведите одну строку NoWay.

В случае существования маршрута между заданными остановками, в первой строке выводите минимальное время, за которое можно проехать от остановки i к остановке j. В последующие строках выведите информацию о способе самого быстрого проезда от i к j путём перечисления остановок и автобусов, на которых осуществлялся выезд из них: StopNo, номер остановки, BusNo, номер автобуса, на котором будет осуществляться движение из данной остановки (в каждой строке информация об одной остановке). В последней строке выведите информацию о маршруте, на котором прибыли в j: StopNo, j, BusNo, номер автобуса, на котором прибыли в конечный пункт j.

    Для каждой остановки в маршруте, за исключением конечной, указывается номер автобуса, на котором будет осуществляться движение из неё; для конечной остановки указывается номер автобуса, на котором мы в неё приехали.
    Если начальная остановка, совпадает с конечной, то выдаётся только минимальная стоимость маршрута (0). */

struct BusStop {
    int number;
    int routNum;
    long long time;
    int index;
    BusStop* pred= nullptr;
    int predInRoute=0;
    int nextInRoute=0;
    BusStop(int n,int r,int i,int p,int nex,long long time):number(n),routNum(r),index(i),predInRoute(p),nextInRoute(nex),time(time) {};
};

int main() {
    std::ifstream in("in.txt");
    const long long INF = LONG_LONG_MAX;
    int countOfBusStop,routCount,start,end;
    in>>countOfBusStop>>routCount>> end>>start;
    std::ofstream fout("out.txt");
    if(start==end)
        fout<<'0';
    else {
        int k, k1, k2;
        std::vector<int> p;
        //список смежности для остановок
        std::vector<std::vector<std::pair<int, BusStop *>>> stops;
        std::vector<std::set<int>>  ins(countOfBusStop);
        std::priority_queue<std::pair<int, BusStop *>> path;
        std::ios_base::sync_with_stdio(false);
        for (int i = 0; i < routCount; i++) {
            in >> k >> k1;
            stops.emplace_back();
            int pfpf=stops.size();
            BusStop *x = new BusStop(k1-1,i+1,pfpf-1,-1,0,INF);
            ins[k1-1].insert(x->index);
            stops[pfpf-1].push_back(std::make_pair(0,x));
            if (k1 == start) {
                x->time=0;
                path.push(std::make_pair(0, x));
                p.push_back(x->index);
            }
            for (int j = 0; j < k-1; j++) {
                in >> k2;
                stops.emplace_back();
                pfpf=stops.size();
                BusStop *y = new BusStop(k2-1,i+1,pfpf-1,x->number,0,INF);
                x->nextInRoute=y->number;
                stops[pfpf-2].push_back(std::make_pair(0, y));
                stops[pfpf-1].push_back(std::make_pair(0,y));
                stops[pfpf-1].push_back(std::make_pair(0,  x));
                if (k2 == start) {
                    y->time=0;
                    path.push(std::make_pair(0, y));
                    p.push_back(y->index);
                }
                ins[k2-1].insert(pfpf-1);
                x = y;
                k1 = k2;
            }
        }
        start = start - 1;
        end = end - 1;
        p.clear();
        BusStop* res,*post;
        long long time=INF;
        bool f=0;
        while (!path.empty()) {
            if(path.top().second->number==end && (path.top().second->time<time || time==INF)) {
                res=path.top().second->pred;
                post=path.top().second;
                time=path.top().second->time;
                f= true;
            }
            BusStop *cur = path.top().second;
            long long cur_t = -path.top().first;
            path.pop();
            if (cur->time < cur_t ) continue;
            for (int j = 1; j < stops[cur->index].size(); j++) {
                BusStop *neib = stops[cur->index][j].second;
                long long time ;
                if(cur->routNum!=neib->routNum )
                    time=3;
                else time=1;
                if (cur->time+ time < neib->time ) {
                    neib->time = cur->time+ time;
                    path.push(std::make_pair(-neib->time, neib));
                    neib->pred= cur;
                }
            }
            for (auto&x : ins[cur->number]) {
                if ((stops[x][0].second->routNum!=cur->routNum) || (stops[x][0].second->number==cur->number && stops[x][0].second->index!=cur->index )) {
                    if(stops[x][0].second->time==INF &&
                       stops[x][0].second->time>cur->time+3 ) {
                        stops[x][0].second->time=cur->time+3;
                        stops[x][0].second->pred = cur;
                        path.push({-cur->time - 3, stops[x][0].second});
                    }
                }
            }
        }
        if (!f)
            fout << "NoWay" << std::endl;
        else {
            fout << time << std::endl;
            p.push_back( post->number+1);
            p.push_back(post->routNum);
            while (res!=nullptr) {
                if( res->number == post->number){
                    res = res->pred;
                }
                else {
                    p.push_back(res->number+1);
                    p.push_back(res->routNum);
                    post = res;
                    res= res->pred;
                }
            }
            for(int i = p.size()-1;i>=0;i-=2)
                fout << "StopNo "<<p[i-1]  << " BusNo " << p[i]<< std::endl;
        }
    }
    return 0;
}

