// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull mod = 998244353;

const ull max_sz = 2e5;
vu fact(max_sz + 1);

void init() {
  fact[0] = 1;
  fore(i, 1, max_sz + 1) {
    fact[i] = (fact[i - 1] * i) % mod;
  }
}

uu solve(const string& s) {
  ull n = s.size();

  ull m = 0;
  vu cnt = {1};

  fore(i, 1, n) {
    if (s[i] == s[i - 1]) {
      m++;
      cnt.back()++;
    } else {
      cnt.push_back(1);
    }
  }

  ull ans = 1;
  for (ull c : cnt) {
    ans *= c;
    ans %= mod;
  }

  ans *= fact[m];
  ans %= mod;

  return {m, ans};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  ull t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    auto [m, c] = solve(s);
    cout << m << ' ' << c << '\n';
  }

  return EXIT_SUCCESS;
}
