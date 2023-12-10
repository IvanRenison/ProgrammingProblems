// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull k, vector<ull> as, vector<ull> bs) {
  ull n = as.size();

  vector<pair<ull, ull>> ab_s(n);
  fore(i, 0, n) {
    ab_s[i] = {as[i], bs[i]};
  }

  sort(ab_s.begin(), ab_s.end());

  for (auto [a, b] : ab_s) {
    if (k < a) {
      return k;
    }
    k += b;
  }

  return k;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vector<ull> as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    vector<ull> bs(n);
    fore(j, 0, n) {
      cin >> bs[j];
    }
    cout << solve1(k, as, bs) << "\n";
  }

  return EXIT_SUCCESS;
}
