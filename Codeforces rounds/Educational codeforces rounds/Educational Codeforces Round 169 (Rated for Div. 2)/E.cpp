// https://codeforces.com/contest/2004/problem/E

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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


/* vu dp(100);

void init() {
  dp[0] = 0;
  fore(i, 1, 100) {
    set<ull> found;
    fore(j, 0, i) if (gcd(j, i) == 1) {
      found.insert(dp[j]);
    }

    fore(k, 0, i + 1) {
      if (!found.count(k)) {
        dp[i] = k;
        break;
      }
    }
  }
} */

const ull alim = 1e7 + 1;


vu prime_fact(alim);
vu primes;
void sieve(void) {
  fore(i, 0, alim) {
    prime_fact[i] = i;
  }

  fore(i, 2, alim) {
    if (prime_fact[i] == i) {
      primes.push_back(i);
      for (ull j = i * i; j < alim; j += i) {
        if (prime_fact[j] == j) {
          prime_fact[j] = i;
        }
      }
    }
  }
}


ull grundy(ull a) {
  if (a <= 1) {
    return a;
  }
  if (a % 2 == 0) {
    return 0;
  }

  ull p = prime_fact[a];

  ull i = lower_bound(ALL(primes), p) - primes.begin();
  i += 1;

  return i;
}



bool solve(vu& as) {
  ull x = 0;
  for (ull a : as) {
    x ^= grundy(a);
  }

  return x != 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();
/*   init();

  fore(i, 0, 100) {
    cout << i << " " << dp[i] << ' ' << grundy(i) << endl;
    assert(dp[i] == grundy(i));
  }
  return 0; */

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    bool ans = solve(as);
    if (ans) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }

}
