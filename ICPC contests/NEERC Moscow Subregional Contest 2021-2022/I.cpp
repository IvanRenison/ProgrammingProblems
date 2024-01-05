// https://codeforces.com/gym/104848/problem/I
#include <bits/stdc++.h>
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

#pragma GCC optimize("Ofast")

double dist(ii p0, ii p1) {
  auto [x0, y0] = p0;
  auto [x1, y1] = p1;

  return sqrt((double)((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

const ll total = 4e7;

double solve(const vii& ps) {
  ll n = ps.size();

  if (n*n <= total) {
    double ans = 0.0;
    fore(i, 0, n) {
      fore(j, i + 1, n) {
        ans += dist(ps[i], ps[j]);
      }
    }
    return ans;
  } else {
    double ans = 0.0;

    static random_device rd;
    static mt19937_64 gen(rd());
    uniform_int_distribution<ll> dis(0, n - 1);

    fore(_, 0, total) {
      ll i = dis(gen), j = dis(gen);

      if (i != j) {
        ans += dist(ps[i], ps[j]);
      }
    }

    ans *= ((double)(n * (n - 1))) / ((double)(2*total));

    return ans;
  }
}

int main() {
  FIN;

  ll n;
  cin >> n;
  vii ps(n);
  for (auto& [x, y] : ps) {
    cin >> x >> y;
  }

  cout << setprecision(5) << fixed;
  cout << solve(ps) << '\n';

  return 0;
}
