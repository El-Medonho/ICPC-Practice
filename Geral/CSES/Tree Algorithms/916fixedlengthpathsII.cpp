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

const ll INFL = 1e18;

vector<int> nos;

struct Centroid{
    int n;
    vector<int> used, pai, sub;
    vector<vector<int>> vec;

    Centroid(int n): n(n), used(n+1), pai(n+1), sub(n+1), vec(n+1) {nos.reserve(n+1);}

    void add_edge(int v, int u){
        vec[v].push_back(u);
        vec[u].push_back(v);
    }

    int dfs_sz(int x, int p = 0){
        sub[x] = 1;
        for(int i: vec[x]){
            if(i==p || used[i]) continue;
            sub[x]+=dfs_sz(i, x);
        }
        return sub[x];
    }

    int find_c(int x, int total, int p=0){
        for(int i: vec[x]){
            if(i==p || used[i]) continue;
            if(2*sub[i]>total) return find_c(i, total, x);
        }
        return x;
    }

    void build(int x = 1, int p = 0){
        int c = find_c(x, dfs_sz(x));

        nos.push_back(c);

        used[c] = 1;
        pai[c]=p;
        for(int i: vec[c]){
            if(!used[i]) build(i, c);
        }
    }
};

void upd(int ind, ll val, vector<ll> &bit){   //O(logn)
    ind++;
    while(ind<=bit.size()-1){
        bit[ind]+=val;
        ind+=ind&-ind;
    }
}
void upd2(int ind, ll val, vector<ll> &bit){   //O(logn)
    ind++;
    while(ind<=bit.size()-1){
        bit[ind]=val;
        ind+=ind&-ind;
    }
}

ll sum(int ind, vector<ll> &bit){         //O(logn)
    ind++;
    ll ans=0;
    while(ind){
        ans+=bit[ind];    
        ind-=ind&-ind;    
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin >> n;
    int kr, kl; cin >> kl >> kr;
    Centroid centroid(n);

    for(int i = 1; i < n; i++){
        int a,b; cin >> a >> b;
        centroid.add_edge(a, b);
    }

    centroid.build();
    vector<int> vis(n+1, 0);
    vector<ll> dp(kr+2, 0LL), dp2(kr+1, 0LL);

    ll ans = 0;
    int mx = -1, mx2 = -1;

    auto dfs = [&](auto &&self, int cc, int last, int d = 0) -> void {
        if(d > kr) return;

        ans += sum(kr-d, dp);
        ans -= sum(max(-1, kl-d-1), dp);
        if(d == 0) upd(0, 1, dp);
        else dp2[d]++;

        for(int j: centroid.vec[cc]){
            if(j == last || vis[j]) continue;
            if(d == 0){
                for(int h = 0; h <= mx; h++){
                    upd(h, dp2[h], dp);
                    dp2[h] = 0;
                }
                mx = -1;
            }
            self(self, j, cc, d+1);
        }
        
        mx = max(mx, d);
        mx2 = max(mx2, mx);
    };

    for(int cc: nos){
        dfs(dfs, cc, 0);
        vis[cc] = 1;
        for(int h = 0; h <= mx2; h++){
            upd2(h, 0, dp);
            dp2[h] = 0;
        }
        mx2 = -1;
        mx = -1;
    }

    cout << ans << endl;


    return 0;
}