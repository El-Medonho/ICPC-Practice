// ⢸⣿⣿⣿⣿⠃⠄⢀⣴⡾⠃⠄⠄⠄⠄⠄⠈⠺⠟⠛⠛⠛⠛⠻⢿⣿⣿⣿⣿⣶⣤⡀⠄
// ⢸⣿⣿⣿⡟⢀⣴⣿⡿⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣸⣿⣿⣿⣿⣿⣿⣿⣷
// ⢸⣿⣿⠟⣴⣿⡿⡟⡼⢹⣷⢲⡶⣖⣾⣶⢄⠄⠄⠄⠄⠄⢀⣼⣿⢿⣿⣿⣿⣿⣿⣿⣿
// ⢸⣿⢫⣾⣿⡟⣾⡸⢠⡿⢳⡿⠍⣼⣿⢏⣿⣷⢄⡀⠄⢠⣾⢻⣿⣸⣿⣿⣿⣿⣿⣿⣿
// ⡿⣡⣿⣿⡟⡼⡁⠁⣰⠂⡾⠉⢨⣿⠃⣿⡿⠍⣾⣟⢤⣿⢇⣿⢇⣿⣿⢿⣿⣿⣿⣿⣿
// ⣱⣿⣿⡟⡐⣰⣧⡷⣿⣴⣧⣤⣼⣯⢸⡿⠁⣰⠟⢀⣼⠏⣲⠏⢸⣿⡟⣿⣿⣿⣿⣿⣿
// ⣿⣿⡟⠁⠄⠟⣁⠄⢡⣿⣿⣿⣿⣿⣿⣦⣼⢟⢀⡼⠃⡹⠃⡀⢸⡿⢸⣿⣿⣿⣿⣿⡟
// ⣿⣿⠃⠄⢀⣾⠋⠓⢰⣿⣿⣿⣿⣿⣿⠿⣿⣿⣾⣅⢔⣕⡇⡇⡼⢁⣿⣿⣿⣿⣿⣿⢣
// ⣿⡟⠄⠄⣾⣇⠷⣢⣿⣿⣿⣿⣿⣿⣿⣭⣀⡈⠙⢿⣿⣿⡇⡧⢁⣾⣿⣿⣿⣿⣿⢏⣾
// ⣿⡇⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢻⠇⠄⠄⢿⣿⡇⢡⣾⣿⣿⣿⣿⣿⣏⣼⣿
// ⣿⣷⢰⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⢰⣧⣀⡄⢀⠘⡿⣰⣿⣿⣿⣿⣿⣿⠟⣼⣿⣿
// ⢹⣿⢸⣿⣿⠟⠻⢿⣿⣿⣿⣿⣿⣿⣿⣶⣭⣉⣤⣿⢈⣼⣿⣿⣿⣿⣿⣿⠏⣾⣹⣿⣿
// ⢸⠇⡜⣿⡟⠄⠄⠄⠈⠙⣿⣿⣿⣿⣿⣿⣿⣿⠟⣱⣻⣿⣿⣿⣿⣿⠟⠁⢳⠃⣿⣿⣿
// ⠄⣰⡗⠹⣿⣄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⠟⣅⣥⣿⣿⣿⣿⠿⠋⠄⠄⣾⡌⢠⣿⡿⠃
// ⠜⠋⢠⣷⢻⣿⣿⣶⣾⣿⣿⣿⣿⠿⣛⣥⣾⣿⠿⠟⠛⠉⠄⠄

#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;

vector<int> build(string &s){
    int n = (int)s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r){
            z[i] = min(r-i+1, z[i-l]);
        }
        while(i+z[i] < n && s[z[i]] == s[i+z[i]]){
            z[i]++;
        }
        if(i+z[i]-1>r){
            l = i, r=i+z[i]-1;
        }
    }

    return z;
}

struct SA{
    int n;
    string s;
    vector<int> sa, pos;
    // vector<vector<int>> rank_subs;

    vector<int> suffix_array(){
        s.push_back('$');
        int n = (int)s.size(), N=max(n, 260);
        vector<int> sa(n), rank(n);

        for(int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i];

        for(int k = 0; k < n; k ? k*=2 : k++){
            vector<int> nsa(sa), nrank(n), cnt(N);

            for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[rank[i]]++;
            for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
            for(int i = n-1; i+1; i--) sa[--cnt[rank[nsa[i]]]] = nsa[i];

            for(int i = 1, r = 0; i < n; i++) nrank[sa[i]] = r += rank[sa[i]] != rank[sa[i-1]] || rank[(sa[i]+k)%n] != rank[(sa[i-1]+k)%n];

            rank = nrank;
            // rank_subs.push_back(rank);
            if(rank[sa[n-1]]==n-1) break;
        }
        s.pop_back();

        return vector<int>(sa.begin()+1, sa.end());
    }

    SA(string s) : s(s), n((int)s.size()), pos(n){
        sa = suffix_array();
    }
};

signed solve(){
    string a,b; cin >> a >> b;

    SA sa(a);

    vector<int> z = build(b);

    vector<ll> ans(b.size());
    for(char c: a){
        if(c == b[0]) ans[0]++;
    }

    ans[0] = (ans[0]*(ans[0]+1))/2;

    vector<int> sz(b.size(), 0);

    stack<pair<int,int>> qw;
    for(int i = 1; i < b.size(); i++){
        if(z[i] > 0) qw.emplace(i, z[i]);

        while(!qw.empty() && qw.top().first + qw.top().second <= i) qw.pop();
        if(qw.empty()) sz[i] = i+1;
        else sz[i] = i - qw.top().first + 1;
    }

    // for(int x: sz) cout << x << ' ';
    // cout << endl;

    vector<ll> by_sz(b.size(), 0LL);

    int L = 0, R = a.size()-1;
    for(int i = 0; i < b.size(); i++){
        int l = L, r = R;

        while(l <= r){
            int md = (l+r)/2;
            if(sa.sa[md]+i >= sa.sa.size()) {
                l = md+1;
                continue;
            }

            if(a[sa.sa[md]+i] < b[i]) {
                l = md+1;
            } else {
                r = md-1;
                L = md;
            }
        }

        l = L, r = R;

        while(l <= r){
            int md = (l+r)/2;
            if(sa.sa[md]+i >= sa.sa.size()) {
                l = md+1;
                continue;
            }

            if(a[sa.sa[md]+i] <= b[i]) {
                l = md+1;
                R = md;
            } else {
                r = md-1;
            }
        }

        if(sa.sa[L] + i >= a.size() || a[sa.sa[L]+i] != b[i]) break;
        by_sz[i] = R-L+1;
    }

    for(int i = 1; i < b.size(); i++){
        ll cc = by_sz[sz[i]-1];
        ans[i] = cc * (cc+1)/2;
        ans[i] *= sz[i];
    }

    for(ll x: ans) cout << x << ' ';
    cout << endl;

    return 0;
}


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}