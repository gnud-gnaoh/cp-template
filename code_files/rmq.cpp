#include "general.cpp"

const int INF = 0x3f3f3f3f3f3f3f3f;

struct RMQ {
    int n, logn;
    vector<vector<int>> st;

    RMQ() = default;
    RMQ(int _n) {
        n = _n;
        logn = __lg(n + 1);
        st.resize(logn, vector<int>(n + 1));
    }
    RMQ(const vector<int>& a) {
        n = sz(a) - 1; // 1-index
        logn = __lg(n + 1);
        st.resize(logn, vector<int>(n + 1, INF));
        for (int i = 1; i <= n; i++) {
            st[0][i] = a[i];
        } 
        for (int j = 1; j < logn; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int get(int l, int r) {
        int j = __lg(r - l + 1);
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};