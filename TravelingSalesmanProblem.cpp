#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <climits>

/*Решите задачу коммивояжёра на плоскости с евклидовой метрикой, если положения городов задаются их координатами.*/


//Алгоритм на основе построения двойного остовного дерева
void FindEulerPath (int V,std::vector<bool> &used2,std::vector <std::vector<std::pair<int,int>>> ost,std::vector<int> &euler) {
    euler.push_back(V);
    used2[V]= true;
    for(int i=0;i<ost[V].size();i++){
        if(!used2[ost[V][i].second])
            FindEulerPath(ost[V][i].second,used2,ost,euler);
    }
    return;
}
double distantion (double x,double y,double x1,double y1){
    return std::sqrt((x-x1)*(x-x1)+ (y-y1)*(y-y1));
}
struct  City{
    int x;
    int y;
    int number;
    City(int x1,int y1,int d,int num):x(x1),y(y1),number(num){};
};

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n,l,k;
    in>>n;
    std::vector<int> euler;
    std::vector<City*> ver(n);
    for(int i=0;i<n;i++) {
        in >> l >> k;
        City* a=new City(l,k,0,i);
        ver[i]=a;
    }
    std::vector<std::vector<std::pair<double,std::pair<int,int>>>> g(n,std::vector<std::pair<double,std::pair<int,int>>>());
    double d=0;
    for(int i=0;i<ver.size();i++){
        for(int j=i+1;j<ver.size();j++){
            d=distantion(ver[i]->x,ver[i]->y,ver[j]->x,ver[j]->y);
            g[i].push_back(std::make_pair(d,std::make_pair(i,j)));
            g[j].push_back(std::make_pair(d,std::make_pair(j,i)));
        }
    }
    std::vector <std::vector<std::pair<int,int>>> ost(n);
    const long long INF = LONG_LONG_MAX;
    std::vector<bool> used (n);
    std::vector<bool> used2(n, false);
    std::vector<double> min_e (n, INF), sel_e (n, -1);
    min_e[0] = 0;
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
                v = j;
            }
        used[v] = true;
        if (sel_e[v] != -1) {
            ost[v].push_back(std::make_pair(v, sel_e[v]));
            ost[sel_e[v]].push_back(std::make_pair(sel_e[v],v));
        }
        for (int to=0; to<g[v].size(); ++to) {
            if (g[v][to].first < min_e[g[v][to].second.second]) {
                min_e[g[v][to].second.second] = g[v][to].first;
                sel_e[g[v][to].second.second] = v;
            }
        }
    }
    for(int i=0;i<ost.size();i++){
        int k=ost[i].size();
        for(int j=0;j<k;j++){
            ost[i].push_back(ost[i][j]);
        }
    }
    double res=0;
    FindEulerPath(0,used2,ost,euler);
    euler.push_back(euler[0]);
    std::string s=std::to_string(ver[euler[0]]->number+1)+" ";
    for(int i=0;i<euler.size();i++) {
        for(int j=0;j<g[euler[i]].size();j++)
            if(g[euler[i]][j].second.second==euler[i+1]) {
                res += g[euler[i]][j].first;
                s+=std::to_string(g[euler[i]][j].second.second+1)+" ";
            }
    }
    res=round(res*1000)/1000;
    out<<std::fixed<<std::setprecision(3)<<res<<'\n'<<s.substr(0,s.size()-3);
    return 0;
}
