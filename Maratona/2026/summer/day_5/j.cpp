#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

int get(int x){
  int ans = 0, cans = 0;
  while(x){
    int cc = x%10; x/=10;
    if(cc == 1) cans = 1;
    if(cc == 2) cans = 2;
    if(cc == 3) cans = 3;
    if(cc == 4) cans = 1;
    if(cc == 5) cans = 1;
    if(cc == 6) cans = 1;
    if(cc == 7) cans = 2;
    if(cc == 8) cans = 3;
    if(cc == 9) cans = 1;
    ans = max(ans, cans);
  }

  return ans;
}

string build(int x){
    string tot = "";
    int h = x/1000;
    if(h == 1) tot += "M";
    if(h == 2) tot += "MM";
    if(h == 3) tot += "MMM";

    h = x/100; h %= 10;
    if(h == 1) tot += "C";
    if(h == 2) tot += "CC";
    if(h == 3) tot += "CCC";
    if(h == 4) tot += "CD";
    if(h == 5) tot += "D";
    if(h == 6) tot += "DC";
    if(h == 7) tot += "DCC";
    if(h == 8) tot += "DCCC";
    if(h == 9) tot += "CM";

    h = x/10; h %= 10;

    if(h == 1) tot += "X";
    if(h == 2) tot += "XX";
    if(h == 3) tot += "XXX";
    if(h == 4) tot += "XL";
    if(h == 5) tot += "L";
    if(h == 6) tot += "LX";
    if(h == 7) tot += "LXX";
    if(h == 8) tot += "LXXX";
    if(h == 9) tot += "XC";

    h = x%10;

    if(h == 1) tot += "I";
    if(h == 2) tot += "II";
    if(h == 3) tot += "III";
    if(h == 4) tot += "IV";
    if(h == 5) tot += "V";
    if(h == 6) tot += "VI";
    if(h == 7) tot += "VII";
    if(h == 8) tot += "VIII";
    if(h == 9) tot += "IX";

    return tot;
}

string chars = "IVXLCDM";

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    // [i][char][qtt]
    vector<vector<vector<int>>> pref(4000, vector<vector<int>>(chars.size(), vector<int>(4, 0)));
    vector<vector<vector<int>>> suf = pref, mid = pref, special = pref;

    for(int i = 1; i < 4000; i++){
        for(int j = 0; j < chars.size(); j++){
            for(int k = 0; k < 4; k++) {
                pref[i][j][k] = pref[i-1][j][k];
                suf[i][j][k] = suf[i-1][j][k];
                mid[i][j][k] = mid[i-1][j][k];
                special[i][j][k] = special[i-1][j][k];
            }
        }
        string s = build(i);

        char c = s[0];
        int cnt = 0;
        for(char cc: s){
            if(cc != c) break;
            cnt++;
        }

        if(cnt == s.size()){
            for(int j = 0; j < chars.size(); j++){
                if(chars[j] == c) {
                    mid[i][j][s.size()]++;
                    break;
                }
            }
            continue;
        }
        
        if(s[0] == s.back()) {
            for(int j = 0; j < chars.size(); j++){
                if(chars[j] == c) {
                    // cout << i << ' ' << cnt << endl;
                    special[i][j][cnt]++;
                    break;
                }
            }
            continue;
        }

        for(int j = 0; j < chars.size(); j++){
            if(chars[j] == c) {
                pref[i][j][cnt]++;
                break;
            }
        }

        reverse(s.begin(), s.end());

        c = s[0];
        cnt = 0;
        for(char cc: s){
            if(cc != c) break;
            cnt++;
        }

        for(int j = 0; j < chars.size(); j++){
            if(chars[j] == c) {
                suf[i][j][cnt]++;
                break;
            }
        }
    }

    int t; cin >> t;
    while(t--){
        int l,r; cin >> l >> r; l--;

        int ans = 0;

        for(int i = l+1; i <= r && i <= l+15; i++) ans = max(ans, get(i));

        for(int j = 0; j < chars.size(); j++){
            int cans = 0;
            int bp = 0;
            for(int k = 3; k > -1; k--){
                int qtt = pref[r][j][k] - pref[l][j][k];
                if(qtt == 0) continue;
                // cout << k << endl;
                bp = k;
                break;
            }
            int bs = 0;
            for(int k = 3; k > -1; k--){
                int qtt = suf[r][j][k] - suf[l][j][k];
                if(qtt == 0) continue;
                // cout << k << endl;
                bs = k;
                break;
            }
            int midb = 0;
            for(int k = 3; k > -1; k--){
                int qtt = mid[r][j][k] - mid[l][j][k];
                // cout << k*qtt << endl;
                midb += qtt * k;
            }

            int cnt = 0;
            for(int k = 3; k > -1; k--){
                cnt += special[r][j][k] - special[l][j][k];
            }
            if(cnt > 1) bs = max(bs, 1);
            // cout << cnt << endl;

            cans = max(cans, midb + bp + bs);
            for(int k = 3; k > -1; k--){
                int qtt = special[r][j][k] - special[l][j][k];
                if(qtt){
                    cans = max(cans, midb + max(bs, 1) + bp);
                    bp = max(bp, k);
                    cans = max(cans, midb + bp + bs);
                }
            }
            
            ans = max(ans, cans);
        }

        cout << ans << '\n';
    }


    return 0;
}