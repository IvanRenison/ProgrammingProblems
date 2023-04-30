// https://codeforces.com/contest/230/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(ull s, vector<pair<ull, ull>> xys) {
  ull n = xys.size();
  sort(xys.begin(), xys.end());

  fore(i, 0, n) {
    if (s > xys[i].first) {
      s += xys[i].second;
    } else {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull s, n;

  cin >> s >> n;

  vector<pair<ull, ull>> xys(n);

  fore(i, 0, n) {
    cin >> xys[i].first >> xys[i].second;
  }

  if (solve(s, xys)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

  return EXIT_SUCCESS;
}
