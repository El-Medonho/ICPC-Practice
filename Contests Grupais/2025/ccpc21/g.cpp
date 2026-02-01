#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(){
    int n; cin >> n;

    string s; cin >> s;

    ll ans = 1e9;

    int l = 0, r = n;

    while(l <= r){
        int md = (l+r)/2;
        bool ok = true;

        bool ll = false, l_alone = false;
        int cc = 0;

        for(int i = 0; i < n; i++){
            char c = s[i];
            if(c == '0') {cc++; continue;}
            else {
                bool r_alone = false;
                if(i < n-1 && s[i+1] == '0') r_alone = true;

                int cost = cc;
                if(l_alone) cost++;
                if(r_alone) cost++;

                int real_cost = cost;
                if(ll) real_cost = (real_cost+1)/2;

                if(real_cost <= md){
                    ll = true;
                    l_alone = false;
                    cc = 0;
                    continue;
                }

                if(r_alone) cost--;
                real_cost = cost;
                if(ll) real_cost = (real_cost+1)/2;

                if(real_cost > md){
                    ok = false;
                    break;
                }

                ll = true;
                l_alone = true;
                cc = 0;
            }
        }

        if(cc > 0 && ok){
            int cost = cc;
            if(l_alone) cost++;
            if(cost > md) ok = false;
        }

        // cout << l << ' ' << r << ' ' << md << ' ' << ok << endl;

        if(ok){
            ans = md;
            r = md-1;
        } else{
            l = md+1;
        }
    }

    cout << ans << endl;


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}