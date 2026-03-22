#include "bits/stdc++.h"

using namespace std;

// #define endl '\n'
typedef long long ll;
typedef tuple<int,int,int> tii;

const int lim = 1e9, high = 5e4;
const __int128_t inf = 1e30;
map<int,tii> mp;
map<tii, bool> vis;

void find(__int128_t x, int a, int b, int c){
    if(vis[{a, b, c}] == 1) return;
    vis[{a, b, c}] = 1;
	if(x <= lim) {
		if(mp.find((int)x) == mp.end()) mp[x] = {a, b, c};
		else mp[x] = min(mp[x], {a, b, c});
	}

    if(inf/x >= (a+1) && a+1 <= high) find(x*(a+1), a+1, b, c);
    if(x%(b+1) == 0 && b+1 < a) find(x/(b+1), a, b+1, c);
    if(c+1 <= b && x%(c+1) == 0) find(x/(c+1), a, b, c+1);
    // cout << x << ' ' << a << ' ' << b << ' ' << c << endl; 
}

signed solve(int TEST_CASE){

    int n; cin >> n;

	find(6, 4, 2, 2);
    for(int a = 100; a <= high; a++){
		ll cc = 1;
        for(int b = a; b > a-4; b--){
			cc *= b;
			ll temp = cc;
			for(int c = 2; c < 30; c++){
				if(temp % c != 0) break;
				temp /= c;
				if(temp <= lim) find(temp, a, b-1, c);
			}
		}
    }

    
    if(mp.find(n) == mp.end()) cout << "-1 -1 -1\n";
    else{
        cout << get<0>(mp[n]) << ' ' << get<1>(mp[n]) << ' ' << get<2>(mp[n]) << endl; 
    }

    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    for(int i = 1; i <= t; i++) solve(i);

    return 0;
}