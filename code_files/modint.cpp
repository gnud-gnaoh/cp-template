#include "general.cpp"

const int MOD = 1e9 + 7;

struct Mint {
    int v;
    explicit operator int() { return v; }
    Mint() { v = 0; }
    Mint(long long _v) { v = _v % MOD; v += (v < 0) * MOD; }
    bool operator == (const Mint& oth) const { return v == oth.v; }
};
Mint& operator += (Mint& a, const Mint& b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
Mint& operator -= (Mint& a, const Mint& b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
Mint operator + (Mint a, Mint b) { return a += b; }
Mint operator - (Mint a, Mint b) { return a -= b; }
Mint operator * (const Mint& a, const Mint& b) { return Mint(1LL * a.v * b.v); }
Mint& operator *= (Mint& a, Mint b) { return a = a * b; }
Mint pow(Mint a, long long p) {
    Mint res = 1;
    while (p) {
        if (p & 1) res *= a;
        a *= a;
        p >>= 1;
    }
    return res;
}
Mint inv(Mint a) {
    return pow(a, MOD - 2);
}
Mint operator / (Mint a, Mint b) { return a * inv(b); }