#include <bits/stdc++.h>
using namespace std;
template<class U> struct Segtree : public U {
    using T = typename U::T;
    int n;
    vector<T> t, a;
    Segtree(int n) : n(n), t(4 * n, U::neutral), a(n, U::neutral) {}
    Segtree(vector<T> b) : n(b.size()), t(4 * n, U::neutral), a(b) {
        build(1, 0, n - 1);
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {t[v] = a[tl]; return;}
        int mid = (tl + tr) / 2;
        build(v * 2, tl, mid);
        build(v * 2 + 1, mid + 1, tr);
        t[v] = U::merge(t[v * 2], t[v * 2 + 1]);
    }

    void update(int p, T x, int v, int tl, int tr) {
        if (tl == tr) {t[v] = x, a[tl] = x; return;}
        int mid = (tl + tr) / 2;
        if (p <= mid) update(p, x, v * 2, tl, mid);
        else update(p, x, v * 2 + 1, mid + 1, tr);
        t[v] = U::merge(t[v * 2], t[v * 2 + 1]);
    }

    T query(int ql, int qr, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return U::neutral;
        if (tl >= ql && tr <= qr) return t[v];
        int mid = (tl + tr) / 2;
        T l = query(ql, qr, v * 2, tl, mid);
        T r = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return U::merge(l, r);
    }

    int walkright(int ql, T &x, int v, int tl, int tr) {
        if (tr < ql) return n;
        if (tl >= ql && U::f(U::merge(x, t[v]))) {
            x = U::merge(x, t[v]);
            return n;
        }

        if (tl == tr) return tl;
        int mid = (tl + tr) / 2;
        int l = walkright(ql, x, v * 2, tl, mid);
        if (l != n) return l;
        return walkright(ql, x, v * 2 + 1, mid + 1, tr); 
    }

    int walkleft(int qr, T &x, int v, int tl, int tr) {
        if (tl > qr) return n;
        if (tr <= qr && U::f(U::merge(x, t[v]))) {
            x = U::merge(x, t[v]);
            return -1;
        }

        if (tl == tr) return tl;
        int mid = (tl + tr) / 2;
        int r = walkright(qr, x, v * 2 + 1, mid + 1, tr);
        if (r != -1) return r;
        return walkright(qr, x, v * 2, tl, mid); 
    }

    void update(int p, T x) {update(p, x, 1, 0, n - 1);}
    T query(int ql, int qr) {return query(ql, qr, 1, 0, n - 1);}
    int walkright(int ql) {
        T x = U::neutral; assert(U::f(x));
        return walkright(ql, x, 1, 0, n - 1);
    }

    int walkleft(int qr) {
        T x = U::neutral; assert(U::f(x));
        return walkright(qr, x, 1, 0, n - 1);
    }
};

int target;
struct MaxInt {
    using T = int;
    const T neutral = numeric_limits<int>::min();
    // value <-> value
    T merge(T a, T b) {
        return max(a, b);
    }

    // v = merge(t[l], t[l + 1]..., t[r - 1], t[r])
    // this example is used for find first >=
    bool f(T v) {
        return v < target;
    }
};