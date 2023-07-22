// https://codeforces.com/contest/1646/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve1(vector<ull> as) {
  ull n = as.size();
  sort(as.begin(), as.end());

  ull sum_end = as[n - 1];
  ull sum_start = as[0] + as[1];

  if (sum_end > sum_start) {
    return true;
  }

  ull end = n - 2;
  ull start = 2;

  while (start < end) {
    sum_end += as[end];
    sum_start += as[start];

    if (sum_end > sum_start) {
      return true;
    }

    end -= 1;
    start += 1;
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<ull> as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    if (solve1(as)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
