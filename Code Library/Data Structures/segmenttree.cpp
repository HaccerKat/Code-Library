#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
template <class T>
class lazysegtree {
public:
    int ty, n;
    vector<T> t, op;
    lazysegtree(int ty, int n) {
        this->ty = ty;
        this->n = n;
        t.resize(n * 4);
        op.resize(n * 4);
    }
    
    T operation(T x, T y) {
        if (ty == 0) return min(x, y);
        else if (ty == 1) return max(x, y);
        else return x + y;
    }
    
    T returnval() {
        if (ty == 0) return inf;
        else if (ty == 1) return -inf;
        else return 0;
    }
    
    // MAKE CHANGES FIRST!
    void propogate(int v, int l, int r) {
        // if (op[v] == inf) return;
        // int mid = (l + r) / 2;
        // op[v * 2] = op[v], op[v * 2 + 1] = op[v];
        // if (ty != 2) t[v * 2] = op[v], t[v * 2 + 1] = op[v];
        // else t[v * 2] = op[v] * (mid - l + 1), t[v * 2 + 1] = op[v] * (r - mid);
        // op[v] = inf;
    }
    
    void update(int ql, int qr, T x, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return;
        // MAKE CHANGES FIRST!
        if (tl >= ql && tr <= qr) {
            // if (ty != 2) t[v] = x;
            // else t[v] = x * (tr - tl + 1);
            // op[v] = x;
            return;
        }
        
        propogate(v, tl, tr);
        int mid = (tl + tr) / 2;
        update(ql, qr, x, v * 2, tl, mid);
        update(ql, qr, x, v * 2 + 1, mid + 1, tr);
        t[v] = operation(t[v * 2], t[v * 2 + 1]);
    }
    
    void update(int ql, int qr, T x) {
        update(ql, qr, x, 1, 0, n - 1);
    }
    
    T query(int ql, int qr, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return returnval();
        if (tl >= ql && tr <= qr) {
            return t[v];
        }
        
        propogate(v, tl, tr);
        int mid = (tl + tr) / 2;
        T left = query(ql, qr, v * 2, tl, mid);
        T right = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return operation(left, right);
    }
    
    T query(int ql, int qr) {
        return query(ql, qr, 1, 0, n - 1);
    }
    
    // ty = 0 -> returns the leftmost value in range that is smaller than x
    // ty = 1 -> returns the leftmost value in range that is larger than x
    int findfirst(int ql, int qr, T x, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return -1;
        if (ty == 0 && t[v] >= x) return -1;
        if (ty == 1 && t[v] <= x) return -1;
        if (tl == tr) return tl;
        propogate();
        int mid = (tl + tr) / 2;
        int left = findfirst(ql, qr, x, v * 2, tl, mid);
        if (left != -1) return left;
        else return findfirst(ql, qr, x, v * 2 + 1, mid + 1, tr);
    }
    
    int findfirst(int ql, int qr, T x) {
        return findfirst(ql, qr, x, 1, 0, n - 1);
    }
};

template <class T>
class pointsegtree {
public:
    int ty, n;
    vector<T> t;
    pointsegtree(bool ty, int n) {
        this->ty = ty;
        this->n = n;
        t.resize(n * 4);
    }
    
    T returnval() {
        if (ty == 0) return inf;
        else if (ty == 1) return -inf;
        else return 0;
    }
    
    T operation(T x, T y) {
        if (ty == 0) return min(x, y);
        else if (ty == 1) return max(x, y);
        else return x + y;
    }
    
    void update(int p, T x, int v, int tl, int tr) {
        // MAKE CHANGES FIRST!
        if (tl == tr) {
            // t[v] = x;
            return;
        }
        
        int mid = (tl + tr) / 2;
        if (p <= mid) update(p, x, v * 2, tl, mid);
        else update(p, x, v * 2 + 1, mid + 1, tr);
        t[v] = operation(t[v * 2], t[v * 2 + 1]);
    }
    
    void update(int p, T x) {
        update(p, x, 1, 0, n - 1);
    }
    
    T query(int ql, int qr, int v, int tl, int tr) {
        if (tl > qr || tr < ql || ql > qr) return returnval();
        if (tl >= ql && tr <= qr) {
            return t[v];
        }
        
        int mid = (tl + tr) / 2;
        T left = query(ql, qr, v * 2, tl, mid);
        T right = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return operation(left, right);
    }
    
    T query(int ql, int qr) {
        return query(ql, qr, 1, 0, n - 1);
    }
};