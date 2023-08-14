// https://codeforces.com/contest/1851/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve1(ull k, vector<ull> cs) {
  ull n = cs.size();

  if (cs[0] == cs[n - 1]) {
    ull count = 0;
    fore(i, 0, n) {
      if (cs[i] == cs[0]) {
        count++;
      }
    }
    return count >= k;
  } else {
    ull count_first = 0, count_last = 0;
    ull i;
    for (i = 0; i < n && count_first < k; i++) {
      if (cs[i] == cs[0]) {
        count_first++;
      }
    }
    for (; i < n && count_last < k; i++) {
      if (cs[i] == cs[n - 1]) {
        count_last++;
      }
    }
    return count_first >= k && count_last >= k;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vector<ull> cs(n);
    fore(j, 0, n) {
      cin >> cs[j];
    }

    if (solve1(k, cs)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
