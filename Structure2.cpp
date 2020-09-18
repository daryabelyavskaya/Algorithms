#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

/*Имеется план местности, разбитой на квадраты, заданный матрицей A размера n × m. Каждый квадрат c координатами (i, j) имеет высоту относительно уровня моря, значение которой определяется натуральным числом aij (нумерация строк и столбцов матрицы a начинается с 1, верхний левый квадрат матрицы имеет координаты (1, 1)). Робот может двигаться только по местности и только параллельно осям OX и OY между центрами квадратов. При переходе в соседний квадрат длина подъёма (спуска) равна модулю разности высот квадратов, а длина перемещения из квадрата в квадрат равна k. Необходимо найти среди маршрутов робота из позиции (x1, y1) в позицию (x2, y2) маршрут минимальной длины. Длина маршрута определяется как суммарная длина подъёмов и спусков плюс суммарная длина перемещений из квадрата в квадрат.

Формат входных данных
Первая строка содержит числа n и m (1 ≤ n, m ≤ 1 000) — размеры поля, по которому двигается робот (числа разделены одним или несколькими пробелами).

Следующие n строк содержат информацию о матрице высот каждого квадрата (строка входа соответствует строке матрицы высот; высоты — целые числа от 0 до 109).

Следующая строка — число k (целое число от 0 до 109).

В последней строке задаются координаты начальной и конечной точек движения робота: x1, y1, x2, y2 (числа разделяются одним или несколькими пробелами).

Формат выходных данных
Выведите длину кратчайшего маршрута робота.*/

struct Stop {
    int i = 0;
    int j = 0;
    long long d = 0;

    Stop(int i1, int j1, long long k1) : i(i1), j(j1), d(k1) {};
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    int n, m, k, el;
    in >> n >> m;
    std::vector<std::pair<long long, Stop *>> a(m);
    std::vector<std::vector<std::pair<long long, Stop *> > > matrix(n, a);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            in >> el;
            matrix[i][j] = std::make_pair(0L, new Stop(i, j, el));
        }
    in >> k;
    int startx, starty, endx, endy;
    in >> startx >> starty >> endx >> endy;
    if (startx == endx && starty == endy)
        out << "0";
    else {
        startx -= 1;
        starty -= 1;
        endx -= 1;
        endy -= 1;
        long long INF = LONG_LONG_MAX;
        std::vector<std::vector<long long>> length(n, std::vector<long long>(m, INF));
        length[startx][starty] = 0;
        std::priority_queue<std::pair<long long, Stop *> > q;
        q.push(matrix[startx][starty]);
        while (!q.empty()) {
//                 if(q.top().second->i ==endx && q.top().second->j ==endy)
//                     break;
            Stop *cur = q.top().second;
            long long cur_d = -q.top().first;
            q.pop();
            if (length[cur->i][cur->j] < cur_d) continue;
            //нижний
            if ((cur->i + 1) <= (n - 1) &&
                (cur_d + k + abs(cur->d - matrix[cur->i + 1][cur->j].second->d)) < length[cur->i + 1][cur->j]) {
                length[cur->i + 1][cur->j] = length[cur->i][cur->j] + abs(cur->d - matrix[cur->i + 1][cur->j].second->d) + k;
                q.push(std::make_pair(-length[cur->i + 1][cur->j], matrix[cur->i + 1][cur->j].second));
            }
            //верхний
            if ((cur->i - 1) >= 0 &&
                (cur_d + k + abs(cur->d - matrix[cur->i - 1][cur->j].second->d)) < length[cur->i - 1][cur->j]) {
                length[cur->i - 1][cur->j] =length[cur->i][cur->j] + abs(cur->d - matrix[cur->i - 1][cur->j].second->d) + k;
                q.push(std::make_pair(-length[cur->i - 1][cur->j], matrix[cur->i - 1][cur->j].second));
            }
            //правый брат
            if ((cur->j + 1) <= m - 1 &&
                (cur_d + k + abs(cur->d - matrix[cur->i][cur->j + 1].second->d)) < length[cur->i][cur->j + 1]) {
                length[cur->i][cur->j + 1] = length[cur->i][cur->j] + abs(cur->d - matrix[cur->i][cur->j + 1].second->d) + k;
                q.push(std::make_pair(-length[cur->i][cur->j + 1], matrix[cur->i][cur->j + 1].second));
            }
            //левый брат
            if ((cur->j - 1) >= 0 &&
                (cur_d + k + abs(cur->d - matrix[cur->i][cur->j - 1].second->d)) < length[cur->i][cur->j - 1]) {
                length[cur->i][cur->j - 1] = length[cur->i][cur->j] + abs(cur->d - matrix[cur->i][cur->j - 1].second->d) + k;
                q.push(std::make_pair(-length[cur->i][cur->j - 1], matrix[cur->i][cur->j - 1].second));
            }
        }
        out << length[endx][endy];
    }
}

