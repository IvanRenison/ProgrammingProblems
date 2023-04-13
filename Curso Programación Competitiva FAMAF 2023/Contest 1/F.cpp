// https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(ull n, vector<ull> as) {
  ull m = as.size();
  map<ull, ull> problems;
  vector<ull> ans(m);

  fore(i, 0, m) {
    ull a = as[i];
    problems[a]++;
    if (problems.size() == n) {
      ans[i] = 1;
      for (auto it = problems.begin(); it != problems.end();) {
        it->second--;
        if (it->second == 0) {
          it = problems.erase(it);
        } else {
          it++;
        }
      }
    } else {
      ans[i] = 0;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;

  cin >> n >> m;

  vector<ull> a(m);
  fore(i, 0, m) {
    cin >> a[i];
  }

  vector<ull> ans = solve(n, a);
  for (ull a : ans) {
    cout << a;
  }
  cout << "\n";

  return EXIT_SUCCESS;
}
