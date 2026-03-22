#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t; cin >> t;
    
    while(t--){
        int a,b,p,q; cin >> a >> b >> p >> q;

        a--; b--; p--; q--;
        int d = 1+p-b;

        if(b != a+1 || q != p+1 || (q-b != p-a) || d <= 1){
            cout << -1 << endl;
            continue;
        }

        if(a/d != b/d || p/d != q/d) cout << -1 << endl;

        else {
            cout << 100000 << ' ' << d << endl;
        }
    }


    return 0;
}