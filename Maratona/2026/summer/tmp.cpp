#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio ios::sync_with_stdio(0), cin.tie(nullptr)

using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using tiii = tuple<int,int,int>;
using tlll = tuple<ll,ll,ll>;

using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<int K> 
struct AhoCorasick {
    struct Node{
        array<int,K> nxt;
        int is_terminal;
        int link;
        int p;
        array<int,K> go;
        Node() {
            nxt.fill(-1);
        }
    };

    vector<Node> t;

    AhoCorasick(const vector<string>& dict) : t(1) {
        queue<tiii> q; // nó, i no dict, j na string
        for(int i = 0; i < dict.size(); i++) {
            q.emplace(0,i,0);
        }

        while(!q.empty()) {
            auto [u,i,j] = q.front();
            q.pop();

            if(j == dict.size()) {
                t[u].is_terminal = true;
                continue;
            }

            int c = dict[i][j] - 'a';

            if(t[u].nxt[c] == -1) {
                t[u].nxt[c] = t.size();
                t.push_back(Node());
                t.back().p = u;
            }
            q.emplace(t[u].nxt[c],i,j+1);

            link[u] = go[t[u].p][c];
        }
    }
};

int solve() {
    int n;
    cin >> n;

    if(n == 0) return false;

    vector<string> dict(n);
    for(string& s : dict) cin >> s;

    AhoCorasick<26> aho(dict);

    return true;
}

int main() {
    fastio;

    while(solve());
}