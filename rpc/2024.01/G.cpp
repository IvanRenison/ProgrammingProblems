// https://redprogramacioncompetitiva.com/contests/2024/01/
#ifdef ONLINE_JUDGE
#pragma GCC optimize("O2,unroll-loops,modulo-sched,modulo-sched-allow-regmoves,gcse-sm,gcse-las,ipa-pta,tree-loop-im,tree-loop-ivcanon,ivopts,tree-vectorize")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,tune=native")
#endif
#include "bits/stdc++.h"
// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// #include "ext/rope"
// using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fori(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define rof(i, a, b) for (ll i = a - 1; i >= b; i--)
#define fore(xs, x) for (auto& x : xs)
#define forp(xs, a, b) for (auto& [a, b] : xs)
#define prnt(x) cout << (x) << "\n"
#define all(x) begin(x), end(x)
#define SZ(x) (ll)(x.size())
#define ii pair<ll, ll>
#define vii vector<ii>
#define vvii vector<vii>
#define vi vector<ll>
#define vvi vector<vi>
#define vd vector<ld>
#define vvd vector<vd>
#define vc vector<char>
#define vvc vector<vector<char>>
constexpr array<ii, 4> dir = {mp(1, 0), mp(0, 1), mp(-1, 0), mp(0, -1)};
constexpr ll INF = 1e18;
constexpr ld EPS = 1e-7;
constexpr ll MOD = 1e9 + 7;

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
    // angle to x−axis in interva l [−pi , pi ]
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }  // makes d is t ()=1
    P perp() const { return P(-y, x); }        // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated ’a ’ radians ccw around the origin
    P rotate(ld a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

ld segDist(Point<ld>& s, Point<ld>& e, Point<ld>& p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max((ld)0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

template <class P>
bool onSegment(P s, P e, P p) {
    return segDist(s, e, p) <= EPS;
}

template <class P>
vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

ll n;
vector<Point<ld>> ps;
Point<ld> c, b, v;

bool can(ld t) {
    Point<ld> p = b + v * t;
    fori(i, 0, n) {
        auto inter = segInter(ps[i], ps[i + 1], p, c);
        if (SZ(inter) > 1) return false;
        if (SZ(inter) && (inter[0] - c).dist2() > EPS) return false;
    }
    return true;
}

ld func(ld t) {
    Point<ld> p = b + v * t;
    if (can(t)) return (p - c).dist();
    return (p - c).dist() + 1e10;
}

ld gss(ld a, ld b, ld (*f)(ld)) {
    ld r = (sqrt(5) - 1) / 2;
    ld x1 = b - r * (b - a), x2 = a + r * (b - a);
    ld f1 = f(x1), f2 = f(x2);
    while (b - a > EPS)
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - r * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + r * (b - a);
            f2 = f(x2);
        }
    return a;
}

int main() {
    FIN;
    cin >> n;
    vii a(n + 1);
    forp(a, x, y) cin >> x >> y;
    sort(all(a));
    forp(a, x, y) ps.pb(Point<ld>(x, y));

    ll _c;
    cin >> _c;
    auto it = lower_bound(all(a), mp(_c, 0ll));
    ii ne = *it;
    ii pre = *prev(it);
    ld m = (ld)(ne.snd - pre.snd) / (ne.fst - pre.fst);
    ld cy = pre.snd + m * (_c - pre.fst);
    c = Point<ld>(_c, cy);

    ll sx, sy, r, dx, dy, _v;
    cin >> sx >> sy >> r >> dx >> dy >> _v;
    Point<ld> s = Point<ld>(sx, sy), d = Point<ld>(dx, dy);
    b = s + d.unit() * r;
    v = d.unit() * _v;

    ld seen = gss(0, 1e9, func);

    ld l = 0, ri = seen;
    while (ri - l > EPS) {
        ld mid = l + (ri - l) / 2;
        if (can(mid)) {
            ri = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(10) << (ri + l) / 2 << "\n";

    return 0;
}
