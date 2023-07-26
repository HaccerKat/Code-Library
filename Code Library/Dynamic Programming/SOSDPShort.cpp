#include <bits/stdc++.h>
using namespace std;

const int N = 5;
int a[1 << N], f[1 << N];
int n;
void calc() {
    // calculates the sum of all a[subset of mask] for all mask that is memory optimized
    // cannot easily be used when the masks must be computed in order
    for (int mask = 0; mask < (1 << n); mask++) {
        f[mask] = a[mask];
    }
    
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                f[mask] += f[mask ^ (1 << i)];
            }
        }
    }
}