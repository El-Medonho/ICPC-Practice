#include "bits/stdc++.h"
using namespace std;
 
#define MOD 1000000009
#define mod(x,m) (((x%m)+m)%m)
#define f first
#define s second
#define pb push_back
#define pii pair<int,int>
#define vii vector<int>
#define vss vector<string>
#define vll vector<long long>
#define endl "\n"
#define esp " "
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3f
#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr)
typedef long long ll;
 
vector<int> z_function(string s) {          
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
 
int main(){
    fastio;
 
    string s;
    cin >> s;
 
    if(s.size() == 1) return 0;
    vii ans;
    vii z = z_function(s);
    int tamanho = s.size();
    for(int i = 1; i < s.size(); i++){
        if(z[i] == tamanho-i) ans.pb(z[i]);
    }
    reverse(ans.begin(), ans.end());
 
    for(auto x: ans) cout << x << esp;
    cout << endl;
 
    return 0;
}