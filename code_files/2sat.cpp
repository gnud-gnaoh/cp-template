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

void dfs1(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v]) continue;
        dfs1(v);
    }
    ord.push_back(u);
}

void dfs2(int u, int col) {
    comp[u] = col;
    for (int v : radj[u]) {
        if (comp[v]) continue;
        dfs2(v, col);
    }
}

bool twosat() {
    for (int i = 0; i < 2 * n; i++) {
        if (vis[i]) continue;
        dfs1(i);
    }

    for (int i = 0, j = 1; i < 2 * n; i++) {
        int u = ord[2 * n - i - 1];
        if (comp[u]) continue;
        dfs2(u, j++);
    }

    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i + 1]) return false;
        res[i / 2] = comp[i] > comp[i + 1];
    }

    return true;
}

// a or b
void AddEdge(int a, bool na, int b, bool nb) {
    a = 2 * a ^ na;
    b = 2 * b ^ nb;
    int aa = a ^ 1;
    int bb = b ^ 1;

    adj[aa].push_back(b);
    radj[b].push_back(aa);

    adj[bb].push_back(a);
    radj[a].push_back(bb);
}

void AddNxor(int u, int v) {
    AddEdge(u, 0, v, 1);
    AddEdge(u, 1, v, 0);
}
 
void AddXor(int u, int v) {
    AddEdge(u, 1, v, 1);
    AddEdge(u, 0, v, 0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;

        if (c[u] == 0) {
            if (c[v] == 0) {
                AddEdge(u, 0, v, 0);
                AddEdge(u, 1, v, 1);
            } else if (c[v] == 1) {
                AddEdge(u, 0, v, 1);
            } else {
                AddEdge(u, 1, v, 0);
            }
        } else if (c[u] == 1) {
            if (c[v] == 0) {
                AddEdge(u, 1, v, 0);
            } else if (c[v] == 1) {
                AddEdge(u, 0, v, 0);
                AddEdge(u, 1, v, 1);
            } else {
                AddEdge(u, 0, v, 1);
            }
        } else {
            if (c[v] == 0) {
                AddEdge(u, 0, v, 1);
            } else if (c[v] == 1) {
                AddEdge(u, 1, v, 0);
            } else {
                AddEdge(u, 0, v, 0);
                AddEdge(u, 1, v, 1);
            }
        }
    }

    if (twosat()) {
        for (int i = 0; i < n; i++) {
            if (res[i]) {
                c[i] = (c[i] + 1) % 3;
            } else {
                c[i] = (c[i] - 1 + 3) % 3;
            }
            cout << c[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << -1 << '\n';
    }
}
