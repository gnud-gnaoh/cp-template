#include "general.cpp"

const int N = 1e5 + 5;
const int NN = 2e5 + 5;

int n, m;
int c[N];

vector<int> adj[NN], radj[NN];
bool vis[NN];
vector<int> ord;
int comp[NN];
bool res[N];

void dfs_1(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v]) continue;
        dfs_1(v);
    }
    ord.push_back(u);
}

void dfs_2(int u, int col) {
    comp[u] = col;
    for (int v : radj[u]) {
        if (comp[v]) continue;
        dfs_2(v, col);
    }
}

bool twosat() {
    for (int i = 0; i < 2 * n; i++) {
        if (vis[i]) continue;
        dfs_1(i);
    }

    for (int i = 0, j = 1; i < 2 * n; i++) {
        int u = ord[2 * n - i - 1];
        if (comp[u]) continue;
        dfs_2(u, j++);
    }

    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i + 1]) return false;
        res[i / 2] = comp[i] > comp[i + 1];
    }

    return true;
}

// a or b
void add_edge(int a, bool na, int b, bool nb) {
    a = 2 * a ^ na;
    b = 2 * b ^ nb;
    int aa = a ^ 1;
    int bb = b ^ 1;

    adj[aa].push_back(b);
    radj[b].push_back(aa);

    adj[bb].push_back(a);
    radj[a].push_back(bb);
}

void add_nxor(int u, int v) {
    add_edge(u, 0, v, 1);
    add_edge(u, 1, v, 0);
}
 
void add_xor(int u, int v) {
    add_edge(u, 1, v, 1);
    add_edge(u, 0, v, 0);
}
