#include <bits/stdc++.h>
using namespace std;
template<class U> struct ZKW : public U {
    using T = typename U::T;
    int n;
    vector<T> t, a;
    ZKW(int n) : n(n), t(2 * n, U::neutral), a(n, U::neutral) {}
    ZKW(vector<T> b) : n(b.size()), t(2 * n, U::neutral), a(b) {build();}
    void build() {
        for (int i = 2 * n - 1; i >= n; i--) t[i] = a[i - n];
        for (int i = n - 1; i >= 0; i--) t[i] = t[i] = U::merge(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, T x) {
        for (t[i += n] = x; i >>= 1;) t[i] = U::merge(t[i << 1], t[i << 1 | 1]);
    }

    T query(int l, int r) {
        T lv = U::neutral, rv = U::neutral;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lv = U::merge(lv, t[l++]);
            if (r & 1) rv = U::merge(t[--r], rv);
        }

        return U::merge(lv, rv);
    }
};

struct Add {
    using T = int;
    const T neutral = 0;
    T merge(T a, T b) {
        return a + b;
    }
};