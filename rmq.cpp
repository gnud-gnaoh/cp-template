// range minimum queries
int st[LG][N];
// int mlg[N]; // optional

int Get(int l, int r) {
    int j = __lg(r - l + 1);
    return min(st[j][l], st[j][r - (1 << j) + 1]);
}

void Init() {
    memset(st, 0x3f, sizeof st);

    // mlg[1] = 0;
    // for (int i = 2; i <= n; i++) {
    //     mlg[i] = mlg[i / 2] + 1;
    // }

    for (int i = 1; i <= n; i++) {
        st[0][i] = a[i];    
    }

    for (int j = 1; j < LG; j++) {
        for (int i = 1; i <= n; i++) {
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
}