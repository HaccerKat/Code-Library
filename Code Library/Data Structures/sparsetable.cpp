#include <bits/stdc++.h>
using namespace std;
template<class U> struct RMQ : public U {
    using T = typename U::T;
    int n, LOG;
    vector<T> a;
    vector<vector<T>> t;
    RMQ(vector<T> b) : n(b.size()), a(b) {
        LOG = __lg(n) + 1;
        t = vector<vector<T>>(LOG, vector<T>(n));
        t[0] = a;
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                t[i][j] = U::merge(t[i - 1][j], t[i - 1][j + (1 << i - 1)]);
            }
        }
    }

    T query(int l, int r) {
        int sz = r - l + 1;
        int lg = __lg(sz);
        return U::merge(t[lg][l], t[lg][r - (1 << lg) + 1]);
    }
};

struct Min {
    using T = int;
    T merge(T a, T b) {
        return min(a, b);
    }
};