#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <fstream>
#include <vector>
#include <list>


/*Задана последовательность слов. Игра заключается в том, что игроки по очереди называют слова из заданной последовательности. Правило, по которому называется слово заключается в следующем: если названо некоторое слово, то следующий игрок может назвать слово, которое начинается с буквы, на которую заканчивается предыдущее слово, и которое ещё не было названо. Необходимо определить, можно ли в процессе игры выстроить цепочку из всех слов, причём последнее слово должно заканчиваться на ту букву, с которой начиналось первое слово. Например, для последовательности слов

terminator, department, epic, cat, rapid, toothpaste

требуемая цепочка слов имеет вид

cat, terminator, rapid, department, toothpaste, epic. */

void DFS(std::vector<bool> &visit,std::vector<std::vector<int>> &matrix, int cur) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[cur][j] > 0 && !visit[j]) {
                matrix[cur][j]=0;
                visit[j]=true;
                 DFS(visit, matrix, j);
            }
        }
    return;
}

int indexOf(std::vector<char> &symb, char a) {
    for (int i = 0; i < symb.size(); i++)
        if (symb[i] == a)
            return i;
}

bool containe(std::vector<char> &symb, char a) {
    for (int i = 0; i < symb.size(); i++)
        if (symb[i] == a)
            return true;
    return false;
}

int main() {
    //строки начало столбцы конец
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    int size = std::min(2 * n, 26);
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    std::vector<bool> visit(size, true);
    std::string s;
    std::vector<char> symb;
    char begin, end;
    for (int i = 0; i < n; i++) {
        in >> s;
        begin = s[0];
        end = s[s.length() - 1];
        if (!containe(symb, begin))
            symb.push_back(begin);
        if (!containe(symb, end))
            symb.push_back(end);
        int p = indexOf(symb, begin), l = indexOf(symb, end);
        matrix[p][l] += 1;
        visit[p]=false;
    }
    in.close();
    int k;
    bool f = true;
    for (int i = 0; i < size; i++) {
        k = 0;
        for (int j = 0; j < size; j++) {
            if (j == i) continue;
            k += matrix[i][j];
            k -= matrix[j][i];
        }
        if (k != 0) {
            out << "No";
            return 0;
        }
    }
    DFS(visit,matrix, 0);
    for(int i=0;i<visit.size();i++){
        if(!visit[i]) {
            out << "No";
            return 0;
        }
    }
     out << "Yes";
    out.close();
    return 0;
}



