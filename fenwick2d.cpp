/*
n, m <= 1e9
q <= 1e5

2 types of queries:
- {1, i, j, v} (1 <= i <= m, 1 <= j <= n, |v| <= 1e9): add v to square (i, j)
- {2, x1, y1, x2, y2}: find the sum of squares inside rectangle with the corresponding 4 corners
*/
#include <bits/stdc++.h>
using namespace std;

const int Q = 1e5;
const int INF = 2e9;

int m, n, q, queries[Q + 5][5], sz;
vector<int> cx, cy;
vector<vector<int>> nodes;
vector<vector<long long>> bit;

void fakeupd(int i, int j) {
    for (int ii = i; ii <= sz; ii += ii & -ii) {
        nodes[ii].push_back(j);
    }
}

void upd(int i, int j, int v) {
    for (int ii = i; ii <= sz; ii += ii & -ii) {
        for (int jj = lower_bound(nodes[ii].begin(), nodes[ii].end(), j) - nodes[ii].begin() + 1; jj <= (int)nodes[ii].size(); jj += jj & -jj) {
            bit[ii][jj] += v;
        }
    }
}

long long que(int i, int j) {
    long long res = 0;
    for (int ii = i; ii >= 1; ii -= ii & -ii) {
        for (int jj = upper_bound(nodes[ii].begin(), nodes[ii].end(), j) - nodes[ii].begin(); jj >= 1; jj -= jj & -jj) {
            res += bit[ii][jj]; 
        }
    }
    return res;
}

long long que(int i1, int j1, int i2, int j2) {
    return que(i2, j2) - que(i2, j1 - 1)  - que(i1 - 1, j2) + que(i1 - 1, j1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> queries[i][0];
        if (queries[i][0] == 1) {
            for (int j = 1; j <= 3; j++) {
                cin >> queries[i][j];
            }
            cx.push_back(queries[i][1]);
            cy.push_back(queries[i][2]);
        } else {
            for (int j = 1; j <= 4; j++) {
                cin >> queries[i][j];
            }
            cx.push_back(queries[i][1]);
            cy.push_back(queries[i][2]);
            cx.push_back(queries[i][3]);
            cy.push_back(queries[i][4]);
        }
    }

    cx.push_back(INF);
    sort(cx.begin(), cx.end());
    cx.resize(unique(cx.begin(), cx.end()) - cx.begin());

    cy.push_back(INF);
    sort(cy.begin(), cy.end());
    cy.resize(unique(cy.begin(), cy.end()) - cy.begin());

    sz = cx.size();

    for (int i = 1; i <= q; i++) {
        queries[i][1] = lower_bound(cx.begin(), cx.end(), queries[i][1]) - cx.begin() + 1;
        queries[i][2] = lower_bound(cy.begin(), cy.end(), queries[i][2]) - cy.begin() + 1;
        
        if (queries[i][0] == 2) {
            queries[i][3] = lower_bound(cx.begin(), cx.end(), queries[i][3]) - cx.begin() + 1;
            queries[i][4] = lower_bound(cy.begin(), cy.end(), queries[i][4]) - cy.begin() + 1;
        }
    }

    nodes.resize(sz + 5);
    bit.resize(sz + 5);

    for (int i = 1; i <= q; i++) {
        if (queries[i][0] == 1) {
            fakeupd(queries[i][1], queries[i][2]);
        }
    }

    for (int i = 1; i <= sz; i++) {
        nodes[i].push_back(INF);
        sort(nodes[i].begin(), nodes[i].end());
        nodes[i].resize(unique(nodes[i].begin(), nodes[i].end()) - nodes[i].begin());
        bit[i].resize(nodes[i].size() + 1);
    }

    for (int i = 1; i <= q; i++) {
        if (queries[i][0] == 1) {
            upd(queries[i][1], queries[i][2], queries[i][3]);
        } else {
            cout << que(queries[i][1], queries[i][2], queries[i][3], queries[i][4]) << '\n';
        }
    }
}
