// https://codeforces.com/group/id8eYTCwzg/contest/445210/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(ull n) {
  return vector<ull>(n, 1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<ull> ans = solve(n);
  cout << ans.size() << "\n";
  fore(i, 0, ans.size()) {
    cout << ans[i] << " ";
  }
  cout << "\n";

  return EXIT_SUCCESS;
}
