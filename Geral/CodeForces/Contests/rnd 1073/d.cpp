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

ll expo(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b%mod;
        b = b*b%mod;
        e>>=1;
    }
    return ans;
}

signed solve(){
    ll n,m; cin >> n >> m;
    ll k = n-m;

    vector<ll> repr(n), peso(n, 1);
    for(int i = 0; i < n; i++) repr[i] = i;

    auto ff = [&](auto&&self, int x) -> int{
        if(repr[x] == x) return x;
        return repr[x] = self(self, repr[x]);
    };

    auto uu = [&](int x, int y) -> void{
        x = ff(ff, x);
        y = ff(ff, y);
        if(x == y) return;

        if(peso[x] < peso[y]) swap(x, y);
        peso[x] += peso[y];
        repr[y] = x;
    };

    vector<vector<int>> graph(n);
    for(int i = 0; i < m; i++){
        int a,b; cin >> a >> b; a--; b--;
        uu(a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<ll> ans(n-1, 0LL);
    set<int> st;
    for(int i = 0; i < n; i++){
        int x = ff(ff, i);
        st.insert(x);
    }
    
    ll tot = 1;
    if(k > 1){
        tot = expo(n, k-2);
        for(int x: st) tot = tot * peso[x] % mod;
    }

    ll sobra = tot;

    if(ff(ff, n-2) == ff(ff, n-1)){

        auto dfs = [&](auto&& self, int x, int last) -> bool{
            if(x == n-2) return true;

            for(int j: graph[x]){
                if(j == last) continue;
                if(self(self, j, x)) {
                    if(x == n-1) ans[j] = tot;
                    return true;
                }
            }

            return false;
        };

        dfs(dfs, n-1, n-1);

        for(ll i: ans) cout << i << ' ';
        cout << endl;
        return 0;
    }

    auto dfs = [&](auto&& self, int x, int last) -> int{
        if(x == n-2) return true;

        int cont = 1;
        for(int j: graph[x]){
            if(j == last) continue;
            int qtt = self(self, j, x);
            if(x == n-1) {
                ans[j] = tot * expo(peso[ff(ff, n-1)], mod-2) % mod * qtt % mod;
                sobra -= ans[j]; 
                if(sobra < 0) sobra += mod;
            }

            cont += qtt;
        }

        return cont;
    };

    dfs(dfs, n-1, n-1);

    for(int i = 0; i < n-1; i++){
        int pai = ff(ff, i);
        if(pai != ff(ff, n-1) && pai != ff(ff, n-2)) {
            ans[i] = tot * expo(peso[ff(ff, n-1)] * n % mod, mod-2) % mod;
            sobra -= ans[i]; 
            if(sobra < 0) sobra += mod;
        }
    }

    sobra %= mod;
    sobra = sobra * expo(peso[ff(ff, n-2)], mod-2) % mod;
    if(sobra < 0) sobra += mod;

    for(int i = 0; i < n-1; i++){
        int pai = ff(ff, i);
        if(pai != ff(ff, n-1) && pai == ff(ff, n-2)) {
            ans[i] = sobra;
        }
    }

    for(ll i: ans) cout << i << ' ';
    cout << endl;


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }    

    return 0;
}