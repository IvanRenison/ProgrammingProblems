// https://codeforces.com/gym/101309
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;

ld gss(ld a, ld b, auto f) {
  ld r = (sqrtl(5)-1)/2, eps = 1e-12;
  ld x1 = b - r*(b-a), x2 = a + r*(b-a);
  ld f1 = f(x1), f2 = f(x2);
  while (b-a > eps) {
    if (f1 < f2) {
      b = x2; x2 = x1; f2 = f1;
      x1 = b - r*(b-a); f1 = f(x1);
    } else {
      a = x1; x1 = x2; f1 = f2;
      x2 = a + r*(b-a); f2 = f(x2);
    }
  }
  return a;
}

struct Point {
  ld x, y;
};

struct Point3D {
  ld x, y, z;
};

ld volCono(ld h, ld r) {
  return r * r * h;
}

pair<ld, ld> solve(vector<Point3D>& points) {
  ll n = points.size();

  vector<Point> points2D(n);
  ld max_z = 0;
  fore(i, 0, n) {
    auto [x, y, z] = points[i];
    points2D[i] = {sqrtl(x*x + y*y), z};
    max_z = max(z, max_z);
  }

  auto f = [&](ld h) -> ld {
    ld r = 0;
    for (auto [x, y] : points2D) {
      ld a = (y - h) / x;
      r = max(r, -h / a);
    }
    ld ans = volCono(h, r);
    return ans;
  };

  ld h = gss(max_z + 1e-12, 1e50, f);

  ld r = 0;
  for (auto [x, y] : points2D) {
    ld a = (y - h) / x;
    r = max(r, -h / a);
  }

  return {h, r};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("dome.in", "r", stdin);
  freopen("dome.out", "w", stdout);
#endif

  ll n;
  cin >> n;
  vector<Point3D> points(n);
  for (auto& [x, y, z] : points) {
    cin >> x >> y >> z;
  }
  auto [h, r] = solve(points);
  cout << setprecision(3)  << fixed;
  cout << h << ' ' << r << '\n';

}