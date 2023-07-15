// https://atcoder.jp/contests/abc310/tasks/abc310_c

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(vector<string> Ss) {
  set<string> S;
  for (string s : Ss) {
    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());
    if (S.find(s) == S.end() && S.find(s_rev) == S.end()) {
      S.insert(s);
    }
  }
  return S.size();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<string> Ss(N);
  fore(i, 0, N) {
    cin >> Ss[i];
  }

  auto ans = solve(Ss);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
