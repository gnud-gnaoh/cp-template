int Add(int a, const int& b) {
    if ((a += b) >= MOD) a -= MOD;
    return a;
}

void Sadd(int& a, const int& b) {
    if ((a += b) >= MOD) a -= MOD;
}

int Sub(int a, const int& b) {
    if ((a -= b) < 0) a += MOD;
    return a;
}

void Ssub(int& a, const int& b) {
    if ((a -= b) < 0) a += MOD;
}

int Mul(const int& a, const int& b) {
    return 1LL * a * b % MOD;
}

void Smul(int& a, const int& b) {
    a = Mul(a, b);
}

int Pow(int a, int b) {
    // b %= MOD - 1; // for prime mod
    int res = 1;
    while (b) {
        if (b & 1) Smul(res, a);
        Smul(a, a);
        b >>= 1;
    }
    return res;
}

int Inv(int a) {
    return Pow(a, MOD - 2);
}