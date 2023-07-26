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
    const int N = 10;
    cout << N << "\n";
    vector<int> perm(N);
    for (int i = 0; i < N; i++) {
        perm[i] = i;    
    }
    
    shuffle(perm.begin(), perm.end(), rng);
    set<pi> edges;
    for (int i = 1; i < N; i++) {
        edges.insert({rnd(0, i - 1), i});
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