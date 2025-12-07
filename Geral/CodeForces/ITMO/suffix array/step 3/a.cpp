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

struct SA{
    int n;
    string s;
    vector<int> sa;

    vector<int> suffix_array() {
        s.push_back('$');

        int n=(int)s.size(), N=max(n, 260);
        vector<int> sa(n), rank(n);

        for(int i=0; i<n; i++) sa[i] = i, rank[i] = s[i];

        for(int k=0; k<n; k ? k*=2 : k++) {
            vector<int> nsa(sa), nrank(n), cnt(N);

            for(int i=0; i<n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[rank[i]]++;
            for(int i=1; i<N; i++) cnt[i]+=cnt[i-1];
            for(int i=n-1; i+1; i--) sa[--cnt[rank[nsa[i]]]] = nsa[i];

            for(int i=1, r=0; i<n; i++) nrank[sa[i]] = r += rank[sa[i]] != rank[sa[i-1]] || rank[(sa[i]+k)%n] != rank[(sa[i-1]+k)%n];

            rank = nrank;
        }
        s.pop_back();

        return sa;
    }

    SA() {}

    SA(string s) : s(s), n((int)s.size()){
        sa = suffix_array();
    }
};

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    string s; cin >> s;
    int q; cin >> q;
    
    int n = s.size();
    int j = 0;

    SA sa(s);
    vector<int> suf = sa.sa;
    

    for(int g = 0; g < q; g++){
        string t; cin >> t;

        int l = 0, r = suf.size()-1;
        int ll = n+1, rr = 0;

        while(l <= r){
            int md = (l+r)/2;

            int i = suf[md];
            int h = min(n-i, (int)t.size());
            string comp = s.substr(i, h);
            if(comp == t){
                ll = md;
            }
            if(comp >= t){
                r = md-1;
            }
            else l = md+1;
        }
        if(ll == n+1){
            cout << "0\n";
            continue;
        }

        l = 0, r = suf.size()-1;
        while(l <= r){
            int md = (l+r)/2;

            int i = suf[md];
            int h = min(n-i, (int)t.size());
            string comp = s.substr(i, h);
            if(comp == t){
                rr = md;
            }
            if(comp > t){
                r = md-1;
            }
            else {
                l = md+1;
            }
        }
        cout << rr-ll+1 << endl;
    }

    return 0;
}