#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n), b(n), posA(n), posB(n);
        for(int i=0; i<n; i++){
            cin >> a[i];
            a[i]--;
            posA[a[i]] = i;
        }
        for(int i=0; i<n; i++){
            cin >> b[i];
            b[i]--;
            posB[b[i]] = i;
        }
        int can = 1;
        vector<pair<int, int> > resp;
        for(int x = n-1; x>=0; x--){
           // cout << x << endl;
            if(posB[x] < posA[x]){
                cout << -1 << endl;
                can = 0;
                break;
            }
            if(posA[x] == posB[x]){
                continue;
            }
            int maior = -1, posTemp = -1;
            vector<pair<int, int> > ord;
            for(int j=posA[x]+1; j<=posB[x]; j++){
                if(a[j]<x){
                    ord.push_back({a[j], j});
                }
            }
            int atual = posA[x];
            for(auto [u, j]:ord){
                if(j<atual) continue;
                resp.push_back({atual, j});
                swap(a[atual], a[j]);
                swap(posA[x], posA[u]);
                atual = j;
            }
            // for(int i=0; i<n; i++){
            //     cout << a[i] << ' ';
            // }
            // cout << endl;
            // for(int i=0; i<n; i++){
            //     cout << posA[i] << ' ';
            // }
            // cout << endl << endl;
        }
        if(!can) continue;
        cout << resp.size() << endl;
        for(auto [a, b]:resp){
            cout << a+1 << ' ' << b+1 << endl;
        }
    }

    return 0;
}