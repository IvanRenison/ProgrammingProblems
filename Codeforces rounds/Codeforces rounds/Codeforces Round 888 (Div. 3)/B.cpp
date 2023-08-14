// https://codeforces.com/contest/1851/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve1(const vector<ull>& as) {
  ull n = as.size();
  vector<ull> as_copy = as;
  sort(as_copy.begin(), as_copy.end());
  fore(i, 0, n) {
    if (as[i] % 2 != as_copy[i] % 2) {
      return false;
    }
  }
  return true;
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
