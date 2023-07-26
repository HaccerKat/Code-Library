#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int mod = 1e9 + 7;
template<class T>
T power(T b, ll p) {
    T res = 1;
    for (; p; p >>= 1, b *= b) {
        if (p & 1) res *= b;
    }
    
    return res;
}
    
class Mint {
public:
    ll x;
    Mint() : x(0) {}
    Mint(ll x) : x((x % mod + mod) % mod) {}
    Mint &operator += (Mint rhs) {
        x += rhs.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    
    Mint &operator -= (Mint rhs) {
        x -= rhs.x;
        if (x < 0) x += mod;
        return *this;
    }
    
    Mint &operator *= (Mint rhs) {
        x *= rhs.x;
        x %= mod;
        return *this;
    }
    
    friend Mint &operator + (Mint lhs, Mint rhs) {return lhs += rhs;}
    friend Mint &operator - (Mint lhs, Mint rhs) {return lhs -= rhs;}
    friend Mint &operator * (Mint lhs, Mint rhs) {return lhs *= rhs;}
    Mint &operator /= (Mint rhs) {return *this * power(rhs, mod - 2);}
    friend Mint &operator / (Mint lhs, Mint rhs) {return lhs /= rhs;}
};