// ⢸⣿⣿⣿⣿⠃⠄⢀⣴⡾⠃⠄⠄⠄⠄⠄⠈⠺⠟⠛⠛⠛⠛⠻⢿⣿⣿⣿⣿⣶⣤⡀⠄
// ⢸⣿⣿⣿⡟⢀⣴⣿⡿⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣸⣿⣿⣿⣿⣿⣿⣿⣷
// ⢸⣿⣿⠟⣴⣿⡿⡟⡼⢹⣷⢲⡶⣖⣾⣶⢄⠄⠄⠄⠄⠄⢀⣼⣿⢿⣿⣿⣿⣿⣿⣿⣿
// ⢸⣿⢫⣾⣿⡟⣾⡸⢠⡿⢳⡿⠍⣼⣿⢏⣿⣷⢄⡀⠄⢠⣾⢻⣿⣸⣿⣿⣿⣿⣿⣿⣿
// ⡿⣡⣿⣿⡟⡼⡁⠁⣰⠂⡾⠉⢨⣿⠃⣿⡿⠍⣾⣟⢤⣿⢇⣿⢇⣿⣿⢿⣿⣿⣿⣿⣿
// ⣱⣿⣿⡟⡐⣰⣧⡷⣿⣴⣧⣤⣼⣯⢸⡿⠁⣰⠟⢀⣼⠏⣲⠏⢸⣿⡟⣿⣿⣿⣿⣿⣿
// ⣿⣿⡟⠁⠄⠟⣁⠄⢡⣿⣿⣿⣿⣿⣿⣦⣼⢟⢀⡼⠃⡹⠃⡀⢸⡿⢸⣿⣿⣿⣿⣿⡟
// ⣿⣿⠃⠄⢀⣾⠋⠓⢰⣿⣿⣿⣿⣿⣿⠿⣿⣿⣾⣅⢔⣕⡇⡇⡼⢁⣿⣿⣿⣿⣿⣿⢣
// ⣿⡟⠄⠄⣾⣇⠷⣢⣿⣿⣿⣿⣿⣿⣿⣭⣀⡈⠙⢿⣿⣿⡇⡧⢁⣾⣿⣿⣿⣿⣿⢏⣾
// ⣿⡇⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢻⠇⠄⠄⢿⣿⡇⢡⣾⣿⣿⣿⣿⣿⣏⣼⣿
// ⣿⣷⢰⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⢰⣧⣀⡄⢀⠘⡿⣰⣿⣿⣿⣿⣿⣿⠟⣼⣿⣿
// ⢹⣿⢸⣿⣿⠟⠻⢿⣿⣿⣿⣿⣿⣿⣿⣶⣭⣉⣤⣿⢈⣼⣿⣿⣿⣿⣿⣿⠏⣾⣹⣿⣿
// ⢸⠇⡜⣿⡟⠄⠄⠄⠈⠙⣿⣿⣿⣿⣿⣿⣿⣿⠟⣱⣻⣿⣿⣿⣿⣿⠟⠁⢳⠃⣿⣿⣿
// ⠄⣰⡗⠹⣿⣄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⠟⣅⣥⣿⣿⣿⣿⠿⠋⠄⠄⣾⡌⢠⣿⡿⠃
// ⠜⠋⢠⣷⢻⣿⣿⣶⣾⣿⣿⣿⣿⠿⣛⣥⣾⣿⠿⠟⠛⠉⠄⠄

#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;


vector<int> dp(1e4+5, 1);

const int sigma = 26;
struct Aho{
    int n;
    array<int, sigma> init;
    vector<array<int, sigma> > trie;
    vector<int> out, parent, ids, bfs, f;
    vector<string> v;

    Aho(vector<string> &v) : n((int)v.size()), v(v), out(1, -1), parent(n, -1), ids(n) {
        for(int i=0; i<sigma; i++) init[i] = -1;
        trie.push_back(init);

        for(int i=0; i<n; i++){
            int cur = 0;
            for(char ch:v[i]){
                int c = ch - 'a';
                if(trie[cur][c]==-1){
                    trie[cur][c] = (int)trie.size();
                    trie.push_back(init); out.push_back(-1);
                }
                cur = trie[cur][c];
            }
            if(out[cur]==-1) out[cur] = i;
            ids[i] = out[cur];
        }

        f.resize(trie.size());
        bfs.reserve(trie.size());

        for(int c=0; c<sigma; c++){
            if(trie[0][c]==-1) trie[0][c] = 0;
            else bfs.push_back(trie[0][c]);
        }
        for(int z=0; z<(int)bfs.size(); z++){
            int cur = bfs[z];
            for(int c=0; c<sigma; c++){
                if(trie[cur][c]==-1)
                    trie[cur][c] = trie[f[cur]][c];
                else{
                    int nxt = trie[cur][c];
                    int fail = trie[f[cur]][c];
                    if(out[nxt]==-1) out[nxt] = out[fail];
                    else parent[out[nxt]] = out[fail];
                    f[nxt] = fail; bfs.push_back(nxt);
                }
            }
        }
    }

    void run_pos(string &ss, int ind){
        int state = 0, pos = 0;
        for(char ch:ss){
            int c = ch - 'a';
            state = trie[state][c];
            int i = out[state];
            while(i!=-1){
                if(i != ind) dp[ind] = max(dp[ind], dp[i]+1);
                // ocorrência da string i na posição pos
                i = parent[i];
            }
            pos++;
        }
    }

    void run_count(string &ss){
        int state = 0;
        vector<int> freq(n), freqNode(trie.size());
        for(char ch:ss){
            int c = ch - 'a';
            state = trie[state][c];
            freqNode[state]++;
        }
        for(int i=(int)bfs.size()-1; i>=0; i--){
            int cur = bfs[i];
            int pcur = f[cur];
            freqNode[pcur]+=freqNode[cur];
            if(out[cur]!=-1){
                freq[out[cur]] = freqNode[cur];
            }
        }
        // freq possui a frequência de cada string na string ss
    }
};

signed solve(int n){
    
    vector<string> arr(n);
    for(string &i: arr) cin >> i;

    sort(arr.begin(), arr.end(), [&](string &a, string& b) -> bool {return a.size() == b.size() ? a < b : a.size() < b.size();});

    Aho aho(arr);
    
    for(int i = 0; i < n; i++){
        aho.run_pos(arr[i], i);
    }

    int ans = 1;
    for(int i = 0; i <= n; i++) { ans = max(ans, dp[i]); dp[i] = 1;}
    cout << ans << '\n';


    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    while(true){
        int n; cin >> n;
        if(n == 0) return 0;
        solve(n);
    }

    return 0;
}