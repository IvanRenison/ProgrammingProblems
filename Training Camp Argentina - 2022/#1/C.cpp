// https://codeforces.com/group/4zVk9dZl6Q/contest/390414/problem/C

#include <bits/stdc++.h>
#define fore(i, a, b) for (ull i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

vector<tuple<ull, ull, ll, ull>> lasts[3];

void init(vector<ull>& as, vector<ull>& bs, vector<ull>& cs) {
  ull n = as.size();

  lasts[0] = vector<tuple<ull, ull, ll, ull>>(n);
  lasts[1] = vector<tuple<ull, ull, ll, ull>>(n);
  lasts[2] = vector<tuple<ull, ull, ll, ull>>(n);

  fore(i, 0, n) {
    ull a = as[i], b = bs[i], c = cs[i];
    lasts[0][i] = {b, c, -ll(a), i};
    lasts[1][i] = {a, c, -ll(b), i};
    lasts[2][i] = {a, b, -ll(c), i};
  }

  sort(ALL(lasts[0]));
  sort(ALL(lasts[1]));
  sort(ALL(lasts[2]));
}

vector<ull> ans;
ull best = 0;

void query(ull k, ull i, ull x, ull y, ull z) {
  auto it = lower_bound(
      ALL(lasts[k]), tuple<ull, ull, ll, ull>({y, z, LLONG_MIN, 0})
  );

  if (i == get<3>(*it)) {
    it++;
  }

  if (it == lasts[k].end()) {
    return;
  }

  ull j_y = get<0>(*it);
  ull j_z = get<1>(*it);
  ull j_x = ull(-get<2>(*it));
  ull j = get<3>(*it);

  if (y == j_y && z == j_z) {
    ull new_best = min({x + j_x, y, z});
    if (new_best > best) {
      ans = {i, j};
      best = new_best;
    }
  }
}

vector<ull> solve(vector<ull>& as, vector<ull>& bs, vector<ull>& cs) {
  ull n = as.size();

  init(as, bs, cs);

  fore(i, 0, n) {
    ull new_best = min({as[i], bs[i], cs[i]});
    if (new_best > best) {
      ans = {i};
      best = new_best;
    }
  }

  fore(i, 0, n) {
    ull a = as[i], b = bs[i], c = cs[i];

    if (a < b && a < c) {
      query(0, i, a, b, c);
      query(0, i, a, c, b);
      query(1, i, a, b, c);
      query(1, i, a, c, b);
      query(2, i, a, b, c);
      query(2, i, a, c, b);
    }

    if (b < a && b < c) {
      query(0, i, b, a, c);
      query(0, i, b, c, a);
      query(1, i, b, a, c);
      query(1, i, b, c, a);
      query(2, i, b, a, c);
      query(2, i, b, c, a);
    }

    if (c < a && c < b) {
      query(0, i, c, b, a);
      query(0, i, c, a, b);
      query(1, i, c, b, a);
      query(1, i, c, a, b);
      query(2, i, c, b, a);
      query(2, i, c, a, b);
    }
  }

  return ans;
}

int main(void) {
  FIN;

  ull n;

  cin >> n;

  vector<ull> as(n), bs(n), cs(n);

  fore(i, 0, n) {
    cin >> as[i] >> bs[i] >> cs[i];
  }

  vector<ull> ans = solve(as, bs, cs);

  cout << ans.size() << '\n';

  for (ull a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';

  return 0;
}
