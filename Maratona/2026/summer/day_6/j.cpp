#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endl '\n'
using pii = pair<int,int>;

int n, m;
vector<vector<int>> g;
vector<int> color;

void colorize(int u, int c) {
  color[u] = c;
  queue<int> q;
  q.push(u);

  while(!q.empty()) {
    int u = q.front();
    q.pop();

    for(int v : g[u]) {
      if(!color[v]) {
        color[v] = color[u] != 1 ? 1 : 2;
        q.push(v);
      }
    }
  }
}

bool is_bipartite() {
  for(int u = 1; u <= n; u++) {
    if(!color[u]) colorize(u,1);
  }

  for(int u = 1; u <= n; u++) {
    for(int v : g[u]) {
      if(color[u] == color[v]) return false;
    }
  }
  return true;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(nullptr);

  cin >> n >> m;

  g = vector<vector<int>>(n+1);
  color = vector<int>(n+1);
  vector<pii> edges(m);

  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    edges[i] = {min(u,v), max(u,v)};
  }

  if(is_bipartite()) {
    cout << m << '\n';
    for(int i = 1; i <= m; i++) {
      cout << i << ' ';
    }
    cout << '\n';
    return 0;
  }

  vector<int> good;

  for(int i = 0; i < m; i++) {
    fill(color.begin(), color.end(), 0);
    auto [u,v] = edges[i];
    color[v] = 1;
    colorize(u,1);
    for(int u = 1; u <= n; u++) {
      if(!color[u]) colorize(u,1);
    }
    
    int cnt = 0;
    for(auto [u,v] : edges) {
      if(color[u] == color[v]) cnt++;
    }
    if(cnt == 1) good.push_back(i+1);
  }

  cout << good.size() << '\n';
  for(int x : good) cout << x << ' ';
  cout << '\n';
}