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


// using ModType = int;
 
// struct VarMod { static ModType value; };
// ModType VarMod::value;
// ModType& md = VarMod::value;
// using Mint = Modular<VarMod>;

 
constexpr int md = (int) 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
 
// vector<Mint> fact;
// vector<Mint> inv_fact;
 
// Mint C(int n, int k) {
//     if (k < 0 || k > n) {
//         return 0;
//     }

//     if (fact.empty()) {
//         fact.push_back(1);
//         inv_fact.push_back(1);
//     }

//     while ((int) fact.size() < n + 1) {
//         fact.push_back(fact.back() * (int) fact.size());
//         inv_fact.push_back(1 / fact.back());
//     }

//     return fact[n] * inv_fact[k] * inv_fact[n - k];
// }

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
int n, m, k, qq;
struct Node {
    Mint val = 0, sum = 0, lazyadd = 0, lazymul = 1;
    int ch[2] = {0, 0}, p = 0, sz = 0;
    bool lazy = 0; 
    Node() {}
    Node(Mint x) {val = x, sum = x, sz = 1;} 
};

int root = 1;
// node 0 is a dummy node that is empty at all times
// node (N - 1) is a dummy node for pushing
Node a[N];
int dir(int u) {
    if (!a[u].p) return -1;
    if (a[a[u].p].ch[0] == u) return 0;
    else return 1;
}

void pull(int u, int v) {
    a[u].sum += a[v].sum, a[u].sz += a[v].sz;
}

void pullup(int u) {
    a[u].sum = a[u].val, a[u].sz = 1;
    pull(u, a[u].ch[0]);
    pull(u, a[u].ch[1]);
}

void push(int u, int v) {
    Mint x = a[u].lazymul, y = a[u].lazyadd;
    a[v].sum *= x, a[v].val *= x, a[v].lazyadd *= x, a[v].lazymul *= x;
    a[v].sum += y * a[v].sz, a[v].val += y, a[v].lazyadd += y;
    a[v].lazy ^= a[u].lazy;
}

void prop(int u) {
    if (a[u].lazy) swap(a[u].ch[0], a[u].ch[1]);
    push(u, a[u].ch[0]);
    push(u, a[u].ch[1]);
    a[u].lazyadd = 0, a[u].lazymul = 1, a[u].lazy = 0;
}

void addedge(int u, int v, int d) {
    if (u != 0) a[u].ch[d] = v;
    if (v != 0) a[v].p = u;
}

void rot(int u) {
    int v = a[u].p;
    int du = dir(u), dv = dir(v);
    int vv = a[v].p, c = a[u].ch[du ^ 1];
    addedge(v, c, du);
    addedge(u, v, du ^ 1);
    addedge(vv, u, dv);
    pullup(v);
    pullup(u);
}

void splay(int u) {
    while (dir(u) != -1) {
        int v = a[u].p;
        int du = dir(u), dv = dir(v);
        if (dv != -1) rot(du == dv ? v : u);
        rot(u);
    }
}

int find(int u, int x) {
    prop(u);
    int sz = a[a[u].ch[0]].sz;
    if (!u) return 0;
    else if (sz > x) return find(a[u].ch[0], x);
    else if (sz == x) return u;
    else return find(a[u].ch[1], x - sz - 1);
}

int merge(int u, int v) {
    if (!u || !v) return u ^ v;
    splay(u);
    int w = find(u, a[u].sz - 1);
    splay(w);
    addedge(w, v, 1);
    pull(w, v);
    return w;
}

// splits into two trees with i <= idx and i > idx
pi split(int idx, int u = root) {
    if (idx + 1 >= a[u].sz) return {u, 0};
    int v = find(u, idx + 1);
    splay(v);
    int c = a[v].ch[0];
    a[c].p = 0, a[v].ch[0] = 0;
    pullup(v);
    return {c, v};
}

array<int, 3> splitthree(int l, int r, int u = root) {
    auto [lv, mrv] = split(l - 1, u);
    auto [mv, rv] = split(r - l, mrv);
    return {lv, mv, rv};
}

int cur = 1;
Mint aa[N];
void solve() {
    cin >> n >> qq;
    for (int i = 1; i <= n; i++) {
        cin >> aa[i];
        a[i] = Node(aa[i]);
        root = merge(i - 1, i);
    }
    
    cur = n + 1;
    while (qq--) {
        int t, i, l, r;
        Mint b, c, x;
        cin >> t;
        if (t == 0) {
            cin >> i >> x;
            a[cur] = Node(x);
            auto [lv, rv] = split(i - 1);
            root = merge(merge(lv, cur), rv);
            cur++;
        }
        
        else if (t == 1) {
            cin >> i;
            auto [lv, mv, rv] = splitthree(i, i);
            root = merge(lv, rv);
        }
        
        else {
            cin >> l >> r;
            r--;
            auto [lv, mv, rv] = splitthree(l, r);
            if (t == 2) {
                a[mv].lazy ^= 1;
            }
            
            else if (t == 3) {
                cin >> b >> c;
                a[N - 1].lazymul = b, a[N - 1].lazyadd = c;
                push(N - 1, mv);
                a[N - 1].lazyadd = 0, a[N - 1].lazymul = 1, a[N - 1].lazy = 0;
            }
            
            else {
                cout << a[mv].sum << "\n";
            }
            
            root = merge(merge(lv, mv), rv);
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}