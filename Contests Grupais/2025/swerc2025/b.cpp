#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(){

    int n; cin >> n;

    ll l,r; cin >> l >> r;

    vector<ll> arr(n);
    for(ll &i: arr) cin >> i;
    sort(arr.begin(), arr.end());

    ll sl = 0, sr = 0;
    int pl = 1e9, pr = -1;

    for(int i = 0; i < n; i++){
        ll x = arr[i];
        if(x <= l || x >= r){
            sl += abs(x-l);
            sr += abs(x-r);
        }
        if(x > l && x < r) {pl = min(pl, i); pr = i;}
    }

    ll ans = min(sl, sr);


    while(pl <= pr){
        if(sl < sr){
            ll x = arr[pr--];
            sl += abs(x-l);
            sr -= abs(x-r);
        } else{
            ll x = arr[pl++];
            sl -= abs(x-l);
            sr += abs(x-r);
        }
        ans = max(ans, min(sl, sr));
    }

    cout << ans << endl;


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1; cin >> t;
    while(t--){
        solve();
    }


    return 0;
}