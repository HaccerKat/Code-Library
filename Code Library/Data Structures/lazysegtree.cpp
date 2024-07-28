#include <bits/stdc++.h>
using namespace std;
// supports range set and arbitrary lazy push functions
// w in this template equals the size of the range
template<class U> struct LazySegtree : public U {
    // V = value, T = tag, D = data
    using V = typename U::V;
    using T = typename U::T;
    typedef struct {
        int type; V set_val; T tag;
    } D;

    // 0 - set, 1 - apply, 2 - none
    D compose(D a, D b) {
        if (a.type == 2) return b;
        else if (b.type == 2) return a;
        else if (a.type == 0) return a;
        else if (b.type == 0) return D({0, U::apply(a.tag, b.set_val, 1), T()});
        else return D({1, V(), U::compose(a.tag, b.tag)});
    }

    int n, fake;
    vector<V> t, a;
    vector<D> lazy;
    LazySegtree(int n) : n(n), fake(4 * n - 1), t(4 * n, U::neutral), a(n, U::neutral) {
        lazy.resize(4 * n, D({2, V(), T()}));
    }

    LazySegtree(vector<V> b) : n(b.size()), fake(4 * n - 1), t(4 * n, U::neutral), a(b) {
        lazy.resize(4 * n, D({2, V(), T()}));
        build(1, 0, n - 1);
    } 

    void build(int v, int tl, int tr) {
        if (tl == tr) {t[v] = a[tl]; return;}
        int mid = (tl + tr) / 2;
        build(v * 2, tl, mid);
        build(v * 2 + 1, mid + 1, tr);
        t[v] = U::merge(t[v * 2], t[v * 2 + 1]);
    }

    void push(int u, int v, int w) {
        if (lazy[u].type == 0) {
            t[v] = U::mult(lazy[u].set_val, w);
            lazy[v] = lazy[u];
        }

        else if (lazy[u].type == 1) {
            t[v] = U::apply(lazy[u].tag, t[v], w);
            lazy[v] = compose(lazy[u], lazy[v]);
        }
    }

    void propagate(int v, int w1, int w2) {
        if (lazy[v].type == 2) return;
        push(v, v * 2, w1), push(v, v * 2 + 1, w2);
        lazy[v] = D({2, V(), T()});
    }

    V query(int ql, int qr, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return U::neutral;
        if (tl >= ql && tr <= qr) return t[v];
        int mid = (tl + tr) / 2;
        propagate(v, mid - tl + 1, tr - mid);
        V l = query(ql, qr, v * 2, tl, mid);
        V r = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return U::merge(l, r);
    }

    void apply(int ql, int qr, D x, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return;
        if (tl >= ql && tr <= qr) {
            lazy[fake] = x;
            push(fake, v, tr - tl + 1);
            return;
        }

        int mid = (tl + tr) / 2;
        propagate(v, mid - tl + 1, tr - mid);
        apply(ql, qr, x, v * 2, tl, mid);
        apply(ql, qr, x, v * 2 + 1, mid + 1, tr);
        t[v] = U::merge(t[v * 2], t[v * 2 + 1]);
    }

    int walkright(int ql, V &x, int v, int tl, int tr) {
        if (tr < ql) return n;
        if (tl >= ql && U::f(U::merge(x, t[v]))) {
            x = U::merge(x, t[v]);
            return n;
        }

        if (tl == tr) return tl;
        int mid = (tl + tr) / 2;
        propagate(v, mid - tl + 1, tr - mid);
        int l = walkright(ql, x, v * 2, tl, mid);
        if (l != n) return l;
        return walkright(ql, x, v * 2 + 1, mid + 1, tr); 
    }

    int walkleft(int qr, V &x, int v, int tl, int tr) {
        if (tl > qr) return n;
        if (tr <= qr && U::f(U::merge(x, t[v]))) {
            x = U::merge(x, t[v]);
            return -1;
        }

        if (tl == tr) return tl;
        int mid = (tl + tr) / 2;
        propagate(v, mid - tl + 1, tr - mid);
        int r = walkright(qr, x, v * 2 + 1, mid + 1, tr);
        if (r != -1) return r;
        return walkright(qr, x, v * 2, tl, mid); 
    }

    V query(int l, int r) {return query(l, r, 1, 0, n - 1);}
    void set(int l, int r, V x) {apply(l, r, D({0, x, T()}), 1, 0, n - 1);}
    void apply(int l, int r, T tag) {apply(l, r, D({1, V(), tag}), 1, 0, n - 1);}
    int walkright(int ql) {
        T x = U::neutral; assert(U::f(x));
        return walkright(ql, x, 1, 0, n - 1);
    }

    int walkleft(int qr) {
        T x = U::neutral; assert(U::f(x));
        return walkright(qr, x, 1, 0, n - 1);
    }
};

struct Value {
    ll inv = 0;
    int zeros = 0, ones = 0;
};

// n is equal to the range size in the segtree
// ignore if not useful
int target;
struct Inv {
    using V = Value;
    using T = bool;
    // identity element
    const V neutral = Value();
    // value <-> value
    V merge(V a, V b) {
        return {a.inv + b.inv + (ll)a.ones * b.zeros, a.zeros + b.zeros, a.ones + b.ones};
    }

    // setting n elements to a
    V mult(V a, int n) {
        return {0, a.zeros * n, a.ones * n};
    }

    // tag -> tag
    T compose(T a, T b) {
        return a ^ b;
    }

    // tag -> value
    V apply(T tag, V a, int n) {
        if (!tag) return a;
        return {(ll)a.zeros * a.ones - a.inv, a.ones, a.zeros};
    }  

    // v = merge(t[l], t[l + 1]..., t[r - 1], t[r])
    // this example is used for find first >= (must change other functions for that)
    bool f(T v) {
        return v < target;
    }
};