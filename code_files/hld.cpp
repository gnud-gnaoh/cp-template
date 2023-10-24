#include "general.cpp"

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
vector<int> adj[N];
int timer = 0, par[N], tin[N], tout[N], sz[N], nxt[N], dep[N];

struct SegmentTree {
    int n, val;
    vector<int> nd, lz;

    SegmentTree() = default;
    SegmentTree(int _n, int _val) {
        n = _n, val = _val;
        nd.resize(4 * n + 5, val);
        lz.resize(4 * n + 5, 0);
    }

    void down(int x) {
        nd[x << 1] += lz[x];
        lz[x << 1] += lz[x];
        nd[x << 1 | 1] += lz[x];
        lz[x << 1 | 1] += lz[x];
        lz[x] = 0;
    }

    void upd(int l, int r, int v, int x, int lx, int rx) {
        if (lx > r || rx < l) return;
        if (l <= lx && rx <= r) {
            nd[x] += v;
            lz[x] += v;
            return;
        }
        int m = lx + rx >> 1;
        upd(l, r, v, x << 1, lx, m);
        upd(l, r, v, x << 1 | 1, m + 1, rx);
        nd[x] = max(nd[x << 1], nd[x << 1 | 1]);
    }

    void upd(int l, int r, int v) {
        upd(l, r, v, 1, 1, n);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (lx > r || rx < l) return val;
        if (l <= lx && rx <= r) return nd[x];
        int m = lx + rx >> 1;
        return max(get(l, r, x << 1, lx, m), get(l, r, x << 1 | 1, m + 1, rx));
    }

    int get(int l, int r) {
        return get(l, r, 1, 1, n);
    }
};

SegmentTree st;

void dfs(int u, int p) {
    par[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

void dfs_size(int u) {
    sz[u] = 1;
    for (int& v : adj[u]) {
        dfs_size(v);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
    }
}

void dfs_hld(int u) {
    tin[u] = ++timer;
    for (int& v : adj[u]) {
        nxt[v] = (v == adj[u][0] ? nxt[u] : v);
        dfs_hld(v);
    }
    tout[u] = timer;
}

void subtree_upd(int u, int v) {
    st.upd(tin[u], tout[v], v);
}

int get(int u, int v) {
    int ans = -INF;
    while (nxt[u] != nxt[v]) {
        if (dep[nxt[u]] < dep[nxt[v]]) swap(u, v);
        ans = max(ans, st.get(tin[nxt[u]], tin[u]));
        u = par[nxt[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans = max(ans, st.get(tin[u], tin[v]));
    return ans;
}

/* Usage:
dfs(1, 0);
for (int i = 2; i <= n; i++) adj[i].erase(find(all(adj[i]), par[i]));
dfs_size(1);
nxt[1] = 1;
dfs_hld(1);
*/