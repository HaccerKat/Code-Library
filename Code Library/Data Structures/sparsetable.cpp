#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int LOG = 20;
template <class T>
class RMQ {
public:
    int n, int ty;
    vector<vector<T>> rmq;
    vector<int> logA;
    T operation(T x, T y) {
        if (ty == 0) return min(x, y);
        else if (ty == 1) return max(x, y);
        else return gcd(x, y);
    }
    
    void precomp(vector<T> &a) {
        for (int i = 2; i <= n; i++) {
            logA[i] = logA[i >> 1] + 1;
        }
        
        for (int i = 0; i < n; i++) {
            rmq[i][0] = a[i];
        }
        
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                rmq[i][j] = operation(rmq[i][j - 1], rmq[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    
    RMQ(vector<T> a, int ty) {
        this->ty = ty;
        n = a.size();
        rmq.resize(n);
        logA.resize(n + 1);
        for (int i = 0; i < n; i++) {
            rmq[i].resize(LOG);
        }
        
        precomp(a);
    }
    
    T query(int l, int r) {
        int sz = r - l + 1;
        int lg = logA[sz];
        return operation(rmq[l][lg], rmq[r - (1 << lg) + 1][lg]);
    }
};