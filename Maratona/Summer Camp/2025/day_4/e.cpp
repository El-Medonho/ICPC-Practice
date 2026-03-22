#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin >> n;

    vector<int> arr(n), mn(200005, 40), mn2(200005, 40), freq(200005, 0);

    for(int &i: arr) cin >> i;

    for(int x: arr){
        int cnt = 0;
        while(x%2 == 0){
            cnt++; x/=2;
        }
        if(cnt) freq[2]++;

        if(cnt && cnt < mn[2]){
            swap(mn[2], mn2[2]);
            mn[2] = cnt;
        } else if(cnt && cnt < mn2[2]) mn2[2] = cnt;

        cnt = 0;
        for(int i = 3; i * i <= x; i+=2){
            while(x%i == 0){
                cnt++;
                x/=i;
            }
            if(!cnt) continue;
            // cout << i << ' ';
            freq[i]++;
            if(cnt < mn[i]){
                swap(mn[i], mn2[i]);
                mn[i] = cnt;
            } else if(cnt < mn2[i]) mn2[i] = cnt;

            cnt = 0;
        }

        if(x > 1){
            freq[x]++; cnt = 1;
            if(cnt < mn[x]){
                swap(mn[x], mn2[x]);
                mn[x] = cnt;
            } else if(cnt < mn2[x]) mn2[x] = cnt;
            // cout << x << ' ';

            cnt = 0;
        }
        // cout << endl;
    }

    ll ans = 1;

    for(int i = 2; i < 200002; i++){
        if(freq[i] <= n-2) mn2[i] = 0;
        else if(freq[i] == n-1) swap(mn2[i], mn[i]);

        for(int j = 0; j < mn2[i]; j++) ans *= i;
    }
    // cout << freq[2] << ' ' << mn2[5] << endl;

    cout << ans << endl;

    return 0;
}