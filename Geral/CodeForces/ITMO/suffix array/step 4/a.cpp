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

template<typename T, typename Cmp=less<T>>
struct rmq_t : private Cmp {
	int N = 0;
	vector<vector<T>> table; 
	const T& min(const T& a, const T& b) const { return Cmp::operator()(a, b) ? a : b; }
	rmq_t() {}
	rmq_t(const vector<T>& values) : N(int(values.size())), table(__lg(N) + 1) {
		table[0] = values;
		for (int a = 1; a < int(table.size()); ++a) {
			table[a].resize(N - (1 << a) + 1);
			for (int b = 0; b + (1 << a) <= N; ++b) 
				table[a][b] = min(table[a-1][b], table[a-1][b + (1 << (a-1))]); 
		}
	}
	T query(int a, int b) const { 
		int lg = __lg(b - a);
		return min(table[lg][a], table[lg][b - (1 << lg) ]);
	}
};

struct suffix_array_t { ///start-hash
	int N, H; vector<int> sa, invsa, lcp;
	rmq_t<pair<int, int>> rmq;
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
        v.push_back(INT_MIN);
		invsa = v; iota(sa.begin(), sa.end(), 0);
		H = 0; ternary_sort(0, N);
		for(H = 1; H <= N; H *= 2) for(int j=0, i=j; i!=N; i=j)
				if (sa[i] < 0) {
					while (j < N && sa[j] < 0) j += -sa[j];
					sa[i] = -(j - i);
				} else {j = invsa[sa[i]] + 1; ternary_sort(i, j);}
		for (int i = 0; i < N; ++i) sa[invsa[i]] = i;
		lcp.resize(N-1); int K = 0;
		for (int i = 0; i < N-1; ++i) {
			if(invsa[i] > 0) while(v[i+K] == v[sa[invsa[i]-1]+K])++K;
			lcp[invsa[i]-1] = K; K = max(K - 1, 0);
		}
		vector<pair<int, int>> lcp_index(N-1);
		for (int i = 0; i < N-1; ++i) lcp_index[i] = {lcp[i], 1+i};
		rmq = rmq_t<pair<int, int>>(std::move(lcp_index));
	} ///end-hash
	auto rmq_query(int a, int b) const {return rmq.query(a,b);}
	auto get_split(int a, int b) const {return rmq.query(a,b-1);}
	int get_lcp(int a, int b) const { ///start-hash
		if (a == b) return N - a;
		a = invsa[a], b = invsa[b];
		if (a > b) swap(a, b);
		return rmq_query(a, b).first;
	} ///end-hash
};


signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    string s; cin >> s;

    suffix_array_t sa(s.begin(), s.end());
    int n = s.size();

    ll ans = 0;
    for(int i = 1; i <= s.size(); i++){
        ans += n-sa.sa[i] - sa.lcp[i-1];
    }

    cout << ans << endl;



    return 0;
}