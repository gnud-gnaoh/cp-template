#include "general.cpp"

struct BIT {
    int n, logn;
    vector<int> bit;

    BIT() = default;
    BIT(int _n) {
        n = _n;
        logn = __lg(n);
        bit.resize(n + 1);
    }

    void upd(int u, int v) {
        for (int i = u; i <= n; i += i & -i) {
            bit[i] += v;
        }
    }

    int get(int u) {
        int ans = 0;
        for (int i = u; i >= 1; i -= i & -i) {
            ans += bit[i];
        }
        return ans;
    }

    int get(int l, int r) {
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }

    int lower_bound(int u) {
        int sum = 0, pos = 0;
        for (int i = logn; i >= 0; i--) {
            int nxt = pos + (1 << i);
            if (nxt <= n && sum + bit[nxt] < u) {
                sum += bit[nxt];
                pos = nxt;
            }
        }
        return pos + 1;
    }
};
