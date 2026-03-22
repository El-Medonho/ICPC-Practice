#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

const int mod = 1e9+7;

ll expo(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b%mod;
        b = b*b%mod;
        e>>=1;
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<ll> arr(n);
    for(ll &i: arr) cin >> i;

    sort(arr.begin(), arr.end());

    ll sum1 = 0, sum2 = 0;
    ll c1 = 0, c2 = 0;

    ll last1 = -1, last2 = -1;
    for(int i = 0; i < k; i++){
        sum1 += arr[i];
        if(last1 != arr[i]) {
            last1 = arr[i];
            c1 = 1;
        } else c1++;
    }

    for(int i = n-1, cnt = 0; cnt < k; i--, cnt++){
        sum2 += arr[i];
        if(last2 != arr[i]) {
            last2 = arr[i];
            c2 = 1;
        } else c2++;
    }

    ll cnt = 0;

    vector<ll> fat(n+5, 1);
    for(int i = 2; i <= n+2; i++) fat[i] = fat[i-1] * i % mod;

    cout << sum2-sum1 << ' ';

    if(last1 != last2) {
        ll cnt1 = count(arr.begin(), arr.end(), last1), cnt2 = count(arr.begin(), arr.end(), last2);
        ll ans = fat[cnt1] * expo(fat[c1] * fat[cnt1-c1] % mod, mod-2) % mod;

        ans *= fat[cnt2] * expo(fat[c2] * fat[cnt2-c2] % mod, mod-2) % mod;

        ans %= mod;

        cout << ans << endl;

        return 0;
    }

    for(int i = 0; i < n; i++){
        if(arr[i] == last1) cnt++;
    }

    ll ans = fat[cnt] * expo(fat[c1] * fat[c2] % mod * fat[cnt-c1-c2] % mod, mod-2) % mod;

    if(count(arr.begin(), arr.end(), last1) == n) ans *= expo(2, mod-2);

    ans %= mod;

    cout << ans << endl;


    return 0;
}