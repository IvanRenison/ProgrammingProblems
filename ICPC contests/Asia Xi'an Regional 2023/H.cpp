// https://contest.ucup.ac/contest/1784/problem/9249

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

vu solve(ull n, ull k, const vu& as) {
  vu as_inv(1 << n);
  fore(i, 0, 1 << n) {
    as_inv[as[i]] = i;
  }

  vu ans(1 << n);

  vu counter(2 * (1 << n));

  fore(i, 0, 1 << n) {
    ull j = as_inv[i];

    ull this_ans = 0;

    ull x = j + (1 << n);
    fore(l, 0, n + 1) {
      ull total = 1 << l;
      ull less = counter[x];
      ull more = total - less - 1;
      ull less_out = i - less;

      if (more <= less_out && more <= k) {
        this_ans++;
      }

      counter[x]++;
      x /= 2;
    }

    ans[j] = this_ans - 1;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, k;
  cin >> n >> k;
  vu as(1 << n);
  for (ull& a : as) {
    cin >> a;
    a--;
  }

  vu ans = solve(n, k, as);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';
}
