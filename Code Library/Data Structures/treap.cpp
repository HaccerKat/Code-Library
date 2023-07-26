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
const int N = 1000005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
string s;
int n, m, k, qq;
int ch[N][2], priority[N], sz[N], lazy[N];
Mint lazymul[N], lazyadd[N], val[N], sum[N], a[N];
int cur = 1, root = 0;
void push(int u, int v) {
    Mint mul = lazymul[u], add = lazyadd[u];
    lazy[v] ^= lazy[u], lazymul[v] *= mul, lazyadd[v] *= mul, val[v] *= mul, sum[v] *= mul;
    lazyadd[v] += add, val[v] += add, sum[v] += add * sz[v];
}

void prop(int u) {
    if (lazy[u]) swap(ch[u][0], ch[u][1]);
    if (ch[u][0] != 0) push(u, ch[u][0]);
    if (ch[u][1] != 0) push(u, ch[u][1]);
    lazy[u] = 0, lazymul[u] = 1, lazyadd[u] = 0;
}

void pull(int u) {
    int l = ch[u][0], r = ch[u][1];
    sz[u] = sz[l] + sz[r] + 1, sum[u] = sum[l] + sum[r] + val[u];
}

pi split(int p, int u = root, int idx = 0) {
    pi nodes = {0, 0};
    if (u == 0) return nodes;
    prop(u);
    if (idx + sz[ch[u][0]] <= p) {
        auto [lv, rv] = split(p, ch[u][1], idx + sz[ch[u][0]] + 1);
        ch[u][1] = lv, nodes = {u, rv};
    }
    
    else {
        auto [lv, rv] = split(p, ch[u][0], idx);
        ch[u][0] = rv, nodes = {lv, u};
    }
    
    pull(u);
    return nodes;
}

array<int, 3> splitthree(int l, int r) {
    auto [lv, mrv] = split(l - 1);
    auto [mv, rv] = split(r - l, mrv);
    return {lv, mv, rv};
}

//lower value for priority is higher priority
int merge(int u, int v) {
    int w;
    if (u == 0) return v;
    if (v == 0) return u;
    if (priority[u] < priority[v]) {
        prop(u);
        ch[u][1] = merge(ch[u][1], v), w = u;
    }
    
    else {
        prop(v);
        ch[v][0] = merge(u, ch[v][0]), w = v;
    }
    
    pull(w);
    return w;
}

void rev(int l, int r) {
    auto [lv, mv, rv] = splitthree(l, r);
    lazy[mv] ^= 1;
    root = merge(merge(lv, mv), rv);
}

//N - 1 is a dummy node for pushing
void upd(int l, int r, Mint b, Mint c) {
    auto [lv, mv, rv] = splitthree(l, r);
    lazymul[N - 1] = b, lazyadd[N - 1] = c;
    push(N - 1, mv);
    root = merge(merge(lv, mv), rv);
}

Mint query(int l, int r) {
    auto [lv, mv, rv] = splitthree(l, r);
    Mint res = sum[mv];
    root = merge(merge(lv, mv), rv);
    return res;
}

void ins(int p, Mint x) {
    int id = cur++;
    val[id] = x, sum[id] = x, sz[id] = 1, lazymul[id] = 1;
    auto [lv, rv] = split(p - 1);
    root = merge(merge(lv, id), rv);
}

void del(int p) {
    auto [lv, mv, rv] = splitthree(p, p);
    root = merge(lv, rv);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve() {
    cin >> n >> qq;
    for (int i = 0; i < n + qq; i++) {
        priority[i] = i;
    }
    
    shuffle(priority, priority + n + qq, rng);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ins(i, a[i]);
    }
    
    while (qq--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, x;
            cin >> i >> x;
            ins(i, x);
        }
        
        else if (t == 1) {
            int i;
            cin >> i;
            del(i);
        }
        
        else if (t == 2) {
            int l, r;
            cin >> l >> r;
            r--;
            rev(l, r);
        }
        
        else if (t == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            r--;
            upd(l, r, b, c);
        }
        
        else {
            int l, r;
            cin >> l >> r;
            r--;
            cout << query(l, r) << "\n";
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}