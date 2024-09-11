// https://contest.ucup.ac/contest/1784/problem/9253
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> iii;
typedef long double ld;

const ld pi = acosl(-1);

struct P {
    ld x, y;

    P(ld x = 0, ld y = 0) : x(x), y(y) {}
    P operator-(P p) const {
        return P(x-p.x, y-p.y);
    }
    ld dot(P p) const {
        return x * p.x + y*p.y;
    }
    ld cross(P p) const {
        return x*p.y - y*p.x;
    }
    ld dist2() {
        return x*x+y*y;
    }
    ld dist() {
        return sqrtl(dist2());
    }
    ld angle() const {
        return atan2(y, x);
    }
};

ld angle(P a, P b) {
    return acosl(a.dot(b) / a.dist() / b.dist());
}

ld polygonArea2(vector<P>& v) {
    ld a = v.back().cross(v[0]);
    fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
    return a;
}


ld solve(vector<P>& points) {
    ll n = points.size();

    ld area = polygonArea2(points);
    if (area < 0) {
        reverse(ALL(points));
    }

    vector<pair<ld,ld>> ints;

    fore(i, 0, n) {
        P a = points[i], b = points[(i+1) % n], c = points[(i+2) % n], d = points[(i+3) % n];

        ld a_b = angle(a-b, c-b);
        ld a_c = angle(b-c, d-c);
        if (a_b + a_c < pi) {
            ld l = (b - a).angle();
            if (l < 0) {
                l = 2*pi + l;
            }
            ld r = (c - d).angle();
            if (r < 0) {
                r = 2*pi + r;
            }
            ints.push_back({l, r});
            l += pi;
            if (l >= 2 * pi) l -= 2*pi;
            r += pi;
            if (r >= 2 * pi) r -= 2*pi;
            ints.push_back({l, r});
        }
    }

    vector<pair<ld,ld>> nints;
    for (auto [l, r] : ints) {
        //cout << l << ' ' << r << '\n';
        if (l > r) {
            nints.push_back({l, 2*pi});
            nints.push_back({0, r});
        } else {
            nints.push_back({l, r});
        }
    }

    sort(ALL(nints));
    ints.clear();

    for (auto [l, r] : nints) {
        if (ints.empty()) {
            ints.push_back({l, r});
        } else {
            auto& [l0, r0] = ints.back();
            if (r0 < l) {
                ints.push_back({l, r});
            } else {
                r0 = r;
            }
        }
    }

    ld sum = 0;
    for (auto [l, r] : ints) {
        sum += r - l;
    }

    ld ans = sum / (2 * pi);

    return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    ll n;
    cin >> n;
    vector<P> points(n);
    for (auto& [x, y] : points) {
        ll X, Y;
        cin >> X >> Y;
        x = X, y = Y;
    }

    cout << setprecision(15) << fixed;
    cout << solve(points) << '\n';

}
/*
4
0 0
0 3
1 2
1 1
2.356194490192345 8.639379797371931
5.497787143782138 5.497787143782138
1.000000000000000

*/