// https://cses.fi/problemset/task/2205

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


vector<string> solve(ull n) {
  if (n == 1) {
    return {"0", "1"};
  }

  vector<string> ans = solve(n - 1);

  vector<string> ans2 = ans;
  reverse(ans2.begin(), ans2.end());

  fore(i, 0, ans.size()) {
    ans[i].push_back('0');
    ans2[i].push_back('1');
  }

  ans.insert(ans.end(), ans2.begin(), ans2.end());

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;

  auto ans = solve(n);
  for (auto s : ans) {
    cout << s << '\n';
  }

  return EXIT_SUCCESS;
}
