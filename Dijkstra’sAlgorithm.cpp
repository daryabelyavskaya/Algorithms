#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

int main() {
    long long INF = LONG_LONG_MAX;
    std::ios_base::sync_with_stdio(false);
        int n,m,d,a,b;
        std::ifstream in("input.txt");
        in>>n>>m;
        std::vector < std::vector < std::pair<int,int> > > graph(n);
        for(int i=0;i<m;i++) {
            in >> a >> b>> d;
            graph[a-1].push_back(std::make_pair(d,b-1));
            graph[b-1].push_back(std::make_pair(d,a-1));
        }
        std::vector<long long> length (n, INF);
        length[0] = 0;
        std::priority_queue < std::pair<long long,int> > q;
        q.push (std::make_pair (0, 0));
        while (!q.empty()) {
            int cur = q.top().second;
            long long  cur_d = -q.top().first;
            q.pop();
            if (length[cur]<cur_d )  continue;
            for (int j=0; j<graph[cur].size(); ++j) {
                int   neib = graph[cur][j].second;
                long long len = graph[cur][j].first;
                if (length[cur] + len < length[neib]) {
                    length[neib] = length[cur] + len;
                    q.push (std::make_pair ( -length[neib],neib));
                }
            }
        }
        std::ofstream out("output.txt");
        out<<length[n-1]<<'\n';
    return 0;
}