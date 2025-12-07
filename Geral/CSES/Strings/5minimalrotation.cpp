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
 
mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
 
struct suffix_array_t { ///start-hash
	int N, H; vector<int> sa, invsa;
	bool cmp(int a, int b) { return invsa[a+H] < invsa[b+H]; }
	void ternary_sort(int a, int b) {
		if (a == b) return;
		int md = sa[a+rng() % (b-a)], lo = a, hi = b;
		for (int i = a; i < b; ++i) if (cmp(sa[i], md))
			swap(sa[i], sa[lo++]);
		for (int i = b-1; i >= lo; --i) if (cmp(md, sa[i]))
			swap(sa[i], sa[--hi]);
		ternary_sort(a, lo);
		for (int i = lo; i < hi; ++i) invsa[sa[i]] = hi-1;
		if (hi-lo == 1) sa[lo] = -1;
		ternary_sort(hi, b);
	}
	suffix_array_t() {} ///end-hash
	template<typename I> ///start-hash
	suffix_array_t(I begin, I end): N(int(end-begin)+1), sa(N) {
		vector<int> v(begin, end); 
        v.push_back('$');
		invsa = v; iota(sa.begin(), sa.end(), 0);
		H = 0; ternary_sort(0, N);
		for(H = 1; H <= N; H *= 2) for(int j=0, i=j; i!=N; i=j)
				if (sa[i] < 0) {
					while (j < N && sa[j] < 0) j += -sa[j];
					sa[i] = -(j - i);
				} else {j = invsa[sa[i]] + 1; ternary_sort(i, j);}
		for (int i = 0; i < N; ++i) sa[invsa[i]] = i;
	} 
};
 
 
 
signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
 
    string s; cin >> s;
    int n = s.size();
    s += s;
 
    suffix_array_t sa(s.begin(), s.end());
 
    // vector<int> suf = sa.sa;

    int i = 0;
    for(; i < sa.sa.size(); i++){
        if(sa.sa[i] < n){
            break;
        }
    }
 
    int g = sa.sa[i];
 
    string ans = ""; ans.reserve(s.size());
    do{
        ans += s[g]; g++;
    } while(g != sa.sa[i]+n);
 
    cout << ans << endl;
 
    return 0;
}