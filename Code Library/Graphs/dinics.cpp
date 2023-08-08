#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
template <class T>
struct Edge {
    int u, v;
    T flow, cap;
    Edge() {}
    Edge(int u, int v, T cap) : u(u), v(v), flow(0), cap(cap) {} 
};

template <class T>
class Dinics {
public:
    T flowinf = 1e9;
    vector<Edge<T>> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    int n, m = 0, s, t;
    Dinics(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
    
    void addedge(int u, int v, T cap) {
        edges.push_back(Edge(u, v, cap));
        edges.push_back(Edge(v, u, 0));
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }
    
    bool bfs() {
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                int v = edges[id].v;
                if (edges[id].cap - edges[id].flow == 0) continue;
                if (level[v] > level[u] + 1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        
        return level[t] != inf;
    }
    
    T dfs(int u, T mn) {
        if (u == t) return mn;
        for (int &idx = ptr[u]; idx < adj[u].size(); idx++) {
            int id = adj[u][idx], v = edges[id].v;
            T pushflow = edges[id].cap - edges[id].flow;
            if (pushflow == 0 || level[v] != level[u] + 1) continue;
            T pushed = dfs(v, min(mn, pushflow));
            if (pushed == 0) continue;
            edges[id].flow += pushed, edges[id ^ 1].flow -= pushed;
            return pushed;
        }
        
        return 0;
    }
    
    T flow() {
        T res = 0;
        while (true) {
            level = vector<int>(n, inf);
            level[s] = 0;
            ptr = vector<int>(n, 0);
            if (!bfs()) break;
            while (true) {
                T pushed = dfs(s, flowinf);
                if (pushed == 0) break;
                res += pushed;
            }
        }
        
        return res;
    }
};