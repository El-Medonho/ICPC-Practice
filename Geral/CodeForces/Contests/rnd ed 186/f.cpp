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
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

#define endl "\n"
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef tree<int,null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int,null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> multiordered_set;  //--set.lower_bound(value) ao inves de find

mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int mod = 998244353;
const ll inf = 1e18+5;

void upd(int ind, ll val, vector<ll> &bit){   //O(logn)
    while(ind<=bit.size()-1){
        bit[ind]+=val;
        ind+=ind&-ind;
    }
}
ll sum(int ind, vector<ll> &bit){         //O(logn)
    ll ans=0;
    while(ind){
        ans+=bit[ind];    
        ind-=ind&-ind;    
    }
    return ans;
}

ll expo(ll b, ll e){
    ll res=1;
    while(e){
        if(e&1) res=res*b%mod;
        b=b*b%mod;
        e >>= 1;
    }
    return res;
}

signed solve(){
    
    int n,m; cin >> n >> m;


    vector<ll> pot(n+m+5, 1), fat(n+m+5, 1);
    for(int i = 1; i < pot.size(); i++) {
        pot[i] = pot[i-1] * 2 % mod;
        fat[i] = fat[i-1] * i % mod;
    }


    vector<int> arr(61, 0);
    vector<ll> bit(65, 0LL);

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        arr[x]++;
        upd(x+1, 1, bit);
    }

    while(m--){
        int tp; cin >> tp;
        if(tp == 1){
            ll x; cin >> x;
            arr[x]++;
            upd(x+1, 1, bit);
            continue;
        }
        else if(tp == 2){
            ll x; cin >> x;
            if(arr[x] > 0) upd(x+1, -1, bit);
            arr[x]--;
            arr[x] = max(arr[x], 0);
            continue;
        }

        ll x; cin >> x;

        vector<ll> seq(0);
        int d = 0, cont = 0;
        for(int i = 60; i >= 0; i--){
            if(x & (1LL << i)){
                if(cont == 0) seq.push_back(d);
                d = 0;
                cont++;
            }
            else {
                if(cont) seq.push_back(cont);
                cont = 0;
                d++;
            }
        }

        if(cont) seq.push_back(cont);
        cont = 0;
        
        assert(seq.size()%2 == 0);

        ll ans = 0, cans = 1;

        ll nxt = 60 - seq[0];
        int j = 1;

        for(int i = 60; i > -1; i--){
            if(i > nxt){
                ll h = pot[sum(i+1, bit)] - pot[sum(i, bit)]; h %= mod;
                if(h < 0) h += mod;
                ans += cans * h % mod; ans %= mod;
                continue;
            }
            assert(i == nxt);

            if(arr[i] < seq[j]) break;
            if(arr[i] > seq[j]) {
                ll h = pot[sum(i+1, bit)];
                ll hb = pot[sum(i, bit)];
    
                for(int k = seq[j]; k > -1; k--) {
                    h -= fat[arr[i]] * expo(fat[arr[i] - k] * fat[k] % mod, mod-2) % mod * hb % mod; h %= mod;
                    if(h < 0) h += mod;
                }

                ans += h * cans % mod; ans %= mod;
                
                cans *= fat[arr[i]] * expo(fat[arr[i] - seq[j]] * fat[seq[j]] % mod, mod-2) % mod;
                cans %= mod;
            }

            if(j+1 == seq.size()){
                ll h = cans * pot[sum(i, bit)] % mod;
                ans += h; ans %= mod;
                break;
            }

            nxt = i - seq[j+1];
            j += 2;
        }

        cout << ans % mod << endl;
    }


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