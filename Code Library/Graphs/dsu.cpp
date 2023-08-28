#include <bits/stdc++.h>
using namespace std;
class DSU {
vector<int> parent, sz;
public:
    DSU(int n) {
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i, sz[i] = 1;
        }
    }
    
    int findset(int u) {
        if (u == parent[u]) return u;
        return parent[u] = findset(parent[u]);
    }
 
    void unionset(int u, int v) {
        int a = findset(u), b = findset(v);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};