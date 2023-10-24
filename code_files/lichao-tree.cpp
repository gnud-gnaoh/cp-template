#include "general.cpp"

struct LichaoSegmentTree {
    struct Line {
        int m, b;
        int operator() (int x) {
            return m * x + b;
        }
    };

    int n;
    vector<Line> st;

    LichaoSegmentTree() = default;
    LichaoSegmentTree(int _n) {
        n = _n;
        st.resize(4 * n + 5);
    }

    void upd(int x, int lx, int rx, Line seg){
        if (lx + 1 == rx) {
            if (seg(lx) > st[x](lx)) st[x] = seg;
            return;
        }

        int m = (lx + rx) / 2;
        if (st[x].m > seg.m) swap(seg, st[x]);
        if (st[x](m) < seg(m)) {
            swap(st[x] , seg);
            upd(2 * x + 1, lx, m, seg);
        } else {
            upd(2 * x + 2, m, rx, seg);
        }
    }

    int get(int x, int lx, int rx, int i){
        if (lx + 1 == rx) return st[x](i);
        int m = (lx + rx) / 2;
        if (i < m) return max(st[x](i), get(2 * x + 1, lx, m, i));
        else return max(st[x](i), get(2 * x + 2, m, rx, i));
    }
};

/*
Insert line f(x) = mx + b
Query for max f(t) for all lines

Negating both m and b for min instead of max
Be careful: [lx, rx)
Remember to insert Line(0, 0) or something before doing queries
*/
