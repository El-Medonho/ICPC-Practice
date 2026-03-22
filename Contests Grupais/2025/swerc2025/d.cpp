#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(){
    int n; cin >> n;
    vector<int> arr(n+1);

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        arr[x]++;
    }

    int ans = 0;

    for(int i = 0; i <= n; i++){
        if(arr[i] >= i) ans += arr[i]-i;
        else ans += arr[i];
    }

    cout << ans << endl;

    


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