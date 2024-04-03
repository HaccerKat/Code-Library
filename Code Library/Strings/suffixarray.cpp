#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
class suffixarray {
public:
    const int al = 256;
    string s;
    int n, mxlg;
    vector<int> p, c, cnt, lcp;
    vector<vector<int>> ch;
    suffixarray() {}
    // remember to add the ending characters like '$' at the end
    suffixarray(string s) : s(s) {
        n = s.size(), mxlg = __lg(n) + 1;
        p.resize(n), c.resize(n), ch.resize(mxlg + 1), cnt.resize(max(al, n));
        for (int i = 0; i <= mxlg; i++) ch[i].resize(n);
        lcp.resize(n);
        build();
        // buildlcp();
    }
    
    void build() {
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < al; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        int classes = 1;
        for (int i = 0; i < n; i++) {
            if (i != 0 && s[p[i]] != s[p[i - 1]]) classes++;
            ch[0][p[i]] = classes - 1;
        }
        
        vector<int> pn(n);
        for (int h = 0; h < mxlg; h++) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) cnt[ch[h][i]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[ch[h][pn[i]]]] = pn[i];
            classes = 1;
            pi prev = {ch[h][p[0]], ch[h][(p[0] + (1 << h)) % n]};
            for (int i = 0; i < n; i++) {
                pi cur = {ch[h][p[i]], ch[h][(p[i] + (1 << h)) % n]};
                if (cur != prev) classes++;
                ch[h + 1][p[i]] = classes - 1;
                swap(prev, cur);
            }
        }
        
        c = ch[mxlg];
    }
    
    int getlcp(int x, int y) {
        int res = 0;
        for (int i = mxlg; i >= 0; i--) {
            if (ch[i][x] == ch[i][y]) {
                int v = 1 << i;
                res += v, x += v, y += v;
            }
        }
        
        return res;
    }
    
    // remember this may include the '$' ending character or more
    void buildlcp() {
        for (int i = 0; i < n - 1; i++) {
            lcp[i] = getlcp(p[i], p[i + 1]);
        }
    }
};