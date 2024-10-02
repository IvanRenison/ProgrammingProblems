// https://codeforces.com/contest/1662/problem/N

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

pair<ull, vu> compress(const vu& xs) {
  ull n = xs.size();

  map<ull, vu> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vu compressed_xs(n);

  ull i = 0;
  for (auto [x, ks] : xs_map) {
    for (ull k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return {i - 1, compressed_xs};
}

ull solve(const vector<vu>& ass) {
  ull n = ass.size();

  vector<vu> c_rows(n), c_cols(n);

  fore(i, 0, n) {
    c_rows[i] = compress(ass[i]).second;
  }

  fore(j, 0, n) {
    vu col(n);
    fore(i, 0, n) {
      col[i] = ass[i][j];
    }
    c_cols[j] = compress(col).second;
  }

  ull ans = 0;

  fore(i, 0, n) {
    fore(j, 0, n) {
      ull r_less = c_rows[i][j],
          c_more = n - c_cols[j][i] - 1;

      ans += r_less * c_more;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<vu> ass(n, vu(n));
  for(vu& as : ass) {
    for(ull& a : as) {
      cin >> a;
      a--;
    }
  }

  auto ans = solve(ass);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
