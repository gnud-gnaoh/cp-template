int tree[4 * N];

int Get(int l, int r, int x, int lx, int rx) {
    if (l > rx || r < lx) {
        return 0;
    }
    if (l <= lx && rx <= r) {
        return tree[x];
    }
    int m = (lx + rx) / 2;
    int leftnode = Get(l, r, 2 * x, lx, m);
    int rightnode = Get(l, r, 2 * x + 1, m + 1, rx);
    return leftnode + rightnode;
}

int Get(int l, int r) {
    return Get(l, r, 1, 1, n);
}

void Set(int pos, int v, int x, int lx, int rx) {
    if (lx == rx) {
        tree[x] = v;
        return;
    }
    int m = (lx + rx) / 2;
    if (pos <= m) {
        Set(pos, v, 2 * x, lx, m);
    } else {
        Set(pos, v, 2 * x + 1, m + 1, rx);
    }
    tree[x] = tree[2 * x] + tree[2 * x + 1];
}

void Build(int x, int lx, int rx) {
    if (lx == rx) {
        tree[x] = a[lx];
        return;
    }
    int m = (lx + rx) / 2;
    Build(2 * x, lx, m);
    Build(2 * x + 1, m + 1, rx);
    tree[x] = tree[2 * x] + tree[2 * x + 1];
}

void Build() {
    Build(1, 1, n);
}
