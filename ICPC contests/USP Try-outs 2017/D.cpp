// https://codeforces.com/gym/101492/problem/D
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, carranza = b; i < carranza; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;

const ld eps = 1e-11;

tuple<ld, ld, ld, ld> solve(vector<pair<ld,ld>>& mbs) {
  ll N = mbs.size();

  if (N == 1) {
    return {0, 0, 0, 0};
  }

  sort(ALL(mbs));

  bool starting = true;
  ld xl = 0, yl = 0, xr = 0, yr = 0;

  vector<pair<ld,ld>> new_mbs;
  fore(i, 0, N) {
    if (mbs[i].first != mbs[(i+1) % N].first || mbs[i].first != mbs[(i + N - 1) % N].first) {
      new_mbs.push_back(mbs[i]);
    }
  }

  fore(i, 0, new_mbs.size()) {
    auto [mi, bi] = new_mbs[i];
    fore(j, 1, min(3ll, (ll)new_mbs.size())) {
      auto [mj, bj] = new_mbs[(i + j) % new_mbs.size()];

      if (abs(mi - mj) < eps) {
        continue;
      }

      ld x = (ld)(bi - bj) / (ld)(mi - mj);
      ld y = (ld)mi * x - (ld)bi;

      if (starting) {
        xl = xr = x;
        yl = yr = y;
        starting = false;
      } else {
        xl = min(x, xl);
        xr = max(x, xr);
        yl = min(y, yl);
        yr = max(y, yr);
      }
    }
  }

  return {xl, yl, xr, yr};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vector<pair<ld,ld>> mbs(N);
  for (auto& [m, b] : mbs) {
    cin >> m >> b;
  }

  auto [xl, yl, xr, yr] = solve(mbs);
  cout << setprecision(5);
  cout << xl << ' ' << yl << ' ' << xr << ' ' << yr << '\n';

}
