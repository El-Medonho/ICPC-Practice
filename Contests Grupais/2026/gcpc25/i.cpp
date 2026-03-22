#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;

bool dp[205][11][11][11][11];


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n,m; cin >> n >> m;

    vector<vector<vector<int>>> f(m+1, vector<vector<int>>(m+1, vector<int>(m+1)));
    
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= m; k++){
                cin >> f[i][j][k];
            }
        }
    }

    vector<int> arr(n);
    for(int &i: arr) cin >> i;

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= m; k++){
                if(f[i][j][k] == arr[0]) dp[0][i][j][j][k] = 1;
            }
        }
    }

    for(int g = 0; g < n-1; g++){
        for(int i = 1; i <= m; i++){
            for(int q = 1; q <= m; q++){
                for(int j = 1; j <= m; j++){
                    for(int k = 1; k <= m; k++){
                        if(dp[g][i][q][j][k] == 0) continue;
                        for(int p = 1; p <= m; p++){
                            if(f[j][k][p] != arr[(g+1)]) continue;
                            if(g == n-3 && p == i) {
                                dp[g+1][i][q][k][p] = 1;
                            } else if(g == n-2 && p == q){
                                cout << "YES\n";
                                return 0;
                            } else if(g < n-3){
                                dp[g+1][i][q][k][p] = 1;
                            }
                        }
                    }
                }

            }
        }
    }

    cout << "NO\n";
    

    return 0;
}