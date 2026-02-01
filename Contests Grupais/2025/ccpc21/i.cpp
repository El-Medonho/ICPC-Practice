#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int remaining = 0;
        ll ans = 0;

        for(int i = n-1; i >= 0; i--) {
            if(s[i] == '1') {
                if(remaining > 0) {
                    ans += i+1;
                    remaining--;
                }
                else remaining++;
            }else {
                remaining++;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}