int bit[N];

void Update(int u, int v) {
    for (int i = 1; i <= n; i += i & -i) {
        bit[i] += v;
    }
}

int Get(int u) {
    int ans = 0;
    for (int i = u; i >= 1; i -= i & -i) {
        ans += bit[i];
    }
    return ans;
}

int Get(int l, int r) {
    return Get(r) - Get(l - 1);
}