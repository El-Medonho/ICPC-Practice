#include "bits/stdc++.h"

using namespace std;

// #define endl '\n'
typedef long long ll;

const int inf = 1e9;

template <class T> struct RMQ {
    int lg;
    vector<vector<T>> tab, tab2;

    T join(T a, T b){
        return min(a, b);
    }

    T join2(T a, T b){
        return max(a, b);
    }

    RMQ() {}

    RMQ(vector<T> &v) {
        int n = (int)v.size();
        lg = __lg(n)+1;
        tab.resize(lg);
        tab2.resize(lg);
        tab[0]=v; tab2[0]=v;
        for(int i = 0; i <(int)v.size(); i++) if(tab2[0][i] == inf) tab2[0][i] = -1;
        for(int j = 1; j < lg; j++){
            tab[j].resize(n-(1<<j)+1);
            tab2[j].resize(n-(1<<j)+1);
            for(int i=0; i+(1<<j)<=n; i++){
                tab[j][i] = join(tab[j-1][i], tab[j-1][i+(1<<(j-1))]);
                tab2[j][i] = join2(tab2[j-1][i], tab2[j-1][i+(1<<(j-1))]);
            }
        }
    }

    T query_min(int l, int r){
        int k = __lg(r-l);
        return min(tab[k][l], tab[k][r-(1<<k)]);
    }

    T query_max(int l, int r){
        int k = __lg(r-l);
        return max(tab2[k][l], tab2[k][r-(1<<k)]);
    }
};

struct SA{
    int n;
    string s;
    vector<int> sa, lcp;
    vector<vector<int>> rank_subs;
    RMQ<int> rmq;

    vector<int> suffix_array() {
        s.push_back('$');

        int n=(int)s.size(), N=max(n, 260);
        vector<int> sa(n), rank(n);

        for(int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i];

        for(int k = 0; k < n; k ? k*=2 : k++) {
            vector<int> nsa(sa), nrank(n), cnt(N);
            for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[rank[i]]++;
            for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
            for(int i = n-1; i+1; i--) sa[--cnt[rank[nsa[i]]]] = nsa[i];

            for(int i = 1, r = 0; i < n; i++) nrank[sa[i]] = r += rank[sa[i]] != rank[sa[i-1]] || 
            rank[(sa[i]+k)%n] != rank[(sa[i-1]+k)%n];

            rank = nrank;
        }

        s.pop_back();

        return vector<int>(sa.begin()+1, sa.end());
    }

    vector<int> build_lcp(){
        int n = (int)s.size(), k = 0;
        vector<int> rank(n), lcp(n);
        for(int i = 0; i < n; i++) rank[sa[i]] = i;

        for(int i = 0; i < n; i++, k-=!!k) {
            if(rank[i] == n-1) {k = 0; continue;}
            int j=sa[rank[i]+1];
            while(i+k<n && j+k<n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
        }
        return lcp;
    }

    SA() {}

    SA(string s) : s(s), n((int)s.size()) {
        sa = suffix_array();
        lcp = build_lcp();
        rmq = RMQ(lcp);
    }

    int get_lcp(int i, int j) {
        // int l = pos[i], r = pos[j];
        if(i == j) return n-sa[i];
        int l = i, r = j;

        if(l > r) swap(l, r);

        return rmq.query_min(l, r);
    }
};

signed solve(){

    int n,q; cin >> n >> q;

    string s; cin >> s;

    SA sa(s);
    
    vector<vector<int>> sum(n+1, vector<int>(26, 0)), last(n+1, vector<int>(26, -1));
    
    for(int i = 0; i < n; i++){
        sum[i+1] = sum[i];
        char c = s[i];
        sum[i+1][c-'a']++;
        last[i+1] = last[i];
        last[i+1][c-'a'] = i;
    }
    
    // for(int x: sa.lcp) cout << x << ' ';
    // cout << endl;
    
    
    vector<pair<int,int>> qu(q);
    vector<int> ans(q, 1), b(q, -1);
    
    for(int i = 0; i < q; i++){
        int l,r; cin >> l >> r; l--; r--;
        qu[i] = {l, r};
    }
    
    for(int c = 0; c < 26; c++){
        vector<int> arr(n, inf);
        for(int j = 0; j < n; j++) {
            if(s[sa.sa[j]] - 'a' != c) continue;
            arr[sa.sa[j]] = j;
        }
        
        RMQ<int> rmqs = RMQ(arr);
        // cout << "oi" << endl;
        
        for(int i = 0; i < q; i++){
            auto[l, r] = qu[i];
            if(rmqs.query_min(l, r+1) == inf) continue;
            
            // cout << c << ' ' << rmqs[c].query_min(l, r+1) << endl;
            
            // if(i == 1) cout << c << ' ' << rmqs[c].query_min(l, r+1) << ' ' << rmqs[c].query_max(l, r+1) << ' ' << sa.get_lcp(rmqs[c].query_min(l, r+1), rmqs[c].query_max(l, r+1)) << endl;
            int occ = sum[r+1][c] - sum[l][c];
            int sz = sa.get_lcp(rmqs.query_min(l, r+1), rmqs.query_max(l, r+1));
    
            sz = min(sz, r - last[r+1][c] + 1);
    
    
            if(occ > b[i]) {
                ans[i] = sz, b[i] = occ;
            } else if(occ == b[i]) ans[i] = max(ans[i], sz);
        }
    }

    for(int x: ans) cout << x << endl;

    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1; 
    // cin >> t;
    while(t--){
        solve();
    }


    return 0;
}