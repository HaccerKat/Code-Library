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
    const int N = 200000;
    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        cout << rnd(1, 1e9) << " ";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}