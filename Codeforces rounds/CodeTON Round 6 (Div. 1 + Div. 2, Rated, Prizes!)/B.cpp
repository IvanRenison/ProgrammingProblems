// https://codeforces.com/contest/1870/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solveMin(const vector<ull>& as, const vector<ull>& bs) {
  ull n = as.size();

  if (n % 2 == 0) {
    ull bor = 0;
    for(ull b : bs) {
      bor |= b;
    }

    ull ans = 0;
    for(ull a : as) {
      ans ^= (a | bor);
    }

    return ans;
  } else {
    ull ans = 0;
    for(ull a : as) {
      ans ^= a;
    }

    return ans;
  }

}

ull solveMax(const vector<ull>& as, const vector<ull>& bs) {
  ull n = as.size();

  if (n % 2 == 0) {
    ull ans = 0;
    for(ull a : as) {
      ans ^= a;
    }

    return ans;
  } else {
    ull bor = 0;
    for(ull b : bs) {
      bor |= b;
    }

    ull ans = 0;
    for(ull a : as) {
      ans ^= (a | bor);
    }

    return ans;
  }
}

pair<ull, ull> solve1(const vector<ull>& as, const vector<ull>& bs) {
  return {solveMin(as, bs), solveMax(as, bs)};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {

    ull n, m;
    cin >> n >> m;
    vector<ull> as(n), bs(m);
    fore(i, 0, n) {
      cin >> as[i];
    }
    fore(i, 0, m) {
      cin >> bs[i];
    }

    auto ans = solve1(as, bs);
    cout << ans.first << ' ' << ans.second << '\n';
  }

  return EXIT_SUCCESS;
}
