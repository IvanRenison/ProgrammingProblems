// https://codeforces.com/contest/1916/problem/A

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

#define MAXN 100001

/* For each number until N get the smallest prime that divides it */
vu smallest_prime_factors(MAXN);
void sieve(void) {
  for (ull i = 1; i < MAXN; i++) {
    if (i % 2 == 0) {
      smallest_prime_factors[i] = 2;
    } else {
      smallest_prime_factors[i] = i;
    }
  }

  for (ull i = 3; i * i < MAXN; i += 2) {
    if (smallest_prime_factors[i] == i) {
      for (ull j = i * i; j < MAXN; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }
}

/* smallest_prime_factors has to have the smallest prime factor of each number until x */
vuu prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vuu factors = {{smallest_prime_factors[x], 1}};
    x = ull(x / smallest_prime_factors[x]);
    while (x != 1) {
      if (smallest_prime_factors[x] != factors.back().first) {
        factors.push_back({smallest_prime_factors[x], 0});
      }
      factors.back().second++;
      x = ull(x / smallest_prime_factors[x]);
    }
    return factors;
  }
}


vu solve1(vu as, ull k) {
  ull prod = 1;
  for (ull a : as) {
    prod *= a;
  }

  if (2023 % prod != 0) {
    return {};
  }

  vuu factors = prime_factors(2023 / prod);

  vu f;
  for (uu factor : factors) {
    fore(i, 0, factor.second) {
      f.push_back(factor.first);
    }
  }

  vu ans(k);
  if (f.size() < k) {
    fore(i, 0, f.size()) {
      ans[i] = f[i];
    }
    fore(i, f.size(), k) {
      ans[i] = 1;
    }
  } else {

    fore(i, 0, k) {
      ans[i] = f[i];
    }
    fore(i, k, f.size()) {
      ans[k - 1] *= f[i];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  sieve();

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vu as(n);
    fore(j, 0, n) cin >> as[j];

    auto ans = solve1(as, k);
    if (ans.size() > 0) {
      cout << "YES\n";
      fore(j, 0, ans.size()) cout << ans[j] << " ";
      cout << "\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
