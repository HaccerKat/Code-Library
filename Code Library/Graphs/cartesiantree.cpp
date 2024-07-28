#include "bits/stdc++.h"
#ifdef DEBUG
#include "algo/debug.hpp"
#else
#define dbg(...)
#define dbgm(...)
#endif
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
// using u128 = __uint128_t;
// using i128 = __int128;
const int mod = 1000000007;
const int N = 1000005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
int n, m, k, qq;
struct Node {
    int p, l, r;
};

int a[N];
Node tree[N];
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tree[i] = {n, n, n};
    }

    tree[n] = {n, n, n};
    for (int i = 0; i < n; i++) {
        tree[i].p = i ? i - 1 : n;
        while (a[tree[i].p] > a[i]) {
            tree[i].p = tree[tree[i].p].p;
        }

        tree[i].l = tree[tree[i].p].r;
        tree[tree[i].l].p = i;
        tree[tree[i].p].r = i;
    }

    for (int i = 0; i < n; i++) {
        cout << (tree[i].p == n ? i : tree[i].p) << " ";
    }

    cout << "\n";
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}