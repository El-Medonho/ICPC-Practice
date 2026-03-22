#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin >> n;

    map<char, string> mp;

    vector<string> arr(n);

    for(int i = 0; i < n; i++){
        string s; cin >> s;
        mp[s[0]] = s;
        arr[i] = s;
    }

    for(string s: arr){
        bool ok = true;
        for(char c: s){
            if(mp.find(c) == mp.end()){
                ok=  false;
                break;
            }
        }

        if(ok){
            cout << s.size() << endl;
            for(char c: s) cout << mp[c] << ' ';
            cout << endl;
            return 0;
        }
    }

    cout << -1 << endl;


    return 0;
}