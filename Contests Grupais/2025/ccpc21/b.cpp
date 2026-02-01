#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
using pii = pair<int,int>;

struct SegmentTree {
    vector<int> seg, lazy;
    int l0, ln;

    SegmentTree(int n) : ln{1} {
        while(ln < n) ln *= 2;
        seg.resize(2*ln-1);
        lazy.resize(seg.size());
        l0 = seg.size()-ln;
    }

    SegmentTree(vector<int>& v) : SegmentTree(v.size()) {
        for(int i = 0; i < v.size(); i++) {
            seg[l0+i] = v[i];
        }
        for(int i = l0-1; i >= 0; i--) {
            seg[i] = seg[2*i+1] + seg[2*i+2];
        }
    }

    void unlazy(int i, int lx, int rx) {
        seg[i] += lazy[i]*(rx-lx+1);
        if(i < l0) {
            lazy[2*i+1] += lazy[i];
            lazy[2*i+2] += lazy[i];
        }
        lazy[i] = 0;
    }

    void upd(int l, int r, int val) {
        upd(l, r, val, 0, ln-1, 0);
    }

    void upd(int l, int r, int val, int lx, int rx, int i) {
        unlazy(i,lx,rx);
        if(rx < l || r < lx) return;
        if(l <= lx && rx <= r) {
            lazy[i] += val;
            unlazy(i,lx,rx);
            return;
        }
        int m = (lx+rx)/2;
        upd(l, r, val, lx, m, 2*i+1);
        upd(l, r, val, m+1, rx, 2*i+2);
    }

    ll query(int l, int r) {
        return query(l, r, 0, ln-1, 0);
    }

    ll query(int l, int r, int lx, int rx, int i) {
        unlazy(i,lx,rx);
        if(rx < l || r < lx) return 0;
        if(l <= lx && rx <= r) return seg[i];
        int m = (lx+rx)/2;
        return query(l, r, lx, m, 2*i+1) +  query(l, r, m+1, rx, 2*i+2);
    }
};

set<pii>::iterator addInterval(set<pii> &is, int L, int R) {
    if (L == R) return is.end();
    auto it = is.lower_bound({L,R}), before = it;
    while (it != is.end() && it->first <= R) {
        R = max(R, it->second);
        before = it = is.erase(it);
    }
    if (it != is.begin() && (--it)->second >= L) {
        L = min(L, it->first); R = max(R, it->second);
        is.erase(it);
    } return is.insert(before, {L,R});
}
void removeInterval(set<pii> &is, int L, int R) {
    if(L == R) return;
    auto it = addInterval(is, L, R);
    auto r2 = it->second;
    if (it->first == L) is.erase(it);
    else (int&) it->second = L;
    if (R != r2) is.emplace(R, r2);
}

set<pii>::iterator getIntervalContaining(set<pii>& is, int i) {
    auto it = is.lower_bound({i,1e9});
    if(it != is.begin()) it--;
    else it = is.end();
    if(it != is.end() && !(it->first <= i && i < it->second)) it = is.end();
    return it;
}

void splitIntervalContaining(set<pii>& is, int i) {
    auto it = getIntervalContaining(is, i);
        if(it != is.end()) {
            auto [l,r] = *it;
            removeInterval(is, l, r);
            if(l < i) addInterval(is, l, i);
            if(i+1 < r) addInterval(is, i+1, r);
        }
}

pii binary_search(int l, int r, SegmentTree& carry, int all_carries) {
    int bbl = 0, bbr = r-l+1, ans = 0;
    while(bbl <= bbr) {
        int mid = (bbl+bbr)/2;

        if(all_carries && carry.query(r-mid+1,r) == mid || !all_carries && carry.query(r-mid+1,r) == 0) {
            ans = mid;
            bbl = mid+1;
        }else {
            bbr = mid-1;
        }
    }

    return {r-ans+1,r+1};
}

void printSeg(SegmentTree& seg) {
    for(int i = 0; i < seg.ln; i++) {
        cout << seg.query(i,i) << ' ';
    }
    cout << endl;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    string sr1, sr2;
    cin >> sr1 >> sr2;

    vector<int> r1(n+1), r2(n+1), num(n+1), c(n+1);

    for(int i = 0; i < n; i++) {
        r1[i+1] = sr1[i]-'0';
        r2[i+1] = sr2[i]-'0';
    }

    for(int i = n, carry = 0; i >= 0; i--) {
        num[i] = r1[i] + r2[i] + carry;
        c[i] = carry;
        carry = 0;
        if(num[i] >= 10) {
            num[i] -= 10;
            carry = 1;
        }
    }

    SegmentTree ans(num), carry(c);
    
    set<pii> intervals;
    int in = 0, l = -1, r = -1;
    for(int i = 0; i <= n; i++) {
        if(r1[i] + r2[i] == 9) {
            if(in) {
                r++;
            }else {
                l = i;
                r = i+1;
                in = true;
            }
        }else {
            if(in) {
                addInterval(intervals,l,r);
                in = false;
            }
        }
    }

    // printSeg(ans);
    // printSeg(carry);

    if(in) addInterval(intervals,l,r);

    while(q--) {
        int r, c, d;
        cin >> r >> c >> d;

        splitIntervalContaining(intervals, c);

        int cnt;

        if(r == 1) {
            cnt = 2*(r1[c] != d);
            r1[c] = d;
        }else {
            cnt = 2*(r2[c] != d);
            r2[c] = d;
        }

        int ccarry = carry.query(c,c);
        int new_sum = r1[c]+r2[c]+ccarry;

        ans.upd(c,c, new_sum % 10 - ans.query(c,c));

        if(carry.query(c-1,c-1) == 0 && new_sum >= 10) {
            auto it = getIntervalContaining(intervals, c-1);
            int l = c, r = c;
            if(it != intervals.end()) {
                auto [cl,cr] = binary_search(it->first, it->second-1, carry, 0);
                int l = cl;
                int r = cr;
            }
            ans.upd(l,r-1,-9);
            ans.upd(l-1,l-1,1);
            carry.upd(l-1,r-1,1);
            cnt += 1 + r-l;
        }else if(carry.query(c-1,c-1) == 1 && new_sum < 10) {
            auto it = getIntervalContaining(intervals, c-1);
            int l = c, r = c;
            if(it != intervals.end()) {
                auto [cl,cr] = binary_search(it->first, it->second-1, carry, 1);
                int l = cl;
                int r = cr;
            }
            ans.upd(l,r-1,+9);
            ans.upd(l-1,l-1,-1);
            carry.upd(l-1,r-1,-1);
            cnt += 1 + r-l;
        }

        if(new_sum-ccarry == 9) addInterval(intervals, c, c+1);

        cout << ans.query(c,c) << ' ' << cnt << '\n';
        // printSeg(ans);
        // printSeg(carry);
    }

    return 0;
}