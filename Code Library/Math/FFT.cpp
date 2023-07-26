#include <bits/stdc++.h>
using namespace std;
typedef complex<long double> Z;
const long double PI = acos(-1);
void FFT(vector<Z> &f, bool ifft = false) {
    int sz = f.size();
    if (sz == 1) return;
    long double theta = (ifft ? -1 : 1) * 2 * PI / sz;
    Z omega = Z(cos(theta), sin(theta));
    vector<Z> even(sz / 2), odd(sz / 2);
    for (int i = 0; i < sz / 2; i++) {
        even[i] = f[2 * i], odd[i] = f[2 * i + 1];
    }
    
    FFT(even, ifft);
    FFT(odd, ifft);
    Z cur = 1;
    for (int i = 0; i < sz / 2; i++) {
        f[i] = even[i] + cur * odd[i];
        f[i + sz / 2] = even[i] - cur * odd[i];
        if (ifft) f[i] /= 2, f[i + sz / 2] /= 2;
        cur *= omega;
    }
}