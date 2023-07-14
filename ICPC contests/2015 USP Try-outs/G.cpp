// https://codeforces.com/gym/101047/problem/G
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2) {
    if (e & 1) {
      ans = modmul(ans, b, mod);
    }
  }
  return ans;
}

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull a : A) {
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) {
      p = modmul(p, p, n);
    }
    if (p != n - 1 && i != s)
      return 0;
  }
  return 1;
}

ull pollard(ull n) {
  auto f = [n](ull x) { return modmul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) {
      x = ++i, y = f(x);
    }
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) {
      prd = q;
    }
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

vector<ull> factor(ull n) {
  if (n == 1) {
    return {};
  }
  if (isPrime(n)) {
    return {n};
  }
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}

bool solve1(ull N, vector<ull>& fs) {
  vector<ull> ps = factor(N);

  sort(ps.begin(), ps.end());

  fore(i, 0, ps.size()) {
    if (i == 0 || ps[i] != ps[i - 1]) {
      bool find = false;
      for (ull f : fs) {
        if (f % ps[i] == 0) {
          find = true;
          break;
        }
      }
      if (!find) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  FIN;

  ull T;
  cin >> T;
  while (T--) {
    ull N, K;
    cin >> N >> K;
    vector<ull> fs(K);
    for (ull& f : fs) {
      cin >> f;
    }
    if (solve1(N, fs)) {
      cout << "Y\n";
    } else {
      cout << "N\n";
    }
  }

  return 0;
}