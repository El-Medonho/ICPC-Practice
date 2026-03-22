#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

const int mod = 998244353;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    vector<int> p;

    vector<int> sieve(1e6+5, 0);
    for(int i = 2; i < 1e6+2; i++){
        if(sieve[i]) continue;
        p.push_back(i);
        for(int j = i; j < 1e6+2; j+=i) sieve[j] = 1;
    }

    ll ans = 1;

    ll n,m; cin >> n >> m;

    for(int x: p){
        ll sm = 0, snm = 0, sn = 0;

        ll mm = m, nm = n-m, nn = n;

        while(mm){
            sm += (mm % x);
            mm /= x;
        }

        while(nm){
            snm += (nm % x);
            nm /= x;
        }

        while(nn){
            sn += (nn % x);
            nn /= x;
        }

        ll b = (sm + snm - sn) / (x-1);

        // if(x > m) assert(b == 0);

        ans *= b+1;
        ans %= mod;
    }

    ll mx = max(m, n-m);
    vector<ll> mp(n-mx+5);

    for(ll i = n; i > mx; i--) {mp[i-mx] = i;}

    set<ll> st;
    for(int x: p){
        st.insert(x);
        ll j = n/x*x;
        for(; j > mx; j-=x) {
            while(mp[j-mx] % x == 0) mp[j-mx] /= x;
        }
    }
    st.insert(1);

    for(ll i = n; i > mx; i--){
        if(st.find(mp[i-mx]) != st.end()) continue;
        st.insert(mp[i-mx]);
        // cout << mp[i] << endl;
        ans *= 2;
        ans %= mod;
    }

    cout << ans << endl;

    return 0;
}