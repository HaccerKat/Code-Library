#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T>
T exgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    
    T x1, y1;
    T g = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - y1 * (a / b);
    return g;
}