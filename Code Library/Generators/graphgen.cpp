#include <bits/stdc++.h>
using namespace std;

#define int long long
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l = 0, int r = 1E9) {
    if(l > r) swap(l, r);
    return std::uniform_int_distribution<int>(l, r)(rng);
    // return std::uniform_real_distribution<long double>(l, r)(rng);
}

typedef pair<int, int> pi;
void testcase() {
    // change output and remove the adding extra edges part when generating a tree
    const int N = 10, M = 15;
    cout << N << " " << M << "\n";
    vector<int> perm(N);
    for (int i = 0; i < N; i++) {
        perm[i] = i;    
    }
    
    shuffle(perm.begin(), perm.end(), rng);
    set<pi> edges;
    for (int i = 1; i < N; i++) {
        edges.insert({rnd(0, i - 1), i});
    }
    
    for (int i = 0; i < M - N + 1; i++) {
        while (true) {
            int u = rnd(0, N - 1), v = rnd(0, N - 1);
            if (u != v && !edges.contains({u, v}) && !edges.contains({v, u})) {
                edges.insert({u, v});
                break;
            }
        }
    }
    
    for (auto [u, v] : edges) {
        cout << perm[u] + 1 << " " << perm[v] + 1 << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}