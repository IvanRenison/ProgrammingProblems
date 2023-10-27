// https://codeforces.com/contest/1851/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)


tuple<ull, ull, ull> solve1(ull k, vector<ull>& as) {
  ull n = as.size();

  vector<pair<ull, ull>> as_i(n);
  fore(i, 0, n) {
    as_i[i] = {as[i], i};
  }

  sort(as_i.begin(), as_i.end());

  ull ans_i = 0;
  ull ans_val = 0;
  ull ans_x = 0;
  fore(j, 1, n) {
    ull ai = as_i[j-1].first, aj = as_i[j].first;
    ull x = ((1ull << k) - 1) ^ ai;
    ull this_ans = (ai ^ x) & (aj ^ x);

    if (this_ans > ans_val) {
      ans_val = this_ans;
      ans_i = j - 1;
      ans_x = x;
    }
  }

  //cerr << "ans_val: " << ans_val << '\n';

  return {as_i[ans_i].second, as_i[ans_i+1].second, ans_x};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(_, 0, t) {
    ull n, k;
    cin >> n >> k;
    vector<ull> as(n);
    for (ull& a : as) {
      cin >> a;
    }

    auto [i, j, x] = solve1(k, as);
    cout << i + 1 << ' ' << j + 1 << ' ' << x << '\n';
  }

  return EXIT_SUCCESS;
}
