#include "general.cpp"

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 5;
const int LIM = 100; // maximum edge weight

int n, m;
vector<pair<int, int>> adj[N];
vector<int> qs[LIM + 5];
int dist[N];
int st;

void init() {
    fill(dist + 1, dist + n + 1, INF);
    dist[st] = 0;
    qs[0].push_back(st);
    
    for (int d = 0, maxd = 0; d <= maxd; d++) {
        for (auto& q = qs[d % LIM]; q.size(); ) {
            int u = q.back();
            q.pop_back();
            if (dist[u] != d) continue;
            for (pair<int, int> tv : adj[u]) {
                int v = tv.first;
                int w = tv.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    qs[dist[v] % LIM].push_back(v);
                    maxd = max(maxd, dist[v]);
                }
            }
        }
    }
}