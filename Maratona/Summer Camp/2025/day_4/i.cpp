#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin >> n;

    vector<vector<ll>> s2(n, vector<ll>(n, 1e18));
    for(int i = 0; i < n; i++) s2[i][i] = 0;
    vector<vector<ll>> s1 = s2, s0 = s2, f = s2;

    int m; cin >> m;
    while(m--){
        ll a,b,c,d; cin >> a >> b >> c >> d; a--; b--;
        if(d >= 2) s2[a][b] = min(s2[a][b], c);
        if(d >= 1) s1[a][b] = min(s1[a][b], c);
        if(d >= 0) s0[a][b] = min(s0[a][b], c);
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                s2[i][j]=min(s2[i][j], s2[i][k] + s2[k][j]);
                s1[i][j]=min(s1[i][j], s1[i][k] + s1[k][j]);
                s0[i][j]=min(s0[i][j], s0[i][k] + s0[k][j]);
            }
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                f[i][j] = min(f[i][j], s2[i][k] + 2*s1[k][j] + s0[j][k]);
            }
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(f[i][j] == 1e18) cout << -1 << ' ';
            else cout << f[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}