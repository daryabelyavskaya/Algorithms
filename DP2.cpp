#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*Вдоль большой широкой дороги располагаются деревни. Дорога представляет собой ось с целочисленными координатами, а позиции каждой деревни соответствует её координата (единственное целое число). Известно, что все деревни расположены в разных местах (нет двух деревень с одинаковой координатой). Расстояние между двумя координатами вычисляется как абсолютная разность их величин. Было решено построить почтовые отделения в деревнях, но не обязательно во всех. Будем считать, что координаты деревни и почтового отделения, построенного в этой деревне, совпадают. Для построения почты в деревнях, координаты почтовых отделений должны быть выбраны таким образом, чтобы сумма расстояний от каждой деревни до ближайшего почтового отделения была минимальна. Необходимо по данным координатам деревень и количеству почтовых отделений вычислить минимальную сумму из всех возможных сумм расстояний между деревнями и их ближайшими почтовыми отделениями.

Первая строка содержит два числа: число v деревень (1 ≤ v ≤ 2000) и число p почтовых отделений (1 ≤ p ≤ 30, p ≤ v). Вторая строка содержит v целых чисел xi в возрастающем порядке, которые соответствуют координатам деревень (|xi| ≤ 10 000).
*/

int main() {
    int count_of_post,point,count;
    std::ifstream in("input.txt");
    std::vector<int> points;
    in>>count>>count_of_post;
    if (in.is_open())
    {
        for(int i=0;i<count;i++)
        {
                in >> point ;
                points.push_back(point);
        }
    }
    std::vector<std::vector<int>> d(count_of_post,std::vector<int>(count,0));
    for(int i=0;i<count;i++){
        for(int j=0;j<i;j++){
            d[0][i]+=abs(points[i]-points[j]);
        }
    }
    int min;
    int step;
    int *middle;
    for (int i = 1; i < count_of_post; i++) {
        for (int j = 0; j < count;j++) {
            int sumlef=0,sumright=0,index=0;
            min = INT32_MAX;
            step=0;
            middle=&points[j];
            if(j>=i) {
                if(i==j)
                    min=0;
                else {
                    for (int k = j-1; k > i-2; k--,index++) {
                        if (j-1 == k) {
                            step = d[i - 1][k];
                            middle=&points[k];
                            index=0;
                        } else {
                            step = d[i - 1][k];
                            sumlef+=(points[k+1]-points[k])*(index);
                            while  (abs(*middle - points[j]) <abs(*middle - points[k]) && middle>=&points[k+1]) {
                                sumright += abs(*middle - points[j]) ;
                                sumlef-=abs(*middle-points[k]);
                                middle--;
                                index--;
                            }
                        }
                        step += sumright + sumlef;
                        if (min > step)
                            min = step;
                    }
                    d[i][j] = min;
                }
            }

            else d[i][j]=-1;

        }
    }
    in.close();
    std::ofstream fout("output.txt");
    std::vector<int> ans(count);
    int min1=INT32_MAX;
    for (int k = count_of_post-1; k <count ; k++) {
        step = d[count_of_post-1][k];
        if(k==count-2) {
            k++;
        k--;
    }
        for (int q = k + 1; q < count; q++) {
            step += abs(points[q] - points[k]);
        }
       // d[count_of_post][k]=step;
        if(step<min1)
            min1=step;
    }

    fout<<min1;
    return 0;
}
