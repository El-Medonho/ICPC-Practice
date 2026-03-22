#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(int T){

    int n; cin >> n;
    int k; cin >> k;

    vector<int> occ(4*n+2, 0), sum(4*n+2, 0);
    set<int> z;

    for(int i = 0; i < n; i++){
        int a; cin >> a;
        occ[a]++;
    }

    int N = 4*n;

    for(int i = 0; i <= N; i++) {
        if(occ[i] == 0) z.insert(i);
    }

    int ans = 0;
    stack<pair<int,int>> stk;

    for(int i = 2*n+1; i > 0; i--){
        int cc = occ[i];
        if(cc <= k){
            if(cc > 0) stk.emplace(i, cc-1);
            continue;
        }

        
        cc -= 1;
        int b = i;

        b = (*z.upper_bound(b));
        while(!stk.empty() && b >= stk.top().first){
            cc += stk.top().second; stk.pop();
        }

        while(cc > k){
            while(!z.empty() && cc > k){
                cc--;
                z.erase(z.find(b));
                b = (*z.upper_bound(b));

                // if(T == 1) cout << cc << ' ' << b << endl;
            }
            
            // cout << stk.size() << endl;
            while(!stk.empty() && b >= stk.top().first){
                cc += stk.top().second; stk.pop();
            }
        }
        // b = (*z.upper_bound(b));
        // if(T == 1) cout << i << ' ' << cc << ' ' << b << endl;
        stk.emplace(b, cc);
        
        ans = max(ans, b - i);
    }

    cout << ans << endl;


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1; 
    cin >> t;
    for(int i = 1; i <= t; i++){
        solve(i);
    }


    return 0;
}