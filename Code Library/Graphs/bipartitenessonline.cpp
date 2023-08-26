#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
class DSU {
vector<pi> parent;
vector<int> sz;
public:
    DSU(int n) {
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = {i, 0}, sz[i] = 1;
        }
    }
    
    pi findset(int u) {
        if (u != parent[u].first) {
            auto [v, p] = parent[u];
            parent[u] = findset(v);
            parent[u].second ^= p;
        }
        
        return parent[u];
    }
 
    bool unionset(int u, int v) {
        auto [a, ap] = findset(u);
        auto [b, bp] = findset(v);
        if (a == b) {
            if (ap == bp) return 0;    
        }
        
        else {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = {a, ap ^ bp ^ 1};
            sz[a] += sz[b];
        }
        
        return 1;
    }
};