#include "general.cpp"

struct DSU {
    int n, cc;
    vector<int> par, sz;

    DSU() = default;
    DSU(int _n) {
        n = _n;
        cc = n;
        par.resize(n + 1);
        sz.resize(n + 1, 1);
    }

    int find(int u) {
        return !par[u] ? u : par[u] = find(par[u]);
    }

    bool unite(int u, int v) {
        if ((u = find(u)) == (v = find(v))) return false;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        cc--;
        return true;
    }
};
