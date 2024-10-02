// https://codeforces.com/gym/104114/problem/B
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

ll readNum() {
    string s;
    cin >> s;
    ll ans = 0;
    ll t = 100000;
    fore(i, 0, s.size() - 2) {
        ans += (s[i + 2] - '0') * t;
        t /= 10;
    }
    return ans;
}

ll sgn(ll x) {
    return (x > 0) - (x - 0);
}
struct P {
    ll x, y;
    P(ll x = 0, ll y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator-() const { return P(-x, -y); }
    ll cross(P p) const { return x*p.y - y*p.x; }
    ll cross(P a, P b) const { return (a - *this).cross(b - *this); }
};

vector<P> convexHull(vector<P>& pts) {
    if (SZ(pts) <= 1) return pts;
    sort(ALL(pts));
    vector<P> h(SZ(pts)+1);
    ll s = 0, t = 0;
    for (ll it = 2; it--; s = --t, reverse(ALL(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

struct Angle {
    ll x, y;
    ll t;
    Angle(ll x, ll y, ll t=0) : x(x), y(y), t(t) {}
    ll half() const {
        assert(x || y);
        return y < 0 || (y == 0 && x < 0);
    }
    Angle t180() const { return {-x, -y, t + half()}; }
    Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
    return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
           make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

// Best count of [x, x+180) in with a < x && x + 180 < b
ll countBest(vector<Angle>& angles, Angle a, Angle b) {
    ll n = angles.size();
    sort(ALL(angles));
    fore(i, 0, n) {
        angles.push_back(angles[i].t360());
    }
    ll ans = 0;
    ll l = upper_bound(ALL(angles), a) - angles.begin();
    ll r = l + 1;
    while (l < 2*n && angles[l] < b) {
        while (r < 2*n && angles[r] < angles[l].t180() && angles[r] < b) {
            r++;
        }
        ll this_ans = r - l;
        ans = max(ans, this_ans);
        l++;
    }
    return ans;
}


ll solve(vector<P>& chips, vector<P>& berries) {
    berries = convexHull(berries);

    ll n = chips.size(), m = berries.size();

    ll ans = 0;
    if (m == 1) {
        auto [x0, y0] = berries[0];

        vector<Angle> angles;
        for (auto [x, y] : chips) {
            angles.push_back({x - x0, y - y0});
        }


        ll this_ans = countBest(angles, {1, 0, -1}, {1, 0, 3});
        ans = max(ans, this_ans);
        return ans;
    }

    fore(i, 0, m) {
        ll j = (i + 1) % m, k = (i + 2) % m;
        auto [xj, yj] = berries[j];

        vector<Angle> angles;
        for (auto [x, y] : chips) {
            angles.push_back({x - xj, y - yj});
        }

        Angle a = {berries[i].x - xj, berries[i].y - yj};
        Angle b = {berries[k].x - xj, berries[k].y - yj};
        if (!(a < b)) {
            b = b.t360();
        }

        ll this_ans = countBest(angles, a, b);
        ans = max(ans, this_ans);
    }


    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m;
    cin >> n >> m;
    vector<P> chips(n), berries(m);
    for (auto& [x, y] : chips) {
        x = readNum(), y = readNum();
    }
    for (auto& [x, y] : berries) {
        x = readNum(), y = readNum();
    }
    cout << solve(chips, berries) << '\n';
}
