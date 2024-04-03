#include <bits/stdc++.h>
using namespace std;
class BCC {
public:
    int timer = 0, cntcomps = 0, n;
    vector<vector<int>> adj, comps;
    vector<int> tin, low;
    stack<int> stk;
    BCC() {}
    BCC(int n) {
        this->n = n;
        adj.resize(n);
    }
    
    void calc() {
        comps = vector<vector<int>>(n);
        tin = low = vector<int>(n, -1);
        for (int i = 0; i < n; i++) {
            if (tin[i] == -1) dfs(i);
        }
    }
    
    void dfs(int u, int p = -1) {
        tin[u] = low[u] = timer++;
        stk.push(u);
        for (int v : adj[u]) {
            if (v == p) {
                p = -1;
                continue;
            }
            
            if (tin[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= tin[u]) {
                    while (true) {
                        int w = stk.top();
                        stk.pop();
                        comps[cntcomps].push_back(w);
                        if (v == w) break;
                    }
                    
                    comps[cntcomps++].push_back(u);
                }
            }
            
            else {
                low[u] = min(low[u], tin[v]);
            }
        }
        
        if (adj[u].empty()) {
            comps[cntcomps++].push_back(u);
        }
    }
    
    void addedge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};