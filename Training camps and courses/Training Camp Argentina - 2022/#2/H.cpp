// https://codeforces.com/group/4zVk9dZl6Q/contest/390672/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(ull s, vector<ull> as, vector<ull> bs) {
  ull n = as.size();
  if (as[0] == 0) {
    return false;
  }
  if (as[s - 1] == 1) {
    return true;
  }
  if (bs[s - 1] == 0) {
    return false;
  }
  fore(i, s, n) {
    if (as[i] == 1 && bs[i] == 1) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, s;
  cin >> n >> s;

  vector<ull> as(n), bs(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  fore(i, 0, n) {
    cin >> bs[i];
  }

  if (solve(s, as, bs)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
