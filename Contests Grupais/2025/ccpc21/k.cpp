#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
typedef long long ll;

const int mxn = 50*50;

int n, m;
ll v[mxn], resp[55];
int dist[55];
vector<int> pai;

vector<vector<pair<int, int> >> vec(55), vec2(55);

// unordered_map<array<int, 1225>, int> who;

void solve(){
    for(int i=1; i<=n; i++){
        dist[i] = n+1;
        resp[i] = 1e18;
    }
    queue<pair<pair<int,ll>, pair<int, unordered_map<int, int> > > > fila;
    dist[1] = 0;

    unordered_map<int, int> temp;
    fila.push({{1, 0LL}, {0, temp}});

    while(!fila.empty()){
        auto [temp2, temp] = fila.front();
        auto [u, atual] = temp2;
        auto [d, comp] = temp;
        fila.pop();

        resp[u] = min(resp[u], atual);

        // if(u != 1){
        //     ll atual = 0;
        //     //cout << d << endl;
        //     for(auto [k, va] : comp){
        //         ll freq = va;
        //        // cout << freq << ' ';
        //         atual += (1LL + freq) * freq / 2LL * v[k];
        //     }
        //    // cout << endl << endl;
        //     resp[u] = min(resp[u], atual);
        // }

        for(auto [i, c]:vec[u]){
            if(dist[i] >= dist[u] + 1){
                dist[i] = dist[u] + 1;
                comp[c-1]++; atual += comp[c-1] * v[c-1];
                fila.push({{i, atual}, {d+1, comp}});
                atual -= comp[c-1] * v[c-1];
                comp[c-1]--; 
                if(!comp[c-1]) comp.erase(c-1);
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
        vec[a].push_back({b, c});
        vec[b].push_back({a, c});
    }

    queue<int> qw;
    qw.push(1);
    vector<int> dist(n+1, 100); dist[1] = 0;

    while(!qw.empty()){
        int cc = qw.front(); qw.pop();

        for(auto[j, c]: vec[cc]){
            if(dist[j] > dist[cc]) {vec2[cc].push_back({j, c});}
            if(dist[cc]+1 >= dist[j]) continue;
            dist[j] = dist[cc]+1;
            qw.push(j);
        }
    }

    vec = vec2;

    solve();

    for(int i=2; i<=n; i++) cout << resp[i] << endl;

    return 0;
}