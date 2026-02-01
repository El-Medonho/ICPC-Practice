#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

const int mxn = 2e3+5;

int n, m, c, dist[mxn];

vector<pair<int, int> > vec[mxn];

int dj(int x){
    memset(dist, (int)1e9+5, sizeof(dist));

    dist[x] = 0;

    priority_queue<pair<int, int> > fila;
    fila.push({0, x});

    int can = 0;

    int menor = 1e9+5;

    while(!fila.empty()){
        auto [d, u] = fila.top();
        fila.pop();
        d*=-1;

        if(u != x && d<=c) can = 1;

        if(d > dist[u]) continue;

        for(auto [i, c]:vec[u]){
            if(dist[i] > d + c){
                dist[i] = d + c;
                fila.push({-(d + c), i});
            }
            if(i == x){
                menor = min(menor, d + c);
            }
        }
    }
    if(menor <= c) return 2;
    return can;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m >> c;
    
    for(int i=0; i<m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        vec[a].push_back({b, c});
    }
    int maior = 0;
    for(int i=1; i<=n; i++){
        maior = max(maior, dj(i));
    }
    cout << maior << endl;
    return 0;
}