// https://codeforces.com/contest/433/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(vector<ull> ws) {
  ull sum = 0;
  ull count_1 = 0;
  for (ull w : ws) {
    sum += w;
    if (w == 1) {
      count_1++;
    }
  }

  return sum % 2 == 0 && (sum % 4 == 0 || count_1 > 0);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;

  cin >> n;

  vector<ull> ws(n);
  fore(i, 0, n) {
    ull w;
    cin >> w;
    ws[i] = w / 100;
  }

  if (solve(ws)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

  return EXIT_SUCCESS;
}
