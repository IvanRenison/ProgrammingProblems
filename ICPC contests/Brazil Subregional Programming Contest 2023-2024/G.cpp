// https://codeforces.com/gym/104555/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template <class T> int sgn(T x) {
  return (x > 0) - (x < 0);
}

template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const {
    return tie(x,y) < tie(p.x, p.y);
  }
  bool operator==(P p) const {
    return tie(x,y) == tie(p.x, p.y);
  }
  P operator-(P p) {
    return P(x-p.x, y-p.y);
  }
  T dot(P p) const {
    return x*p.x + y*p.y;
  }
  T cross(P p) const {
    return x*p.y - y*p.x;
  }
  T cross(P a, P b) const {
    return (a-*this).cross(b-*this);
  }
};

typedef Point<ll> P;

// sideOf.h
int sideOf(P s, P e, P p) {
  return sgn(s.cross(e, p));
}

// OnSegment.h
bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// ConvexHull.h
vector<P> convexHull(vector<P> pts) {
  if (SZ(pts) <= 1) return pts;
  sort(ALL(pts));
  vector<P> h(SZ(pts)+1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(ALL(pts))) {
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) {
        t--;
      }
      h[t++] = p;
    }
  }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

// PointInsideHull
bool inHull(const vector<P>& l, P p, bool strict = true) {
  int a = 1, b = SZ(l) - 1, r = !strict;
  if (SZ(l) < 3) {
    return r && onSegment(l[0], l.back(), p);
  }
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r) {
    return false;
  }
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}


vector<ull> solve(vector<P>& ps) {
  ull N = ps.size();
  vector<P> l = convexHull(ps);

  vector<ull> ans;

  fore(i, 0, N) {
    if (!inHull(l, ps[i], true)) {
      ans.push_back(i);
    }
  }

  sort(ALL(ans));

  return ans;
}

int main(){FIN;
  ull N;
  cin >> N;
  vector<P> ps(N);
  fore(i, 0, N) {
    ull X, Y;
    cin >> X >> Y;
    ps[i] = P(X, Y);
  }

  auto ans = solve(ps);
  for(ull a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';

  return 0;
}