#include <bits/stdc++.h>
using namespace std;
const int N = 200001;
const int LOG = 19;
vector<int> adj[N];
int dep[N], tin[N], logA[N], rmq[N * 2][LOG];
bool vis[N];
vector<int> euler;
int timer = 0;
void dfs(int u) {
    vis[u] = true, tin[u] = timer++;
    euler.push_back(u);
    for (int v : adj[u]) {
        if (!vis[v]) {
            dep[v] = dep[u] + 1;
            dfs(v);
            euler.push_back(u);
            timer++;
        }
    }
}

void precomp() {
    int sz = euler.size();
    for (int i = 2; i <= sz; i++) logA[i] = logA[i >> 1] + 1;
    for (int i = 0; i < sz; i++) {
        rmq[i][0] = euler[i];
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i + (1 << j) <= sz; i++) {
            int x = (1 << j - 1);
            int lx = dep[rmq[i][j - 1]], rx = dep[rmq[i + x][j - 1]];
            rmq[i][j] = (lx < rx ? rmq[i][j - 1] : rmq[i + x][j - 1]);
        }
    }
}

int getlca(int u, int v) {
    int l = tin[u], r = tin[v];
    if (l > r) swap(l, r);
    int len = r - l + 1;
    int lg = logA[len], x = 1 << lg;
    int lx = dep[rmq[l][lg]], rx = dep[rmq[r - x + 1][lg]];
    return (lx < rx ? rmq[l][lg] : rmq[r - x + 1][lg]);
}

int getdist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[getlca(u, v)];
}