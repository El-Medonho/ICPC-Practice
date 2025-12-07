#include "bits/stdc++.h"

using namespace std;

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

template <class T> struct RMQ{ // 0-indexed
    int lg;
    vector<vector<T> > tab;

    T join(T a, T b){
        return min(a, b);
    }

    RMQ() {}

    RMQ(vector<T> &v){
        int n = (int)v.size();
        lg = __lg(n)+1;
        tab.resize(lg);
        tab[0]=v;
        for(int j=1; j<lg; j++){
            tab[j].resize(n-(1<<j)+1);
            for(int i=0; i+(1<<j)<=n; i++){
                tab[j][i]=join(tab[j-1][i], tab[j-1][i+(1<<(j-1))]);
            }
        }
    }

    T query(int l, int r){ //[l, r)
        int k = __lg(r-l);
        return join(tab[k][l], tab[k][r-(1<<k)]);
    }

    T query_sum(int l, int r){ //[l, r)
        T ans=0;
        for(int i=lg-1; i>=0; i--){
            if(l+(1<<i)<=r){
                ans+=tab[i][l];
                l+=(1<<i);
            }
        }
        return ans;
    }
};