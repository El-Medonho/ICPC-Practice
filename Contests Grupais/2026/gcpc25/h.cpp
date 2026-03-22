#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n,s1,s2; cin >> n >> s1 >> s2;

    vector<int> arr1(s1), arr2(s2);

    for(int &i: arr1) cin >> i;
    for(int &i: arr2) cin >> i;

    set<pair<int,int>> st; st.emplace(0, 0);
    vector<int> mp(n+2, -1);
    mp[0] = 0;

    for(int i: arr1){
        if(i == 0) i = n+1;
        int cc = st.size();
        mp[i] = cc;
        st.emplace(cc, i);
    }

    while(!arr2.empty()){
        int i = arr2.back(); arr2.pop_back();
        if(i == 0) i = n+1;
        int cc = st.size();
        mp[i] = cc;
        st.emplace(cc, i);
    }

    auto barra = st.find({arr1.size(), arr1.back()});
    int ans = 0;

    for(int i = 1; i <= n; i++){
        barra = --st.find({mp[i], i});
        st.erase({mp[i], i});
        if(barra == (st.find({mp[n+1], n+1})) || (barra) == (--st.find({mp[n+1], n+1}))) ans++;
    }

    cout << ans << endl;

    return 0;
}