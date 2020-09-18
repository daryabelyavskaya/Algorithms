#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>...
#include <climits>

/*Среди полупутей минимальной положительной длины между листьями выбрать тот, у которого сумма ключей вершин минимальна. Если такой полупуть существует и имеет чётную длину, то удалить (правым удалением) центральную вершину этого полупути.

Если решение неоднозначно, то выбирать такой минимальный полупуть между листьями, корневая вершина которого имеет минимальное ключевое значение.*/

struct ver{
    int v;
    int max;
    int min;
    ver(int v1,int max1,int min1):v(v1),max(max1),min(min1){};
};
int main() {
    std::ifstream in("bst.in");
    std::ofstream out("bst.out");
    int n,root,k,l;
    std::string s;
    in>>n>>root;
    std::vector<ver*> tree(n+1,new ver(0,INT32_MAX,INT32_MIN));
    bool flag= true;
    int max=INT32_MAX,min=INT32_MIN;
    tree[1]=new ver(root,max,min);
    for(int i=2;i<=n;i++) {
        in >> k >> l >> s;
        if(s=="L" && k<tree[l]->max)
        {
            if (tree[l]->v == INT32_MIN){
                flag = false;
                break;
            }
            tree[i]->v = k;
            tree[i]->max=tree[l]->v-1;
            tree[i]->min=tree[l]->min;
        }
        else if(s=="R"  && k>=tree[l]-> min) {
            tree[i]->v=k;
            tree[i]->min=tree[l]->v;
            tree[i]->max=tree[l]->max;

        }
        else {
            flag= false;
            break;
        }

    }
    if(flag) out<<"YES";
    else out<<"NO";

    return 0;
}
