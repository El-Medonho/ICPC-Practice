#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    ll n; cin >> n;

    if(n <= 5){
        cout << 1 << endl;
        return 0;
    } else if(n <= 9){
        cout << 5 << endl;
        return 0;
    } 

    ll b = -1, cnt = 0;
    n--;

    for(int i = 0; i < 60; i++){
        if(n & (1LL<<i)){
            ll cc = 1LL<<i;
            if(cnt == 1){
                if(2*cc > n) break;
                cout << "impossible\n";
                return 0;
            }
            cnt++;
            if(cc == n) b = n/2;
            else {b = cc;}
        }
    }

    cout << b+1 << endl;

    return 0;
}