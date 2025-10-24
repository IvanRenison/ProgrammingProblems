#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


vii solve(vii& points) {
  auto [min_x, min_y] = points[0];
  auto [max_x, max_y] = points[0];

  for (auto [x, y] : points) {
    if (x < min_x) {
      min_x = x;
    }
    if (x > max_x) {
      max_x = x;
    }
    if (y < min_y) {
      min_y = y;
    }
    if (y > max_y) {
      max_y = y;
    }
  }

  vii ans = {
    {min_x, min_y},
    {max_x, min_y},
    {max_x, max_y},
    {min_x, max_y}
  };

  return ans;
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll n;
  cin >> n;
  vii points(n);
  for (auto& [x, y] : points) {
    cin >> x >> y;
  }

  auto ans = solve(points);
  cout << ans.size() << '\n';
  for (auto [x, y] : ans) {
    cout << x << ' ' << y << '\n';
  }

}
