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
typedef double ld;

struct Point{
    typedef Point P;
    ld x, y;
    explicit Point(ld x_=0, ld y_=0) : x(x_), y(y_) {}
    P operator+(P p) const {return P(x+p.x, y+p.y);}
    P operator-(P p) const {return P(x-p.x, y-p.y);}
    P operator*(ld d) const {return P(x*d, y*d);}
    P operator/(ld d) const {return P(x/d, y/d);}
    ld cross(P p) const { return x*p.y - y*p.x;}
    ld cross(P a, P b) const { return (a-*this).cross(b-*this);}
};

using P = Point;

template<class P>
pair<int,P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1-s1).cross(e2-s2);
    if(d == 0) return {-(s1.cross(e1, s2) == 0), P(0,0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

ld area(vector<P> &v){
    if(v.empty()) return 0;
    ld a = v.back().cross(v[0]);
    for(int i = 0; i < v.size()-1; i++){
        a += v[i].cross(v[i+1]);
    }
    return a;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    int n,k; cin >> n >> k;

    ld l = -2e5, r = 2e5;

    vector<P> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i].x >> arr[i].y;
    }

    ld tot = area(arr);
    if(tot < 0) reverse(arr.begin(), arr.end());
    tot = area(arr);

    int cnt = 300;
    while(cnt--){
        ld md = (l+r)/2;
        vector<P> temp(0);


        for(int i = 0; i < n; i++){
            P nx = arr[(i+1)%n];
            if(arr[i].x >= md) temp.push_back(arr[i]);
            if((arr[i].x >= md && nx.x < md) || arr[i].x < md && nx.x >= md) {

                auto [b, inter] = lineInter(arr[i], nx, P(md, -1e6), P{md, 1e6});
                if(b == 0 || b == -1 || inter.x < min(arr[i].x, nx.x) || inter.x > max(arr[i].x, nx.x)) continue;

                temp.push_back(inter);
            }
        }

        ld A = area(temp);

        ld res = tot-A;
        ld hh = res/A;
        if(A/res > k || res == 0){
            l = md;
        }
        else r = md;
    }

    cout << fixed << setprecision(10) << l << '\n';


    return 0;
}