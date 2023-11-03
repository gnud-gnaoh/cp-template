#include "general.cpp"
#include "modint.cpp"

const int N = 1e6 + 5;
const int P = 331; // base
// big prime mod 1e11 + 7

int op[N];
Mint mp[N];

void compute_pow() {
    op[0] = 1;
    mp[0] = 1;
    for (int i = 1; i < N; i++) {
        op[i] = op[i - 1] * P;
        mp[i] = mp[i - 1] * P;
    }
}

struct Hash {
    int n;
    vector<int> oh;
    vector<Mint> mh;

    Hash() = default;
    Hash(const string& a) {
        n = sz(a); // a is 0-indexed
        oh.resize(n + 1);
        mh.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            oh[i] = oh[i - 1] * P + a[i - 1];
            mh[i] = mh[i - 1] * P + a[i - 1];
        }
    }

    pair<int, Mint> get(int l, int r) {
        return {oh[r] - oh[l - 1] * op[r - l + 1], mh[r] - mh[l - 1] * mp[r - l + 1]};
    }
};

pair<int, Mint> get_single_hash(const string& a) {
    int oh;
    Mint mh;
    for (int i = 0; i < sz(a); i++) {
        oh = oh * P + a[i];
        mh = mh * P + a[i];
    }
    return {oh, mh};
}
