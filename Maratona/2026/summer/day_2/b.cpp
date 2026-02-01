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

// #define endl '\n'

typedef long long ll;

string chars = "IVXLCDM";
const int mod = 998244353;

int expo(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b%mod;
        b=b*b%mod;
        e>>=1;
    }
    return ans;
}

int transform(string s){
    int n = s.size();
    string u = "";
    int num = 0;
    while(n && (n >= 2 && s[n-2] == 'I') || (n >= 2 && s[n-2] == 'V') || s[n-1] == 'I' || s[n-1] == 'V') {
        u += s[n-1]; n--;
        s.pop_back();
    }

    reverse(u.begin(), u.end());

    if(u == "I") num += 1;
    else if(u == "II") num += 2;
    else if(u == "III") num += 3;
    else if(u == "IV") num += 4;
    else if(u == "V") num += 5;
    else if(u == "VI") num += 6;
    else if(u == "VII") num += 7;
    else if(u == "VIII") num += 8;
    else if(u == "IX") num += 9;
    else if(u == "") num += 0;
    else return 0;

    u.clear();

    
    while(n && (n >= 2 && s[n-2] == 'X') || (n >= 2 && s[n-2] == 'L') || s[n-1] == 'X' || s[n-1] == 'L') {
        u += s[n-1]; n--;
        s.pop_back();
    }
    
    reverse(u.begin(), u.end());

    if(u == "X") num += 10;
    else if(u == "XX") num += 20;
    else if(u == "XXX") num += 30;
    else if(u == "XL") num += 40;
    else if(u == "L") num += 50;
    else if(u == "LX") num += 60;
    else if(u == "LXX") num += 70;
    else if(u == "LXXX") num += 80;
    else if(u == "XC") num += 90;
    else if(u == "") num += 0;
    else return 0;

    u.clear();

    while(n && (n >= 2 && s[n-2] == 'C') || (n >= 2 && s[n-2] == 'D') || s[n-1] == 'C' || s[n-1] == 'D') {
        u += s[n-1]; n--;
        s.pop_back();
    }

    reverse(u.begin(), u.end());

    if(u == "C") num += 100;
    else if(u == "CC") num += 200;
    else if(u == "CCC") num += 300;
    else if(u == "CD") num += 400;
    else if(u == "D") num += 500;
    else if(u == "DC") num += 600;
    else if(u == "DCC") num += 700;
    else if(u == "DCCC") num += 800;
    else if(u == "CM") num += 900;
    else if(u == "") num += 0;
    else return 0;

    u.clear();

    while(n > 0 && s[n-1] == 'M') {
        u += s[n-1]; n--;
        s.pop_back();
    }

    reverse(u.begin(), u.end());

    if(u == "M") num += 1000;
    else if(u == "MM") num += 2000;
    else if(u == "MMM") num += 3000;
    else if(u == "") num += 0;
    else return 0;

    if(n > 0) return 0;

    return num;
}

vector<int> prof(4000, -1);
vector<vector<int>> graph(4000, vector<int>((int)chars.size(), 0));

int dfs(string s){
    int u = 0;
    if(s != "") {
        u = transform(s);
        // if(s == "XC") cout << u << endl;
        if(u == 0) return 0;
    }

    prof[u] = s.size();

    for(int i = 0; i < chars.size(); i++){
        char c = chars[i];
        string ss = s; ss += c;
        int nx = dfs(ss);

        if(nx){
            graph[u][i] = nx;
            continue;
        }
        string temp = ""; temp += c; 
        nx = transform(temp);
        for(int j = s.size()-1; j > 0; j--){
            ss = s.substr(j, s.size()-j); ss += c;
            int h = (transform(ss));
            if(h) nx = h;
            else break;
        }
        graph[u][i] = nx;
    }

    return u;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    dfs("");
    
    ll n; cin >> n;

    // dp[i][num][mx]
    vector<vector<ll>> dp(4000, vector<ll>(16));
    dp[0][0] = 1;

    for(int i = 0; i < n; i++){
        vector<vector<ll>> ndp(4000, vector<ll>(16));
        for(int j = 0; j < 4000; j++){
            for(int b = 0; b < 16; b++){
                for(int k = 0; k < chars.size(); k++){
                    assert(graph[j][k] > 0);
                    int nx = graph[j][k];
                    ndp[nx][max(b, prof[nx])] += dp[j][b];
                    if(ndp[nx][max(b, prof[nx])] >= mod) ndp[nx][max(b, prof[nx])] -= mod;
                }
            }
        }

        dp = ndp;
    }

    ll ans = 0, bb = 0;

    for(int j = 0; j < 4000; j++){
        for(int b = 0; b < 16; b++){
            bb += dp[j][b];
            if(bb >= mod) bb -= mod;
            
            ans += dp[j][b] * b % mod;
            if(ans >= mod) ans -= mod;
        }
    }

    cout << ans * expo(bb, mod-2) % mod << endl;

    return 0;
}