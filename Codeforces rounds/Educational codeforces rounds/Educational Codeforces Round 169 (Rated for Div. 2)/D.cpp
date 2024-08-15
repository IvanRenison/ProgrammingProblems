// https://codeforces.com/contest/2004/problem/D

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

ull color_to_num(char c) {
  if (c == 'B') {
    return 0;
  } else if (c == 'G') {
    return 1;
  } else if (c == 'R') {
    return 2;
  } else {
    return 3;
  }
}

bool have_common(uu x, uu y) {
  return x.first == y.first || x.first == y.second || x.second == y.first || x.second == y.second;
}

ull diff(ull x, ull y) {
  return max(x, y) - min(x, y);
}

vector<optional<ull>> solve(vuu& colors, vuu& queries) {
  ull n = SZ(colors), q = SZ(queries);

  vector<vector<vu>> pos(4, vector<vu>(4));
  fore(i, 0, n) {
    auto [c0, c1] = colors[i];
    pos[c0][c1].push_back(i);
    pos[c1][c0].push_back(i);
  }

  vector<optional<ull>> ans(q);

  fore(i, 0, q) {
    auto [x, y] = queries[i];
    if (have_common(colors[x], colors[y])) {
      ans[i] = diff(x, y);
    } else {
      if (y < x) {
        swap(x, y);
      }

      auto [cx0, cx1] = colors[x];
      auto [cy0, cy1] = colors[y];

      vuu cross = {{cx0, cy0}, {cx0, cy1}, {cx1, cy0}, {cx1, cy1}};

      ull best = inf;

      for (auto [c0, c1] : cross) {
        if (pos[c0][c1].empty()) {
          continue;
        }
        auto it = lower_bound(ALL(pos[c0][c1]), x);
        if (it != pos[c0][c1].end()) {
          best = min(best, diff(x, *it) + diff(y, *it));
        }
        if (it != pos[c0][c1].begin()) {
          it--;
          best = min(best, diff(x, *it) + diff(y, *it));
        }
      }

      if (best != inf) {
        ans[i] = best;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, q;
    cin >> n >> q;
    vuu colors(n);
    for (auto& [c0, c1] : colors) {
      string s;
      cin >> s;
      c0 = color_to_num(s[0]);
      c1 = color_to_num(s[1]);
    }
    vuu queries(q);
    for (auto& [x, y] : queries) {
      cin >> x >> y;
      x--;
      y--;
    }


    auto ans = solve(colors, queries);

    for (auto a : ans) {
      if (a.has_value()) {
        cout << *a << '\n';
      } else {
        cout << "-1\n";
      }
    }
  }

}
