#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endl '\n'

set<int> p;

ll expo(ll b, ll e, ll m){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b%m;
        b = b*b%m;
        e>>=1;
    }
    return ans;
}

signed solve(int is = -1, int dd = 0, int nn = 0, vector<int> aa = {}){
  map<int,int> mp;
  int d = 0,n = 0;
  vector<int> arr(n);
  cin >> d >> n;
  arr.resize(n);
  
  for(int &i: arr) cin >> i;
  
  for(int i = 0; i < n-1; i++){
    mp[arr[i]] = arr[i+1];
  }
  
  if(n == 1){
    cout << "I don't know.\n";
    return -1;
  }

  if(mp.find(arr.back()) != mp.end()) {
    cout << mp[arr.back()] << '\n';
    return 0;
  }
  
  if(d <= 2){
    // vector<int,pair<int,int>> ans(0);
    set<int> ans;
    int mx = 10;
    if(d == 2) mx = 100;
    if(d == 3) mx = 1000;

    for(int j: p){
      if(j > mx) break;
      for(int a = 0; a < j; a++){
        for(int b = 0; b < j; b++){
          bool ok = true;
          for(int i = 0; i < n-1; i++){
            if(arr[i+1] != ((a*arr[i] + b) % j)) ok = false;
          }
          if(ok) ans.insert((a*arr.back() + b) % j);
        }
      }

    }
    if(ans.size() != 1){
      cout << "I don't know.\n";
      return -1;
    }

    cout << (*ans.begin()) << endl;
    return (*ans.begin());
  }

  int mx_ = (*max_element(arr.begin(), arr.end()));
  vector<int> primes(0);
  int up = 1000;
  if(d == 4) up = 10000;
  if(d == 5) up = 100000;
  if(d == 6) up = 1000000;

  if(n <= 2){
    cout << "I don't know.\n";
    return -1;
  }

  for(auto it = p.upper_bound(mx_); it != p.end(); it++){
    if((*it) > up) break;
    primes.push_back((*it));
  }

  set<int> ans;

  for(int pp: primes){
    ll x = arr[0]; ll y = arr[1], z = arr[2];

    ll a = ((ll)y-z) * expo(x-y, pp-2, pp) % pp;
    if(a < 0) a += pp;
    ll b = y - x*a; b %= pp;
    if(b < 0) b += pp;
    bool ok = true;
    for(int i = 1; i < n; i++){
        if(arr[i] != ((arr[i-1] * a + b) % pp)) ok = false;
    }
    if(ok) ans.insert((a*arr.back() + b) % pp);
  }

    if(ans.size() != 1){
        cout << "I don't know.\n";
        return -1;
    }

    cout << (*ans.begin()) << endl;
    return (*ans.begin());  


  return 0;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(nullptr);

  vector<int> seen(1e6+5, 0);

  for(int i = 2; i < 1e6; i++){
    if(seen[i] == 0) p.insert(i);
    for(int j = i; j < 1e6; j+=i) seen[j] = 1;
  }

  bool local = false;

  if(!local){
    int t; cin >> t;
    for(int i = 1; i <= t; i++){
      cout << "Case #" << i << ": ";
      solve();
    }
  }


  return 0;
}