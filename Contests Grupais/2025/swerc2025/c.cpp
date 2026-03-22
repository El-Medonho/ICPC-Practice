#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed solve(){

    int n,m; cin >> n >> m;

    if(n % 2 == 0){
        set<vector<int>> st;
        for(int i = 0; i < n; i++){
            vector<int> arr(m);
            for(int j = 0; j < m; j++){
                cin >> arr[j];
            }
            st.insert(arr);
        }

        for(vector<int> x: st) {
            for(int a: x) cout << a << ' ';
        }
        cout << endl;
        return 0;
    }

    map<int,int> l, r;

    vector<vector<int>> arr(n, vector<int>(m));
    int md = (m/2);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }

        l[arr[i][0]] = i;
        r[arr[i][md]] = i;
    }

    if(n == 1){
        for(int j = 0; j < m/2; j++) cout << arr[0][j] << ' ';
        cout << endl;
        return 0;
    }

    for(int i = 0; i < n; i++){
        vector<int> ansl(0), ansr(0);
        ansl.reserve(n/2), ansr.reserve(n/2);

        int cc = arr[i][md];
        int cnt = 0;
        // cout << cc << ' ';
        while(cnt < n/2){
            if(l.find(cc) == l.end()) break;
            ansl.push_back(l[cc]);
            cc = arr[l[cc]][md];
            // cout << cc << ' ';

            if(l.find(cc) == l.end()) break;
            ansr.push_back(l[cc]);
            cc = arr[l[cc]][md];
            cnt++;
            // cout << cc << ' ';
        }
        // cout << endl;

        if(cnt == n/2){
            vector<int> ans; ans.reserve(n*m);
            ansl.push_back(i);
            for(int x: ansr) ansl.push_back(x);

            for(int i: ansl){
                for(int j: arr[i]) ans.push_back(j);
            }

            for(int i = 0; i < n*m/2; i++) cout << ans[i] << ' ';
            cout << endl;
            return 0;
        }
    }

    assert(false);
    cout << "NO\n";


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }


    return 0;
}