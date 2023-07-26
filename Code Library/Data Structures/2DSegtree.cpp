#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int inf = 1e9;
int n, m, k, qq;
int a[N][N], t[N * 4][N * 4];
void buildy(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) t[vx][vy] = a[lx][ly];
        else t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
        return;
    }
    
    int mid = (ly + ry) / 2;
    buildy(vx, lx, rx, vy * 2, ly, mid);
    buildy(vx, lx, rx, vy * 2 + 1, mid + 1, ry);
    t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
}

void buildx(int vx, int lx, int rx) {
    if (lx != rx) {
        int mid = (lx + rx) / 2;
        buildx(vx * 2, lx, mid);
        buildx(vx * 2 + 1, mid + 1, rx);
    }
    
    buildy(vx, lx, rx, 1, 0, n - 1);
}

int queryy(int vx, int vy, int tly, int try_, int qly, int qry) {
    if (qly > try_ || qry < tly) return 0;
    if (qly <= tly && qry >= try_) {
        return t[vx][vy];
    }
    
    int mid = (tly + try_) / 2;
    return queryy(vx, vy * 2, tly, mid, qly, qry) +
    queryy(vx, vy * 2 + 1, mid + 1, try_, qly, qry);
}

int queryx(int vx, int tlx, int trx, int qlx, int qrx, int qly, int qry) {
    if (qlx > trx || qrx < tlx) return 0;
    if (qlx <= tlx && qrx >= trx) {
        return queryy(vx, 1, 0, n - 1, qly, qry);
    }
    
    int mid = (tlx + trx) / 2;
    return queryx(vx * 2, tlx, mid, qlx, qrx, qly, qry) + 
    queryx(vx * 2 + 1, mid + 1, trx, qlx, qrx, qly, qry);
}

void updatey(int vx, int tlx, int trx, int vy, int tly, int try_, int x, int y, int val) {
    if (tly == try_) {
        if (tlx == trx) t[vx][vy] = val;
        else t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
        return;
    }
    
    int mid = (tly + try_) / 2;
    if (y <= mid) updatey(vx, tlx, trx, vy * 2, tly, mid, x, y, val);
    else updatey(vx, tlx, trx, vy * 2 + 1, mid + 1, try_, x, y, val);
    t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
}

void updatex(int vx, int tlx, int trx, int x, int y, int val) {
    if (tlx != trx) {
        int mid = (tlx + trx) / 2;
        if (x <= mid) updatex(vx * 2, tlx, mid, x, y, val);
        else updatex(vx * 2 + 1, mid + 1, trx, x, y, val);
    }
    
    updatey(vx, tlx, trx, 1, 0, n - 1, x, y, val);
}