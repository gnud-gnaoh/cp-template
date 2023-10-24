#include "general.cpp"

struct Matrix {
    vector<vector<int>> data;

    int row() const { return data.size(); }
    int col() const { return data[0].size(); }

    auto & operator [] (int i) { return data[i]; }
    const auto & operator [] (int i) const { return data[i]; }
    
    Matrix() = default;
    Matrix(int r, int c) : data(r, vector<int>(c)) {}
    Matrix(const vector<vector<int>>& d) : data(d) {}

    friend ostream & operator << (ostream& out, const Matrix& d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }

    static Matrix identity(int n) {
        Matrix a(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }

    Matrix operator * (const Matrix& b) {
        Matrix a = *this;
        
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); i++) {
            for (int j = 0; j < b.col(); j++) {
                for (int k = 0; k < a.col(); k++) {
                    // c[i][j] += a[i][k] * b[k][j];
                    c[i][k] += a[i][j] * b[j][k]; // this is faster
                }
            }
        }

        return c;
    }

    Matrix pow(int b) {
        assert(row() == col());
        Matrix a = *this;
        Matrix ans = identity(row());
        while (b) {
            if (b & 1) ans = ans * a;
            a = a * a;
            b >>= 1;
        }
        return ans;
    }
};
