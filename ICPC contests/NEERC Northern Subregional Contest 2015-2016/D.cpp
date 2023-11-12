// https://codeforces.com/gym/100801
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

ull pow3(ull n) {
  ull ans = 1;
  while (ans <= n) {
    ans *= 3;
  }
  return ans / 3;
}

vector<ull> solve1(ull n) {
  if (n == 0) {
    return {};
  } else if (n % 2 == 0) {
    vector<ull> ans = solve1(n / 2);
    for (ull& a : ans) {
      a *= 2;
    }
    return ans;
  } else {
    ull x = pow3(n);
    vector<ull> ans = solve1(n - x);
    ans.push_back(x);
    return ans;
  }
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("distribution.in", "r", stdin);
  freopen("distribution.out", "w", stdout);
#endif

  ull t;
  cin >> t;

  while (t--) {
    ull n;
    cin >> n;
    auto ans = solve1(n);
    cout << ans.size() << '\n';
    for (ull a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

  return 0;
}
