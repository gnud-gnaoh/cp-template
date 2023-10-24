#include "general.cpp"

const int N = 1e5 + 5;

vector<int> adj[N];

int sz[N], par[N];
bool vis[N];

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p, int s) {
    for (int v : adj[u]) {
        if (v != p && !vis[v] && sz[v] * 2 > s) {
            return find_centroid(v, u, s);
        }
    }
    return u;
}

void dfs_calc(int u, int p, bool cal) {
    if (cal) {
        // calculate answer
    } else {
        // update
    }
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            dfs_calc(v, u, cal);
        }
    }
}

void build_centroid(int u, int p) {
    dfs_size(u, 0);

    int c = find_centroid(u, p, sz[u]);
    vis[c] = 1;
    par[c] = p;

    for (int v : adj[c]) {
        if (!vis[v]) {
            dfs_calc(v, c, 1);
            dfs_calc(v, c, 0);      
        }
    }
    
    for (int v : adj[c]) {
        if (!vis[v]) {
            build_centroid(v, c);
        }
    }
}