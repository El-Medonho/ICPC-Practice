#include "bits/stdc++.h"

using namespace std;
typedef long long ll;

#define endl '\n'

signed solve(){

    int n, v; cin >> n >> v;
    vector<pair<int,int>> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i].first;
    }
    for(int i = 0; i < n; i++){
        cin >> arr[i].second;
    }

    sort(arr.begin(), arr.end());

    if(v < 600){
        vector<ll> dp(v+1, 0LL);
        for(int i = 0; i < n; i++){
            for(int j = v; j >= arr[i].first; j--) dp[j] = max(dp[j], dp[j-arr[i].first] + arr[i].second);
        }

        cout << (*max_element(dp.begin(), dp.end())) << endl;
        return 0;
    }

    ll ans = 0;
    set<pair<ll,ll>> st;
    int b = 0;

    for(int i = 0; i < n; i++){
        ans = max(ans, (ll)arr[i].second);
        if(!st.empty()){
            auto it = st.upper_bound(make_pair(v-arr[i].first, 1));
            if(it != st.begin()){
                it--;
                ll vv = (*it).second;
                ans = max(ans, vv+arr[i].second);
            }
        }
        if(arr[i].second > b) st.emplace(arr[i].first, arr[i].second);
        b = max(b, arr[i].second);
    }

    vector<pair<int,int>> ch(0);

    int mm = v/3-36;

    v -= 3*mm;

    for(int i = 0; i < n; i++){
        ch.push_back(make_pair(arr[i].first - mm, arr[i].second));
    }

    vector<vector<ll>> dp(v+1, vector<ll>(4, 0));
    for(int i = 0; i < ch.size(); i++){
        for(int j = v; j >= ch[i].first; j--){
            for(int k = 3; k > 0; k--){
                if((k == 1) || (k > 1 && dp[j-ch[i].first][k-1] > 0)) dp[j][k] = max(dp[j][k], dp[j-ch[i].first][k-1] + ch[i].second);
            }
        }
    }

    ans = max(ans, (*max_element(dp[3].begin(), dp[3].end())));

    cout << ans << endl;

    return 0;
}

signed main(){
    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}