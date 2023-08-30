// https://codeforces.com/contest/1863/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

vector<ull> invPerm(const vector<ull>& ps) {
  ull n = ps.size();
  vector<ull> ans(n);
  fore(i, 0, n) {
    ans[ps[i]] = i;
  }
  return ans;
}

ull solve1(const vector<ull>& ps) {
  ull n = ps.size();

  vector<ull> ips = invPerm(ps);

  ull ans = 0;
  for (ull i = n - 2; i < n; i--) {
    if (ips[i] > ips[i + 1]) {
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<ull> ps(n);
    fore(j, 0, n) {
      cin >> ps[j];
      ps[j]--;
    }

    auto ans = solve1(ps);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
