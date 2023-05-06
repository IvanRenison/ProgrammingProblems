// https://codeforces.com/contest/1829/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<pair<ull, pair<bool, bool>>> parse1(void) {
  ull n;
  cin >> n;

  vector<pair<ull, pair<bool, bool>>> mss(n);
  fore(i, 0, n) {
    ull m;
    char c0, c1;
    cin >> m >> c0 >> c1;
    mss[i] = {m, {c0 == '1', c1 == '1'}};
  }

  return mss;
}

ull solve1(vector<pair<ull, pair<bool, bool>>> mss) {
  ull n = mss.size();

  ull min_both = 10e10;
  ull min0 = 10e10;
  ull min1 = 10e10;

  fore(i, 0, n) {
    ull m = mss[i].first;
    bool c0 = mss[i].second.first;
    bool c1 = mss[i].second.second;

    if (c0 && c1) {
      min_both = min(min_both, m);
    } else if (c0) {
      min0 = min(min0, m);
    } else if (c1) {
      min1 = min(min1, m);
    }
  }

  if (min_both == 10e10 && (min0 == 10e10 || min1 == 10e10)) {
    return -1;
  }

  return min(min_both, min0 + min1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
