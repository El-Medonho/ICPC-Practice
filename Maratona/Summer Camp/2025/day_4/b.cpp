#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t; cin >> t;

    vector<int> sieve(4e7+5, 0);

    for(int i = 2; i <= 4e7+2; i++){
        if(sieve[i]) continue;
        for(int j = i; j <= 4e7+2; j+=i){
            sieve[j]++;
        }
    }

    while(t--){
        ll c,d,x; cin >> c >> d >> x;
    
        vector<ll> div; div.reserve(512);
    
        for(ll i = 1; i*i<=x; i++){
            if(x%i == 0){
                div.push_back(i); 
                if(i*i != x) div.push_back(x/i);
            }
        }
    
        ll ans = 0;
    
        for(ll k: div){
            ll cc = c*k, dd = d*k;
            if((x+dd)%cc != 0) continue;
            
            ll p = (x+dd)/cc;
            
            ll cnt = sieve[p];
            
            ll cans = 1LL<<cnt;
            // cout << cc << ' ' << dd << ' ' << p << ' ' << sieve[p] << ' ' << cans << endl;
            
            ans += cans;
        }
    
        cout << ans << endl;
    }



    return 0;
}