#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const int mod = 1000000007;
// const int N = 500;
const int N = 20000005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
int ch[N][2], priority[N], sz[N], lazy[N], roots[N];
ll val[N], sum[N], a[N];
int cur = 1, ti = 1;
void prop(int u) {
    if (lazy[u]) swap(ch[u][0], ch[u][1]);
    lazy[ch[u][0]] ^= lazy[u], lazy[ch[u][1]] ^= lazy[u], lazy[u] = 0;
}

void pull(int u) {
    int l = ch[u][0], r = ch[u][1];
    sz[u] = sz[l] + sz[r] + 1, sum[u] = sum[l] + sum[r] + val[u];
}

int copynode(int u) {
    int v = cur++;
    ch[v][0] = ch[u][0], ch[v][1] = ch[u][1], priority[v] = priority[u];
    sz[v] = sz[u], lazy[v] = lazy[u], val[v] = val[u], sum[v] = sum[u];
    return v;
}

int copy(int u) {
    int v = copynode(u);
    if (ch[v][0] != 0) ch[v][0] = copynode(ch[u][0]);
    if (ch[v][1] != 0) ch[v][1] = copynode(ch[u][1]);
    return v;
}

pi split(int p, int u, int idx = 0) {
    pi nodes = {0, 0};
    if (u == 0) return nodes;
    int v = copy(u);
    prop(v);
    if (idx + sz[ch[v][0]] <= p) {
        auto [lv, rv] = split(p, ch[v][1], idx + sz[ch[v][0]] + 1);
        ch[v][1] = lv, nodes = {v, rv};
    }
    
    else {
        auto [lv, rv] = split(p, ch[v][0], idx);
        ch[v][0] = rv, nodes = {lv, v};
    }
    
    pull(v);
    return nodes;
}

array<int, 3> splitthree(int l, int r, int ver) {
    auto [lv, mrv] = split(l - 1, roots[ver]);
    auto [mv, rv] = split(r - l, mrv);
    return {lv, mv, rv};
}

//lower value for priority is higher priority
int merge(int u, int v) {
    if (u == 0) return v;
    if (v == 0) return u;
    int w = (priority[u] < priority[v] ? u : v);
    if (priority[u] < priority[v]) {
        prop(w);
        ch[w][1] = merge(ch[w][1], v);
    }
    
    else {
        prop(w);
        ch[w][0] = merge(u, ch[w][0]);
    }
    
    pull(w);
    return w;
}

void rev(int l, int r, int ver) {
    auto [lv, mv, rv] = splitthree(l, r, ver);
    lazy[mv] ^= 1;
    roots[ti] = merge(merge(lv, mv), rv);
}

ll query(int l, int r, int ver) {
    auto [lv, mv, rv] = splitthree(l, r, ver);
    ll res = sum[mv];
    roots[ti] = merge(merge(lv, mv), rv);
    return res;
}

void ins(int p, ll x, int ver) {
    int id = cur++;
    val[id] = x, sum[id] = x, sz[id] = 1;
    auto [lv, rv] = split(p - 1, roots[ver]);
    roots[ti] = merge(merge(lv, id), rv);
}

void del(int p, int ver) {
    auto [lv, mv, rv] = splitthree(p, p, ver);
    roots[ti] = merge(lv, rv);
}

int n, m, k, qq;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve() {
    cin >> qq;
    for (int i = 0; i < N; i++) {
        priority[i] = i;
    }
    
    shuffle(priority, priority + N, rng);
    ll lastans = 0;    
    for (; ti <= qq; ti++) {
        int ver, t;
        cin >> ver >> t;
        if (t == 1) {
            ll i, x;
            cin >> i >> x;
            i ^= lastans, x ^= lastans;
            ins(i, x, ver);
        }
        
        else if (t == 2) {
            ll i;
            cin >> i;
            i ^= lastans;
            i--;
            del(i, ver);
        }
        
        else if (t == 3) {
            ll l, r;
            cin >> l >> r;
            l ^= lastans, r ^= lastans;
            l--, r--;
            rev(l, r, ver);
        }
        
        else {
            ll l, r;
            cin >> l >> r;
            l ^= lastans, r ^= lastans;
            l--, r--;
            lastans = query(l, r, ver);
            cout << lastans << "\n";
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}