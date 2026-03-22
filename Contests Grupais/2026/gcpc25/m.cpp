#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    ll d, s, e; cin >> d >> s >> e;
    double dd, ss, ee; dd = d, ee = e, ss = s;

    double sum = ee/dd;
    vector<double> arr(d-e, 1/dd);
    double ans = 0;

    for(int i = 0; i < d-s-e; i++) arr[i] += sum/(d-s-e);

    for(int i = 0; i < s; i++) ans += arr[i];

    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}