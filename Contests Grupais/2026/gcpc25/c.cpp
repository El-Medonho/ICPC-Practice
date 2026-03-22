#include <bits/stdc++.h>
 
using namespace std;

#define f first
#define s second
#define pb push_back
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> pip;
typedef unsigned long long ull;
const int mxn = 1e4+5;
const int mxm = 1e5+5;
const int MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3f;

// Returns -1 if a < b, 0 if a = b and 1 if a > b.
int cmp_double(double a, double b = 0, double eps = 1e-9) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

signed cases(){
    int n;
    cin >> n;

    vector<pair<ll, pair<ll, ll> > > v(n);

    for(int i=0; i<n; i++){
        string s; cin >> s;
        reverse(s.begin(), s.end());
        v[i].first = 0;
        int cnt = 1;
        for(int j = 0; j < s.size(); j++){
            if(j == 2) continue;
            v[i].first += (s[j]-'0') * cnt;
            cnt *= 10;
        }
        cin >> v[i].second.first >> v[i].second.second;
    }
    
    sort(v.begin(), v.end());
    
    vector<ll> prefix(n), suffix(n);
    prefix[0] = v[0].second.second;
    for(int i=1; i<n; i++){
        prefix[i] = prefix[i-1] + v[i].second.second;
    }
    suffix[n-1] = v[n-1].second.first;
    for(int i=n-2; i>=0; i--) suffix[i] = suffix[i+1] + v[i].second.first;

    ll maior=0;
    int pos = -1;
    for(int i=0; i<n; i++){
        if(v[i].first * min(prefix[i], suffix[i]) > maior){
            maior = v[i].first * min(prefix[i], suffix[i]);
            pos = i;
        }
    }
    if(pos == -1){
        cout << "impossible" << endl;
        return 0;
    }

    ll cc = v[pos].first;

    string ans1 = "", ans2 = "";

    while(cc) {
        ans1.push_back((cc%10) + '0');
        cc/=10;
        if(ans1.size() == 2) ans1.push_back('.');
    }

    if(ans1.size() == 0) ans1.push_back('0');
    if(ans1.size() == 1) ans1.push_back('0');
    if(ans1.size() == 2) ans1.push_back('.');
    if(ans1.size() == 3) ans1.push_back('0');
    reverse(ans1.begin(), ans1.end());

    cc = maior;

    while(cc) {
        ans2.push_back((cc%10) + '0');
        cc/=10;
        if(ans2.size() == 2) ans2.push_back('.');
    }

    if(ans2.size() == 0) ans2.push_back('0');
    if(ans2.size() == 1) ans2.push_back('0');
    if(ans2.size() == 2) ans2.push_back('.');
    if(ans2.size() == 3) ans2.push_back('0');
    reverse(ans2.begin(), ans2.end());


    cout << ans1 << ' ' << ans2 << endl;
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t=1;

    //cin >> t;

    for(int i=1; i<=t; i++){
        //cout << "Case #" << i << ": ";
        cases();
    }
    return 0;
}