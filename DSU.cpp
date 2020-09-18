#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*В Берляндии nnn городов, связанных mmm дорогами. Гарантируется, что изначально граф из городов связный, т.е. существует путь между любой парой вершин.
В Берляндии происходит qqq землетрясений, в ходе каждого из них разрушается ровно одна дорога. Необходимо после каждого землетрясения узнать, является ли полученный граф из городов связным. После очередного землетрясений дорога не перестраивается, то есть разрушается навсегда.*/
int counter;
int Find(std::vector<int>&p,int i){
    while(p[i]!=0){
        i=p[i];
    }
    return i;
}
void Union(std::vector<int>&p,int i,int j,std::vector<int>&k){
    int root1=Find(p,i),root2=Find(p,j);
    if(root1==root2)
        return;
    else {
        if(abs(k[root1])>=abs(k[root2])){
            k[root1] -= 1;
            p[root2]=root1;
        }
        else{
            p[root1]=root2;
            k[root2] -= 1;
        }
    }
    counter--;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n,m,q,a,b;
    in>>n>>m>>q;
    std::string s;
    counter=n;
    std::vector<std::pair<int,int>> reb;
    reb.push_back(std::make_pair(0,0));
    std::vector<int> mark(m+1),isRemove(q+1),p(n+1),k(n+1);
    for (int i = 1; i <m+1; i++) {
        in >> a >> b;
        reb.push_back(std::make_pair(a, b));
    }
    for(int j=1;j<q+1;j++)
    {
        in>>a;
        isRemove[j]=a;
        mark[a]=1;
    }
    for(int i=1;i<m+1;i++){
        if(mark[i]==1) continue;
        Union(p,reb[i].first,reb[i].second,k);
    }

    for(int j=q;j>0;j--) {
        if(counter==1) s+="1";
        else{
            s+="0";
        }
        Union(p,reb[isRemove[j]].first,reb[isRemove[j]].second,k);
    }
    reverse(s.begin(),s.end());
    out<<s;
    return 0;
}
