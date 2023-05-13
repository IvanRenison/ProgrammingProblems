// https://codeforces.com/contest/1832/problem/A

#include <bits/stdc++.h>

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

#define subiendo 1
#define bajando 2

ull solve1(vector<ull> as) {
  ull n = as.size();

  ull ans = 1;

  ull i = 1;
  while (i < n && as[i - 1] == as[i]) {
    i++;
  }
  while (i < n) {

    if (as[i - 1] <= as[i]) {
      while (i < n && as[i - 1] <= as[i]) {
        i++;
      }
    } else {
      while (i < n && as[i - 1] >= as[i]) {
        i++;
      }
    }

    ans++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
