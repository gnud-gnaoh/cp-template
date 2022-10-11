vector<int> adj[N];

int sz[N], par[N];
bool vis[N];

void DfsSize(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            DfsSize(v, u);
            sz[u] += sz[v];
        }
    }
}

int FindCentroid(int u, int p, int s) {
    for (int v : adj[u]) {
        if (v != p && !vis[v] && sz[v] * 2 > s) {
            return FindCentroid(v, u, s);
        }
    }
    return u;
}

void DfsCalc(int u, int p, bool cal) {
    if (cal) {
        // calculate answer
    } else {
        // update
    }
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            DfsCalc(v, u, cal);
        }
    }
}

void BuildCentroid(int u, int p) {
    DfsSize(u, 0);

    int c = FindCentroid(u, p, sz[u]);
    vis[c] = 1;
    par[c] = p;

    for (int v : adj[c]) {
        if (!vis[v]) {
            DfsCalc(v, c, 1);
            DfsCalc(v, c, 0);      
        }
    }
    
    for (auto& [v, w] : adj[c]) {
        if (!vis[v]) {
            BuildCentroid(v, c);
        }
    }
}