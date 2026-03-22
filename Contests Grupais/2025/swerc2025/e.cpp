#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(){

    int n,q; cin >> n >> q;
    string s; cin >> s;

    vector<int> sum(n+1, 0);

    for(int i = 0; i < n; i++){
        sum[i+1] = sum[i];
        if(s[i] == '8') sum[i+1]++;
    }

    while(q--){
        ll l, r, x, y; cin >> l >> r >> x >> y; l--;
        x = abs(x), y = abs(y);
        ll mn = min(x, y);
        ll ans = x+y;
        ans -= r-l;
        ans -= min(mn, (ll) sum[r]-sum[l]);

        if(ans <= 0) cout << "YES\n";
        else cout << "NO\n";
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