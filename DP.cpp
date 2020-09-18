#include<iostream>
#include<fstream>
#include<set>
#include<cmath>
#include <vector>


/*Заданы три числа a, b и c. Необходимо определить, можно ли представить число a в виде a = x1 ⋅ x2 ⋅ … ⋅ xk, где k ≥ 1, b ≤ xi ≤ c и xi, a, b, c — целые числа. Кроме того, требуется минимизировать число множителей. Также следует предусмотреть вариант, когда такого представления не существует.
*/

int main() {
    std::set<int> factors, need;
    int a, b, c;
    std::ifstream fin("input.txt");
    fin >> a >> b >> c;
    std::ofstream fout("output.txt");
    if (a < b)
        fout << "-1";
    else if (a >= b && a <= c)
        fout << "1";
    else {
        factors.insert(1);
        for (int i = b; i <= (int) sqrt(a); ++i) {
            if (!(a % i))
                factors.insert(i);
            if (a / i >= b)
                factors.insert(a / i);
        }
        factors.insert(a);
        std::vector<int> dels(factors.size());
        int counter = 0;
        std::vector<int> newFactors(factors.size());
        for (auto it = factors.begin(); it != factors.end(); ++it, ++counter) {
            newFactors[counter] = *it;
            if (*it <= c) {
                need.insert(*it);
                dels[counter] = 1;
            } else
                dels[counter] = 0;
        }
        for(int j=need.size();j<newFactors.size();j++){
            int min = std::numeric_limits<int>::max();
            for (int i = 1; i < j; ++i) {
                if (dels[i] != -1 && dels[i] + 1 < min && newFactors[j] % newFactors[i] == 0 &&
                    need.find(newFactors[j] / newFactors[i]) != need.end()) {
                    dels[j] = dels[i] + 1;
                    min = dels[i] + 1;
                }
            }
            if (dels[j] == 0)
                dels[j] = -1;
        }
        fout << dels[factors.size() - 1];
    }
}
