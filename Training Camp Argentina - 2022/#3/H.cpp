// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define MOD ull(1e9 + 7)

ull pow_mod(ull x, ull y) {
  ull res = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x) % MOD;
    }
    y = y / 2;
    x = (x * x) % MOD;
  }
  return res;
}

/**
 * Author: chilli
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
vector<ll> Z(const string& S) {
  vector<ll> z(S.size());
  ll l = -1, r = -1;
  rep(i, 1, S.size()) {
    z[i] = i >= r ? 0 : min(r - ll(i), z[i - l]);
    while (i + z[i] < S.size() && S[i + z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r)
      l = i, r = i + z[i];
  }
  return z;
}

ull solve(ull n, string p, vector<ull> ys) {
  ull m = ys.size();
  ull p_size = p.size();

  vector<ll> z = Z(p);

  vector<optional<char>> s(n);

  for (ull j = 0, i = 0; i < n && j < m; j++) {
    ull y = ys[j];

    if (i < y) {
      i = y;
    }
    if (y < i) {
      if (z[p_size - (i - y)] != i - y) {
        return 0;
      }
    }

    for (ull k = i - y; k < p_size; k++, i++) {
      s[i] = p[k];
    }
  }

  ull count = 0;
  for (optional<char> c : s) {
    if (!c.has_value()) {
      count++;
    }
  }

  return pow_mod(26, count);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;
  cin >> n >> m;

  string p;
  cin >> p;

  vector<ull> ys(m);
  for (ull& y : ys) {
    cin >> y;
    y--;
  }

  cout << solve(n, p, ys) << '\n';

  return EXIT_SUCCESS;
}
