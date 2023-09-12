#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
// 0 = 2CC, 1 = SCC
// ids and components are in topological order (SCC)
// adjscc does not include edges going up the tree (2CC)
class SCC {
public:
    int timer = 0, cntcomps = 0, n, dagedges = 0;
    bool directed;
    vector<pi> edges;
    vector<vector<int>> adj, comps, adjscc;
    vector<int> tin, low, id, sz;
    vector<bool> onstk;
    stack<int> stk;
    SCC() {}
    SCC(int n, bool directed) {
        this->n = n, this->directed = directed;
        adj.resize(n);
    }
    
    void calc() {
        comps = adjscc = vector<vector<int>>(n);
        tin = low = id = vector<int>(n, -1);
        sz = vector<int>(n);
        onstk = vector<bool>(n);
        for (int i = 0; i < n; i++) {
            if (tin[i] == -1) dfs(i);
        }
        
        reverse(comps.begin(), comps.begin() + cntcomps);
        for (int i = 0; i < n; i++) {
            id[i] = cntcomps - id[i] - 1;
            sz[id[i]]++;
        }
        
        for (auto [u, v] : edges) {
            if (id[u] < id[v]) {
                adjscc[id[u]].push_back(id[v]);
                dagedges++;
            }
        }
    }
    
    void dfs(int u, int p = -1) {
        tin[u] = low[u] = timer++;
        onstk[u] = 1;
        stk.push(u);
        for (int v : adj[u]) {
            if (!directed && v == p) {
                p = -1;
                continue;
            }
            
            if (tin[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            }
            
            else if (onstk[v]) {
                low[u] = min(low[u], tin[v]);
            }
        }
        
        if (tin[u] == low[u]) {
            while (true) {
                int v = stk.top();
                stk.pop();
                onstk[v] = 0, id[v] = cntcomps;
                comps[cntcomps].push_back(v);
                if (u == v) break;
            }
            
            cntcomps++;
        }
    }
    
    void addedge(int u, int v) {
        adj[u].push_back(v), edges.push_back({u, v});
        if (!directed) adj[v].push_back(u), edges.push_back({v, u});
    }
};