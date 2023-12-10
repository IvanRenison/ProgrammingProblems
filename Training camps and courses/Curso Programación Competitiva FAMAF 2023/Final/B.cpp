// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)


ull solve(vector<ull> as) {
  ull n = as.size();

  ull ans = 1;
  ull this_ans = 1;
  ull last = as[0];
  fore(i, 1, n) {
    ull a = as[i];
    if (a > last) {
      this_ans++;
      ans = max(ans, this_ans);
    } else {
      this_ans = 1;
    }
      last = a;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<ull> xs(n);
  fore(i, 0, n) {
    cin >> xs[i];
  }

  cout << solve(xs) << '\n';

  return EXIT_SUCCESS;
}
