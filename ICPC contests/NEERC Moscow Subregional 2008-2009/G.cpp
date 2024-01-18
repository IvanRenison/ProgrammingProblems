// https://codeforces.com/gym/100861

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solve(const vii& points) {
  ull N = points.size();

  if (N < 4) {
    return 0;
  }

  set<ii> sums2;

  fore(i, 0, N) {
    auto [xi, yi] = points[i];
    fore(j, i + 1, N) {
      auto [xj, yj] = points[j];

      ll x = xi + xj, y = yi + yj;

      if (sums2.count({x, y})) {
        return 1;
      } else {
        sums2.insert({x, y});
      }
    }
  }

  return 2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vii points(N);
  for (auto& [x, y] : points) {
    cin >> x >> y;
  }

  auto ans = solve(points);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}


// La respuesta es O(1)

/*
Si hay paralelogramo la respuesta es 1
Si no, si hay al menos 4 se forma un paralelogramo en una generación


*/

