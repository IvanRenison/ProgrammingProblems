// https://codeforces.com/contest/1646/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN 1000001
#define LOG_MAXN 20

ull log_base(ull i, ull n) {
  ull ans = 1;
  ull x = i;
  while (x <= n) {
    ans++;
    x *= i;
  }
  return ans - 1;
}

ull solve(ull n, ull m) {
  vector<ull> n_diff_prod(LOG_MAXN + 1);

  n_diff_prod[0] = 0;
  vector<bool> numbers((m + 1) * (LOG_MAXN + 1));
  fore(i, 1, LOG_MAXN + 1) {
    n_diff_prod[i] = n_diff_prod[i - 1];
    fore(j, 1, m + 1) {
      if (!numbers[i * j]) {
        numbers[i * j] = true;
        n_diff_prod[i]++;
      }
    }
  }

  vector<bool> counted(n + 1, false);
  counted[1] = true;

  ull ans = 1;
  fore(i, 2, n + 1) {
    if (!counted[i]) {
      ans += n_diff_prod[log_base(i, n)];
      for (ull j = i; j <= n; j *= i) {
        counted[j] = true;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  ull ans = solve(n, m);
  cout << ans << endl;

  return EXIT_SUCCESS;
}
