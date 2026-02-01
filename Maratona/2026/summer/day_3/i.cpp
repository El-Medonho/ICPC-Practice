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

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    // int n; cin >> n;
    map<string, bool> mp;
    vector<string> fives(0), others(0); others.reserve(70000);
    vector<vector<string>> doubles(10);
    fives.reserve(30240);

    auto search = [&](auto &&self, int p, string s) -> void {
        if(p == 5){
            vector<int> cnt(10, 0);
            for(char c: s){
                cnt[c-'0']++;
            }
            sort(cnt.rbegin(), cnt.rend());
            
            if(cnt[0] == cnt[1] && cnt[1] == cnt[2] && cnt[2] == cnt[3] && cnt[3] == cnt[4] && cnt[4] == 1) {
                fill(cnt.begin(), cnt.end(), 0);

                int ch = -1;
                for(char c: s){
                    cnt[c-'0']++;
                    if(cnt[c-'0']) ch = c-'0';
                }

                string a = "", b = "";
                for(int i = 0; i < 10; i++){
                    if(cnt[i]) a += '0'+i;
                    else b += '0'+i;
                }

                if(mp[a]) return;

                mp[a] = true; mp[b] = true;

                do {
                    fives.push_back(a); fives.push_back(b);
                } while(next_permutation(a.begin(), a.end()) && next_permutation(b.begin(), b.end()));

                return;
            }
            others.push_back(s);

            if(cnt[0] == 2 && cnt[1] == 1 && cnt[2] == 1 && cnt[3] == 1) {
                fill(cnt.begin(), cnt.end(), 0);

                int ch = -1;
                for(char c: s){
                    if(cnt[c-'0']) ch = c-'0';
                    cnt[c-'0']++;
                }

                string pattern = "XXXXX";
                for(int i = 0; i < 5; i++){
                    if(s[i] == '0'+ch) pattern[i] = 'O';
                }
                int ind = -1;
                if(pattern == "OOXXX") ind = 0;
                if(pattern == "OXOXX") ind = 1;
                if(pattern == "OXXOX") ind = 2;
                if(pattern == "OXXXO") ind = 3;
                if(pattern == "XOOXX") ind = 4;
                if(pattern == "XOXXO") ind = 5;
                if(pattern == "XOXOX") ind = 6;
                if(pattern == "XXOOX") ind = 7;
                if(pattern == "XXOXO") ind = 8;
                if(pattern == "XXXOO") ind = 9;
                assert(ind != -1);
                doubles[ind].push_back(s);
            }

            //
            return;
        }

        for(int i = 0; i < 10; i++) {
            string ss = s; ss += '0'+i;
            self(self, p+1, ss);
        }
    };

    search(search, 0, "");

    int n; cin >> n;

    
    if(n <= 30000){
        // cout << others.size() << endl;
        for(int i = 0; i < n; i++){
            cout << fives[i] << endl;
        }
        return 0;
    }
    if(n >= 70000){
        for(string s: others) cout << s << endl;
        n -= others.size();
        for(int i = 0; i < n; i++){
            cout << fives[i] << endl;
        }
        return 0;
    }
    int x = 0;
    while(n > 30000){
        n -= doubles[x].size();

        for(string s: doubles[x]) cout << s << endl;
        x++;
    }
    for(int i = 0; i < n; i++){
        cout << fives[i] << endl;
    }

    return 0;
}