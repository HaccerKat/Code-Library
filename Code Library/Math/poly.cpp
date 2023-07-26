#include <bits/stdc++.h>
using namespace std;
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}
 
template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
 
  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
 
  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
 
  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }
 
  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }
 
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }
 
  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
 
  friend const Type& abs(const Modular& x) { return x.value; }
 
  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);
 
 private:
  Type value;
};
 
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
 
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
 
template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }
 
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
 
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
 
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
 
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
 
template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}
 
template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}
 
template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}
 
// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
  return stream << number();
}
 
// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}
 
/*
using ModType = int;
 
struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/
 
constexpr int md = (int) 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
 
/*vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);
 
Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}*/

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
// using u128 = __uint128_t;
// using i128 = __int128;
const int mod = 1000000007;
const int N = 200005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
const Mint root = 3, invroot = (Mint)1 / 3, invtwo = (Mint)1 / 2;
int nxtpow(int n) {
    int x = 1;
    while (x < n) x <<= 1;
    return x;
}

void FFT(vector<Mint> &a, bool ifft = false) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int b = n >> 1;
        for (; j & b; b >>= 1) {
            j ^= b;
        }
        
        j ^= b;
        if (i < j) swap(a[i], a[j]);
    }
    
    for (int len = 1; len <= n / 2; len <<= 1) {
        Mint mul = power((ifft ? invroot : root), md / len / 2);
        for (int i = 0; i < n; i += len * 2) {
            Mint cur = 1;
            for (int j = i; j < i + len; j++) {
                Mint x = a[j], y = a[j + len] * cur;
                a[j] = x + y, a[j + len] = x - y;
                if (ifft) a[j] *= invtwo, a[j + len] *= invtwo;
                cur *= mul;
            }
        }
    }
}

void conv(vector<Mint> &a, vector<Mint> b) {
    int n = nxtpow(a.size() + b.size() - 1);
    a.resize(n);
    b.resize(n);
    FFT(a);
    FFT(b);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    
    FFT(a, true);
}

void mulslow(vector<Mint> &a, vector<Mint> b) {
    int n = a.size(), m = b.size();
    vector<Mint> c(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    
    a = c;
}

// magic
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l = 0, int r = md - 1) {
    return uniform_int_distribution<int>(l, r)(rng);
}

bool check(Mint x) {
    return power(x, (md - 1) / 2) == 1;
}

pair<Mint, Mint> mul(Mint a, Mint b, Mint c, Mint d, Mint x) {
    Mint e = a * c + b * d * x, f = b * c + a * d;
    return {e, f};
}

pair<Mint, bool> cipolla(Mint x) {
    if (x == 0) return {0, true};
    if (!check(x)) return {0, false};
    while (true) {
        Mint a = rnd();
        if (!check(a)) continue;
        int cur = (md + 1) / 2;
        Mint b = 1, y = a * a - x, resa = 1, resb = 0;
        if (check(y)) continue;
        while (cur > 0) {
            if (cur & 1) {
                auto [e, f] = mul(a, b, resa, resb, y);
                resa = e, resb = f;
            }
            
            auto [e, f] = mul(a, b, a, b, y);
            a = e, b = f;
            cur >>= 1;
        }
        
        return {resa, true};
    }
}

struct Poly {
    vector<Mint> a;
    Poly() {}
    Poly(Mint x) : a({x}) {}
    Poly(vector<Mint> a) : a(a) {}
    void normalize() {
        while (!a.empty() && a.back() == 0) {
            a.pop_back();
        }
    }
    
    void resz(int n) {
        a.resize(n);
    }
    
    void print() {
        for (Mint x : a) {
            cout << x << " ";
        }
        
        cout << "\n";
    }
    
    Poly operator -() {
        for (int i = 0; i < a.size(); i++) {
            a[i] = -a[i];
        }
        
        return *this;
    }
    
    Poly operator += (const Poly &b) {
        a.resize(max(a.size(), b.a.size()));
        for (int i = 0; i < b.a.size(); i++) {
            a[i] += b.a[i];
        }
        
        normalize();
        return *this;
    }
    
    Poly operator -= (const Poly &b) {
        a.resize(max(a.size(), b.a.size()));
        for (int i = 0; i < b.a.size(); i++) {
            a[i] -= b.a[i];
        }
        
        normalize();
        return *this;   
    }
    
    Poly operator + (const Poly &b) {return Poly(*this) += b;}
    Poly operator - (const Poly &b) {return Poly(*this) -= b;}
    Poly operator *= (const Poly &b) {
        int test = min(a.size(), b.a.size());
        if (test > 100) conv(a, b.a);
        else mulslow(a, b.a);
        normalize();
        return *this;
    }
    
    Poly operator * (const Poly &b) {return Poly(*this) *= b;}
    Poly modx(int k) {
        vector<Mint> b(min(k, (int)a.size()));
        for (int i = 0; i < min(k, (int)a.size()); i++) {
            b[i] = a[i];    
        }
        
        return Poly(b);
    }
    
    Poly inv(int k) {
        int n = a.size();
        assert(a[0] != 0);
        Poly b = Poly((Mint)1 / a[0]), c = *this;
        for (int i = 2; i <= nxtpow(k); i <<= 1) {
            b *= (Poly(2) - c.modx(i) * b);
            b = b.modx(i);
        }
        
        return b.modx(k);
    }
    
    pair<Poly, bool> sqrt(int k) {
        int n = a.size();
        auto [s, ok] = cipolla(a[0]);
        if (!ok) return {Poly(), false};
        if ((ll)s > (ll)(-s)) s = -s;
        Poly b = Poly(s), c = *this;
        for (int i = 2; i <= nxtpow(k); i <<= 1) {
            b = (b * b + c.modx(i)) * b.inv(i) * Poly(invtwo);
            b = b.modx(i);
        }
        
        return {b.modx(k), true};
    }
    
    Poly deriv() {
        int n = a.size();
        vector<Mint> b(n - 1);
        for (int i = 1; i < n; i++) {
            b[i - 1] = a[i] * i;
        }
        
        return Poly(b);
    }
    
    Poly integral() {
        int n = a.size();
        vector<Mint> b(n + 1);
        for (int i = 1; i <= n; i++) {
            b[i] = a[i - 1] / i;
        }
        
        return Poly(b);
    }
    
    Poly log(int k) {
        assert(!a.empty() && a[0] == 1);
        Poly b = Poly(a);
        Poly c = b.deriv() * b.inv(k);
        return c.integral().modx(k);
    }
    
    Poly exp(int k) {
        if (a.empty()) return Poly(1);
        int n = a.size();
        assert(a[0] == 0);
        Poly b = Poly(1), c = *this;
        for (int i = 2; i <= nxtpow(k); i <<= 1) {
            b = b * (Poly(1) - b.log(i) + c.modx(i));
            b = b.modx(i);
        }
        
        return b.modx(k);
    }
    
    Poly shift(int k, int m) {
        int n = a.size();
        vector<Mint> b(k);
        for (int i = 0; i < n; i++) {
            if (i + m >= 0 && i + m < k) b[i + m] = a[i];
        }
        
        return Poly(b);
    }
    
    Poly pow(int k, ll p) {
        if (p == 0) return Poly(1);
        normalize();
        int n = a.size();
        if (n == 0) return Poly();
        Poly b = Poly(a);
        int pos = 0;
        Mint val = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != 0) {
                pos = i, val = a[i];
                break;
            }
        }
        
        if (pos >= (k + p - 1) / p) return Poly();
        b = b.shift(k, -pos) * Poly((Mint)1 / val);
        b = (b.log(k) * Poly(p)).exp(k).shift(k, p * pos) * Poly(power(val, p));
        return b;
    }
    
    Mint eval(Mint x) {
        normalize();
        Mint cur = 1, res = 0;
        for (int i = 0; i < a.size(); i++) {
            res += a[i] * cur;
            cur *= x;
        }
        
        return res;
    }
};

int n, k, qq;
void solve() {
    cin >> n >> k;
    n++;
    vector<Mint> aa(n);
    for (int i = 0; i < n; i++) {
        cin >> aa[i];
    }
    
    Poly a = Poly(aa);
    auto [b, ok] = a.sqrt(n);
    assert(ok);
    b = b.inv(n);
    b = b.integral();
    b -= Poly(b.eval(0));
    b = Poly(2) + a - Poly(a.eval(0)) - b.exp(n);
    b = b.log(n) + Poly(1);
    b = b.pow(n, k).deriv();
    b.resz(n - 1);
    b.print();
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}