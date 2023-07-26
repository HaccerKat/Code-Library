// TODO: Make this better
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int inf = 1e9 + 5;
int n, qq;
vector<int> adj[N];
bool vis[N];
int a[N], sz[N], heavy[N], head[N], pos[N], parent[N], dep[N];
int cur = 0;
template <class T>
class pointsegtree {
public:
    bool ty;
    vector<T> t;
    pointsegtree(bool ty) {
        this->ty = ty;
        t.resize(n * 4);
    }
    
    T returnval() {
        if (ty == 0) return -inf;
        if (ty == 1) return 0;
        return -1;
    }
    
    T operation(T x, T y) {
        if (ty == 0) return max(x, y);
        else return x + y;
    }
    
    void update(int p, T x, int v = 1, int tl = 0, int tr = n - 1) {
        if (tl == tr) {
            t[v] = x;
            return;
        }
        
        int mid = (tl + tr) / 2;
        if (p <= mid) update(p, x, v * 2, tl, mid);
        else update(p, x, v * 2 + 1, mid + 1, tr);
        t[v] = operation(t[v * 2], t[v * 2 + 1]);
    }
    
    T query(int ql, int qr, int v = 1, int tl = 0, int tr = n - 1) {
        assert(ql <= qr);
        if (tl > qr || tr < ql) return returnval();
        if (tl >= ql && tr <= qr) {
            return t[v];
        }
        
        int mid = (tl + tr) / 2;
        T left = query(ql, qr, v * 2, tl, mid);
        T right = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return operation(left, right);
    }
};

void dfs(int u) {
    vis[u] = true, sz[u] = 1;
    int heavysz = 0;
    for (int v : adj[u]) {
        if (!vis[v]) {
            parent[v] = u, dep[v] = dep[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > heavysz) {
                heavysz = sz[v], heavy[u] = v;
            }
        }
    }
}

void decomp(int u, int h) {
    head[u] = h, pos[u] = cur++, vis[u] = true;
    if (heavy[u] != -1) decomp(heavy[u], h);
    for (int v : adj[u]) {
        if (!vis[v] && heavy[u] != v) {
            decomp(v, v);
        }
    }
}

void decomp() {
    memset(heavy, -1, sizeof(heavy));
    dfs(0);
    memset(vis, false, sizeof(vis));
    decomp(0, 0);
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    decomp();
    pointsegtree<int> stmax(0);
    pointsegtree<ll> stsum(1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        stmax.update(pos[i], a[i]);
        stsum.update(pos[i], a[i]);
    }
    
    cin >> qq;
    auto query = [&](int u, int v, bool ty) {
        ll res = (ty == 0 ? -inf : 0);
        for (; head[u] != head[v]; u = parent[head[u]]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            if (ty == 0) res = max(res, (ll)stmax.query(pos[head[u]], pos[u]));
            else res += stsum.query(pos[head[u]], pos[u]);
        }
        
        if (dep[u] < dep[v]) swap(u, v);
        if (ty == 0) res = max(res, (ll)stmax.query(pos[v], pos[u]));
        else res += stsum.query(pos[v], pos[u]);
        return res;
    };
}