struct Line {
    int m, b;
    int operator() (int x) {
        return m * x + b;
    }
} st[N * 4];

void Insert(int x, int lx, int rx, Line seg){
    if (lx + 1 == rx) {
        if (seg(lx) > st[x](lx)) st[x] = seg;
        return;
    }

    int m = (lx + rx) / 2;
    if (st[x].m > seg.m) swap(seg, st[x]);
    if (st[x](m) < seg(m)) {
        swap(st[x] , seg);
        Insert(2 * x + 1, lx, m, seg);
    } else {
        Insert(2 * x + 2, m, rx, seg);
    }
}

int Query(int x, int lx, int rx, int i){
    if (lx + 1 == rx) return st[x](i);
    int m = (lx + rx) / 2;
    if (i < m) return max(st[x](i), Query(2 * x + 1, lx, m, i));
    else return max(st[x](i), Query(2 * x + 2, m, rx, i));
}