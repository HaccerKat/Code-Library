#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int K = 100000;
const int inf = 1e9;
//Li Chao Tree for maximum, change for minimum
struct Line {
	ll m, b;
	Line() : m(0), b(-inf) {}
	Line(ll m, ll b) : m(m), b(b) {}
	ll eval(ll x) {
		return m * x + b;
	}
};

struct Node {
	Line line;
	Node *l = nullptr;
	Node *r = nullptr;
};

void insertline(Node *v, Line x, int tl = -K, int tr = K) {
	if (v == nullptr) v = new Node();
	if (v->line.eval(tl) < x.eval(tl)) {
		swap(v->line, x);
	}
	
	if (v->line.eval(tr) >= x.eval(tr)) return;
	if (tl == tr) return;
	int mid = (tl + tr) / 2;
	if (v->line.eval(mid) > x.eval(mid)) {
		insertline(v->r, x, mid + 1, tr);
	}
	
	else {
		swap(v->line, x);
		insertline(v->l, x, tl, mid);
	}
}

ll query(Node *v, int p, int tl = -K, int tr = K) {
	if (v == nullptr) return -inf;
	if (tl == tr) return v->line.eval(p);
	ll res = v->line.eval(p);
	int mid = (tl + tr) / 2;
	if (p <= mid) {
		return max(res, query(v->l, p, tl, mid));
	}
	
	else {
		return max(res, query(v->r, p, mid + 1, tr));
	}
}