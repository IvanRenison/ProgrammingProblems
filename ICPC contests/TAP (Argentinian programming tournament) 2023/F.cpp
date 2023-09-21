// https://codeforces.com/gym/104603/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

constexpr ll inf = 1ll << 60;

pair<char, ull> solve(ll TX, ll TY, vii A_XYs, vii R_XYs) {
  ll min_dist2_A = inf, min_dist2_R = inf;

  for(auto [X, Y] : A_XYs) {
    ll dist2 = (TX - X) * (TX - X) + (TY - Y) * (TY - Y);
    min_dist2_A = min(min_dist2_A, dist2);
  }
  for(auto [X, Y] : R_XYs) {
    ll dist2 = (TX - X) * (TX - X) + (TY - Y) * (TY - Y);
    min_dist2_R = min(min_dist2_R, dist2);
  }

  if (min_dist2_A < min_dist2_R) {
    ull ans = 0;
    for(auto [X, Y] : A_XYs) {
      ll dist2 = (TX - X) * (TX - X) + (TY - Y) * (TY - Y);
      if (dist2 < min_dist2_R) {
        ans++;
      }
    }
    return {'A', ans};
  } else {
    ull ans = 0;
    for(auto [X, Y] : R_XYs) {
      ll dist2 = (TX - X) * (TX - X) + (TY - Y) * (TY - Y);
      if (dist2 < min_dist2_A) {
        ans++;
      }
    }
    return {'R', ans};
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, W, L, TX, TY;
  cin >> N >> W >> L >> TX >> TY;

  vii A_XYs(N), R_XYs(N);
  for(auto& [X, Y] : A_XYs) {
    cin >> X >> Y;
  }
  for(auto& [X, Y] : R_XYs) {
    cin >> X >> Y;
  }


  auto [c, ans] = solve(TX, TY, A_XYs, R_XYs);
  cout << c << ' ' << ans << '\n';

  return EXIT_SUCCESS;
}
