// https://codeforces.com/contest/2039/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

/** Author: Håkan Terelius
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: s[i] = smallest prime factor of i (except for i = 0, 1).
 * \texttt{sieve} returns sorted primes
 * less than L$. \texttt{fact} returns sorted {prime,
 * exponent} pairs of the factorization of n$.
 * Status: Stress-tested
 */
const ll L = 1e6;
array<ll, L> s;
vi sieve() {
  vi p;
  for (ll i = 4; i < L; i += 2) s[i] = 2;
  for (ll i = 3; i * i < L; i += 2) if (!s[i])
    for (ll j=i*i; j < L; j += 2*i) if (!s[j]) s[j] = i;
  fore(i,2,L) if (!s[i]) p.push_back(i), s[i] = i;
  return p;
}
vector<ii> fact(ll n) {
  vector<ii> res;
  for (; n > 1; n /= s[n]) {
    if (!SZ(res) || res.back().first!=s[n]) res.push_back({s[n],0});
    res.back().second++;
  }
  return res;
}

/** Author: Pietro Palombini
 * Date: 2024-10-11
 * License: CC0
 * Description: Given the prime factorization of a number,
 * returns all its divisors.
 * Time: O(d), where d$ is the number of divisors.
 * Status: stress-tested
 */
vi divisors(vector<ii>& f) {
  vi res = {1};
  for (auto& [p, k] : f) {
    ll sz = SZ(res);
    fore(i,0,sz) for(ll j=0,x=p;j<k;j++,x*=p) res.push_back(res[i]*x);
  }
  return res;
}

vi divisors(ull x) {
  vii f = fact((ll)x);
  return divisors(f);
}



bool isValid(vu& ans, ull i, ull x) {
  vi divs = divisors(i + 1);
  vu ks;

  for (ull j : divs) {
    for (ull k = j; k < i + 1; k += j) {
      if (gcd(i + 1, k) == j && gcd(ans[k - 1], x) == ans[j - 1]) {
        return false;
      }
    }
  }

  return true;
}

optional<vu> solve(ull n, vu& S) {
  ull m = S.size();
  vu ans(n, inf);
  ans[0] = S.back();

  fore(i, 0, n) {
    vii f = fact(i + 1);
    ull total = 0;
    for (auto [p, k] : f) {
      total += k;
    }
    if (total >= m) {
      return {};
    } else {
      ans[i] = S[m - 1 - total];
    }
  }

  return ans;
}

optional<vu> greedy(ull n, vu& S) {
  vu ans(n, inf);
  ans[0] = S.back();
  fore(i, 1, n) {
    for (ull x : views::reverse(S)) {
      bool valid = true;
      fore(j, 0, i) {
        if (gcd(ans[j], x) == ans[gcd(i + 1, j + 1) - 1]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        ans[i] = x;
        break;
      }
    }
    if (ans[i] == inf) {
      return {};
    }
  }
  return ans;
}

bool check(const vu&, vu);
optional<vu> force(ull n, vu& S) {
  ull m = S.size();

  ull lim = 1;
  fore(_, 0, n) {
    lim *= m;
  }

  vu ans;

  fore(mask, 0, lim) {
    ull x = mask;
    vu a;
    fore(_, 0, n) {
      a.push_back(S[x % m]);
      x /= m;
    }
    if (check(S, a)) {
      if (ans.empty() || a > ans) {
        ans = a;
      }
    }
  }

  if (ans.empty()) {
    return {};
  }
  return ans;
}

bool check(const vu& S, vu ans) {
  ull n = ans.size();
  for (ull a : ans) {
    if (lower_bound(ALL(S), a) == S.end()) {
      return false;
    }
  }

  fore(i, 0, n) fore(j, 0, i) {
    if (ans[gcd(i + 1, j + 1) - 1] == gcd(ans[i], ans[j])) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve();
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vu S(m);
    fore(j, 0, m) {
      cin >> S[j];
    }

    auto ans = solve(n, S);

    if (ans.has_value()) {
      for (auto x : ans.value()) {
        cout << x << ' ';
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }
#else
  fore(_, 0, 10000) {
    ull n = rand() % (100) + 1;
    ull m = rand() % n + 1;
    vu S;
    fore(_, 0, m) {
      S.push_back(rand() % n + 1);
    }
    sort(ALL(S));
    S.erase(unique(ALL(S)), S.end());
    m = S.size();

    auto ans = solve(n, S);
    auto forceAns = greedy(n, S);
    if (ans.has_value() != forceAns.has_value()) {
      cerr << "WA" << endl;
      cerr << n << ' ' << m << endl;
      for (ull x : S) {
        cerr << x << ' ';
      }
      return 1;
    } else if (ans.has_value() && ans != forceAns) {
      cerr << n << ' ' << m << endl;
      for (ull x : S) {
        cerr << x << ' ';
      }
      return 1;
    }
  }
#endif
}
