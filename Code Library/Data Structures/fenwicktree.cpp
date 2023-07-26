#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct BIT {
    // remember that the index cannot be zero
    // this template assumes that zero indexing is used for the original array
    int n;
    vector<T> bit;
    BIT(int n) {
        this->n = n;
        bit.resize(n + 1);
    }
    
    void update(int p, T x) {
        p++;
        for (; p <= n; p += p & (-p)) {
            bit[p] += x;
        }
    }
    
    T query(int p) {
        p++;
        T res = 0;
        for (; p > 0; p -= p & (-p)) {
            res += bit[p];
        }
        
        return res;
    }
    
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};