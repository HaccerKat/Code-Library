// Solution for https://dmoj.ca/problem/ds5easy
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int LOG = 20;
const ll inf = 1e18;
struct Node {
    int ch[2] = {0, 0}, p = 0, pathp = 0, sz = 0, idx = 0;
    ll mn = inf, mx = -inf, val = 0, sum = 0, lazyadd = 0, lazyval = inf;
    bool lazy = false;
    Node() {}
    Node(int idx, int x) : sz(1), mn(x), mx(x), sum(x), val(x), idx(idx) {}
};

int root = 1;
// node 0 is a dummy node that is empty at all times
// node (N - 1) is a dummy node for pushing
Node a[N];
int n, m, k, qq;
int dir(int u) {
    if (!a[u].p) return -1;
    if (a[a[u].p].ch[0] == u) return 0;
    else return 1;
}

void pull(int u, int v) {
    a[u].mn = min(a[u].mn, a[v].mn), a[u].mx = max(a[u].mx, a[v].mx);
    a[u].sum += a[v].sum, a[u].sz += a[v].sz;
}

void pullup(int u) {
    a[u].sum = a[u].mn = a[u].mx = a[u].val, a[u].sz = 1;
    pull(u, a[u].ch[0]);
    pull(u, a[u].ch[1]);
}

void push(int u, int v) {
    ll x = a[u].lazyval;
    if (x != inf) {
        a[v].val = a[v].mn = a[v].mx = a[v].lazyval = x, a[v].sum = a[v].sz * x;
        a[v].lazyadd = 0;
    }
    
    x = a[u].lazyadd;
    a[v].val += x, a[v].mn += x, a[v].mx += x, a[v].lazyadd += x, a[v].sum += a[v].sz * x;
    a[v].lazy ^= a[u].lazy;
}

void prop(int u) {
    if (a[u].lazy) swap(a[u].ch[0], a[u].ch[1]);
    if (a[u].ch[0]) push(u, a[u].ch[0]);
    if (a[u].ch[1]) push(u, a[u].ch[1]);
    a[u].lazyadd = 0, a[u].lazyval = inf, a[u].lazy = 0;
}

void addedge(int u, int v, int d) {
    if (u != 0) a[u].ch[d] = v;
    if (v != 0) a[v].p = u;
}

void rot(int u) {
    int v = a[u].p;
    int du = dir(u), dv = dir(v);
    int vv = a[v].p, c = a[u].ch[du ^ 1];
    addedge(v, c, du);
    addedge(u, v, du ^ 1);
    addedge(vv, u, dv);
    pullup(v);
    pullup(u);
    a[u].pathp = a[v].pathp;
}

void splay(int u) {
    int w = u;
    vector<int> path;
    while (w) {
        path.push_back(w);
        w = a[w].p;    
    }
    
    reverse(path.begin(), path.end());
    for (int x : path) prop(x);
    while (dir(u) != -1) {
        int v = a[u].p;
        int du = dir(u), dv = dir(v);
        if (dv != -1) rot(du == dv ? v : u);
        rot(u);
    }
}

// find by index in a splay tree
int find(int u, int x) {
    prop(u);
    int sz = a[a[u].ch[0]].sz;
    if (!u) return 0;
    else if (sz > x) return find(a[u].ch[0], x);
    else if (sz == x) return u;
    else return find(a[u].ch[1], x - sz - 1);
}

void merge(int u, int v) {
    splay(u);
    addedge(u, v, 1);
    pull(u, v);
}

// cuts off right child
// use swaps when cutting off left child
void split(int u, bool makepathp = false) {
    splay(u);
    int c = a[u].ch[1];
    if (makepathp && c) a[c].pathp = u;
    a[u].ch[1] = 0, a[c].p = 0;
    pullup(u);
}

int access(int u) {
    int w = u, v = u;
    split(u, true);
    while (a[u].pathp != 0) {
        v = a[u].pathp;
        split(v, true);
        merge(v, u);
        a[u].pathp = 0, u = v;
    }
    
    splay(w);
    return v;
}

void reroot(int u) {
    access(u);
    a[u].lazy ^= 1;
}

int findroot(int u) {
    access(u);
    return find(u, 0);
}

void link(int u, int v) {
    assert(findroot(u) != findroot(v));
    reroot(u);
    a[u].pathp = v;
}

void cut(int u, int v) {
    reroot(u);
    access(v);
    swap(a[v].ch[0], a[v].ch[1]);
    split(v);
    swap(a[v].ch[0], a[v].ch[1]);
}

int getlca(int u, int v) {
    reroot(root);
    access(u);
    return access(v);
}

void update(int u, int v, ll x, bool t) {
    reroot(u);
    access(v);
    if (t == 0) a[N - 1].lazyval = x;
    else a[N - 1].lazyadd = x;
    push(N - 1, v);
    a[N - 1].lazyval = inf, a[N - 1].lazyadd = 0;
}

ll query(int u, int v, int t) {
    reroot(u);
    access(v);
    if (t == 0) return a[v].mn;
    else if (t == 1) return a[v].mx;
    else return a[v].sum;
}

void changepar(int u, int v) {
    int lca = getlca(u, v);
    if (lca == u) return;
    access(u);
    int w = a[u].ch[0];
    while (a[w].ch[1] != 0) {
        w = a[w].ch[1];
    }
    
    cut(w, u);
    link(u, v);
}

int b[N];
void solve() {
    cin >> n >> qq;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        a[i] = Node(i, b[i]);
    }
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        link(u, v);
    }
    
    cin >> root;
    for (int i = 0; i < qq; i++) {
        int t, u, v, z;
        cin >> t >> u;
        if (t == 0) {
            root = u;
            continue;
        }
        
        cin >> v;
        if (t == 1) {
            cin >> z;
            update(u, v, z, 0);
        }
        
        if (t == 2) {
            cin >> z;
            update(u, v, z, 1);
        }
        
        if (t == 3) {
            cout << query(u, v, 0) << "\n";
        }
        
        if (t == 4) {
            cout << query(u, v, 1) << "\n";
        }
        
        if (t == 5) {
            cout << query(u, v, 2) << "\n";
        }
        
        if (t == 6) {
            changepar(u, v);
        }
        
        if (t == 7) {
            cout << getlca(u, v) << "\n";
        }
    }    
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}