// https://codeforces.com/contest/1807/problem/E

#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

ull query(ull i, ull j) {
  cout << "? " << j - i << ' ';
  fore(k, i, j) {
    cout << k + 1 << " ";
  }
  cout << endl;

  ull x;
  cin >> x;

  return x;
}

ull solve1(const vector<ull>& as) {
  ull n = as.size();

  vector<ull> prefixes_sum(n + 1);

  prefixes_sum[0] = 0;
  fore(i, 0, n) {
    prefixes_sum[i + 1] = prefixes_sum[i] + as[i];
  }

  auto in_range = [as, prefixes_sum](ull i, ull j) {
    return query(i, j) != prefixes_sum[j] - prefixes_sum[i];
  };

  ull lower = 0;
  ull upper = n;

  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (in_range(lower, m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper - 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << "! " << ans + 1 << endl;
  }

  return EXIT_SUCCESS;
}