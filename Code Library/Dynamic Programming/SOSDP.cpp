#include <bits/stdc++.h>
using namespace std;

const int N = 5;
int a[1 << N], dp[1 << N][N + 1], f[1 << N];
int n;
void calc() {
    // calculates the sum of all a[subset of mask] for all mask
    // the second dp state means that the first i bits are allowed to differ from mask
    for (int mask = 0; mask < (1 << n); mask++) {
        dp[mask][0] = a[mask];
        for (int i = 1; i <= n; i++) {
            if ((mask >> i) & 1) {
                dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << (i - 1))][i - 1];
            }
            
            else {
                dp[mask][i] = dp[mask][i - 1];
            }
        }
        
        f[mask] = dp[mask][n];
    }
}