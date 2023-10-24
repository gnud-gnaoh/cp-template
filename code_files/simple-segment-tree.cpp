#include "general.cpp"

struct SegmentTree {
    int n, val;
    vector<int> nd;

    SegmentTree() = default;
    SegmentTree(int _n, int _val) {
        n = _n, val = _val;
        nd.resize(4 * n + 5, val);
    }

    void upd(int i, int v, int x, int lx, int rx) {
        if (lx == rx) {
            nd[x] = v;
            return;
        }
        int m = lx + rx >> 1;
        if (i <= m) upd(i, v, x << 1, lx, m);
        else upd(i, v, x << 1 | 1, m + 1, rx);
        nd[x] = max(nd[x << 1], nd[x << 1 | 1]);
    }

    void upd(int i, int v) {
        upd(i, v, 1, 1, n);
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
