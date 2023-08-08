
#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
template <class T>
struct Edge {
    int u, v;
    T cost, flow, cap;
    Edge() {}
    Edge(int u, int v, T cost, T cap) : u(u), v(v), cost(cost), flow(0), cap(cap) {} 
};

// Does not work if there is a negative cycle
// Solves in O(nm + Fm log n)
template <class T>
class MCMF {
public:
    T flowinf = 1e9;
    vector<Edge<T>> edges;
    vector<T> potential, dist, mnflow;
    vector<vector<int>> adj;
    vector<int> par;
    int n, m = 0, s, t;
    MCMF(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
    }
    
    void addedge(int u, int v, T cost, T cap) {
        edges.push_back(Edge(u, v, cost, cap));
        edges.push_back(Edge(v, u, -cost, 0));
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }
    
    bool spfa() {
        potential = vector<T>(n, flowinf);
        vector<int> cnt(n);
        vector<bool> inq(n);
        queue<int> q;
        q.push(s);
        inq[s] = 1, potential[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int id : adj[u]) {
                int v = edges[id].v;
                T c = edges[id].cost, f = edges[id].cap - edges[id].flow;
                if (potential[u] + c < potential[v] && f > 0) {
                    potential[v] = potential[u] + c;
                    if (!inq[v]) {
                        inq[v] = 1, cnt[v]++;
                        q.push(v);
                        if (cnt[v] > n) return 0;
                    }
                }
            }
        }
        
        return 1;
    }
    
    bool dij() {
        par = vector<int>(n, -1);
        dist = vector<T>(n, flowinf), mnflow = vector<T>(n);
        dist[s] = 0, mnflow[s] = flowinf;
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
        q.push({0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (dist[u] != d) continue;
            for (int id : adj[u]) {
                int v = edges[id].v;
                T c = edges[id].cost + potential[u] - potential[v];
                T f = edges[id].cap - edges[id].flow;
                if (f > 0 && d + c < dist[v]) {
                    dist[v] = d + c, par[v] = id, mnflow[v] = min(mnflow[u], f);
                    q.push({d + c, v});
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (dist[i] < flowinf) potential[i] += dist[i];
        }
        
        return dist[t] != flowinf;
    }
    
    // ty == 1 means that we must push as much flow as possible
    T flow(T mxf, bool ty) {
        T res = 0, curf = 0;
        bool ok = spfa();
        assert(ok);
        while (curf < mxf && dij()) {
            int v = t;
            T f = min(mxf - curf, mnflow[t]), add = 0;
            while (v != s) {
                int id = par[v];
                edges[id].flow += f, edges[id ^ 1].flow -= f;
                add += edges[id].cost * f;
                v = edges[id].u;
            }
            
            if (!ty && add > 0) break;            
            curf += f, res += add;
        }
        
        return res;
    }
};