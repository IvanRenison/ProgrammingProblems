// https://codeforces.com/contest/1850/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(vector<pair<ull, ull>> abs) {
  ull n = abs.size();
  ull ans = 0, q_ans = 0;
  fore(i, 0, n) {
    auto [a, b] = abs[i];
    if (a <= 10 && b > q_ans) {
      q_ans = b;
      ans = i;
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
    vector<pair<ull, ull>> abs(n);
    fore(j, 0, n) {
      cin >> abs[j].first >> abs[j].second;
    }

    auto ans = solve1(abs);
    cout << ans +1<< '\n';
  }

  return EXIT_SUCCESS;
}
