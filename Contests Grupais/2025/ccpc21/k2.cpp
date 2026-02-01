#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

int n, m, nodes;
ll v[1225], resp[55];
int dist[55];
vector<pair<int, int> > pai;
vector<pair<int, int> > vec[55];

void solve(){
    for(int i=1; i<=n; i++){
        dist[i] = n+1;
        resp[i] = 1e18;
    }
    queue<pair<int, pair<int, int> > > fila;
    dist[1] = 0;

    fila.push({1, {0, 0}});

    pai.push_back({0, 0});

    while(!fila.empty()){
        auto [u, temp] = fila.front();
        auto [d, node] = temp;
        fila.pop();

        if(u != 1){
            ll atual = 0;
            int a = node;
            unordered_map<int, int> mapa;
            while(a != 0){
                mapa[pai[a].second]++;
                atual += mapa[pai[a].second] * v[pai[a].second];
                a = pai[a].first;
            }
            resp[u] = min(resp[u], atual);
        }

        for(auto [i, c]:vec[u]){
            if(dist[i] >= dist[u] + 1){
                dist[i] = dist[u] + 1;
                pai.emplace_back();
                nodes++;
                pai[nodes] = {node, c};
                fila.push({i, {d+1, nodes}});
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;

    for(int i=0; i<m; i++){
        cin >> v[i];
    }

    for(int i=0; i<m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        c--;
        vec[a].push_back({b, c});
        vec[b].push_back({a, c});
    }

    solve();

    for(int i=2; i<=n; i++) cout << resp[i] << endl;

    return 0;
}