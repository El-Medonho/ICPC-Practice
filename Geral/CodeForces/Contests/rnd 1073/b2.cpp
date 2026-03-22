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

signed solve(){
    
    int n; cin >> n;

    string s; cin >> s;

    // dp[sum][state][csum]
    vector<vector<vector<ll>>> dp(n+5, vector<vector<ll>>(10, vector<ll>(n+5, 0LL)));
    dp[0][0][0] = 1;

    for(char c: s){
        auto dp2 = dp;
        if(c == '('){
            for(int i = n+2; i > -1; i--){
                for(int st = 4; st > -1; st-=2){
                    for(int cs = n+2; cs > -1; cs--){
                        dp2[i+1][st][cs+1] += dp[i][st][cs];
                        if(dp2[i+1][st][cs+1] >= mod) dp2[i+1][st][cs+1] -= mod;
                    }
                }

                for(int st = 5; st > -1; st-=2){
                    for(int cs = n+2; cs > -1; cs--){
                        if(st != 5){
                            dp2[i+1][st+1][0] += dp[i][st][cs];
                            if(dp2[i+1][st+1][0] >= mod) dp2[i+1][st][0] -= mod;
                        }

                        if(st == 5){
                            dp2[i+1][st-1][0] += dp[i][st][cs];
                            if(dp2[i+1][st-1][0] >= mod) dp2[i+1][st][0] -= mod;
                        }
                    }
                }
            }
        } else {
            for(int i = n+2; i > 1; i--){
                for(int st = 5; st > -1; st-=2){
                    for(int cs = n+2; cs >= 1; cs--){
                        dp2[i-1][st][cs] += dp[i][st][cs];
                        if(dp2[i-1][st][cs] >= mod) dp2[i-1][st][cs] -= mod;
                    }
                }

                for(int st = 4; st > -1; st-=2){
                    for(int cs = n+2; cs > -1; cs--){
                        dp2[i-1][st+1][cs] += dp[i][st][cs];
                        if(dp2[i-1][st+1][cs] >= mod) dp2[i-1][st+1][cs] -= mod;
                    }
                }
            }
        }

        dp = dp2;
    }

    ll ans = 0;


    // dp[0][3,5][se 3, cs > 1]
    for(int i = 0; i < n+2; i++) {
        if(i > 1) ans += dp[0][3][i];
        ans += dp[0][5][i];
    }

    cout << ans % mod << endl;


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