#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;
typedef double ld;

void upd(int x, ld v, vector<ld> &bit){
    for(;x < bit.size(); x+=x&-x) bit[x] = max(bit[x], v);
}

ld sum(int x, vector<ld> &bit){
    ld ans = 0;
    for(; x; x-=x&-x) ans = max(ans, bit[x]);
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin >> n;

    vector<ld> bit(n+5, 0);

    for(int i = 1; i <= n; i++){
        ld x; cin >> x;
        ld b = x*i;
        b += sum(i, bit) * (1-x);
        upd(i, b, bit);
    }

    cout << fixed << setprecision(10) << sum(n, bit) << endl;

    return 0;
}