// https://codeforces.com/gym/104901/problem/M
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

typedef ll T;
struct P {
  ll x, y;
  explicit P(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const {return tie(x,y) < tie(p.x, p.y); }
  bool operator==(P p) const {return tie(x,y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

vector<P> convexHull(vector<P> pts) {
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
  Angle(P p) : x(p.x), y(p.y), t(0) {}
  ll half() const {
    assert(x || y);
    return y < 0 || (y == 0 && x < 0);
  }
};
bool operator<(Angle a, Angle b) {
  return make_tuple(a.t, a.half(), a.y * (ll)b.x) < make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

ll solve(vector<P>& points) {
  ll n = points.size();

  vector<P> hull = convexHull(points);

  set<P> hull_set(ALL(hull));


  ll ans = 1;

  fore(i, 0, n) {
    P p = points[i];
    if (!hull_set.count(p)) {
      vector<P> p_center;
      fore(j, 0, n) if (i != j) {
        p_center.push_back(points[j] - p);
      }
      sort(ALL(p_center), [](P a, P b) {
        return Angle(a) < Angle(b);
      });

      bool last_in_hull = hull_set.count(p_center.back() + p);

      for (P q : p_center) {
        if (hull_set.count(q + p)) {
          if (last_in_hull) {
            ans++;
          }
          last_in_hull = true;
        } else {
          last_in_hull = false;
        }
      }
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vector<P> points(n);
  for (auto& [x, y] : points) {
    cin >> x >> y;
  }

  ll ans = solve(points);

  cout << ans << '\n';


}