//

#ifdef PRAGMAS
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

/** Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Description: Prime sieve for generating all primes smaller than LIM.
 * Time: O(n \log \log n); LIM=1e9 $\approx$ 1.5s
 * Status: Stress-tested
 * Details: Despite its n log log n complexity, segmented sieve is still faster
 * than other options, including bitset sieves and linear sieves. This is
 * primarily due to its low memory usage, which reduces cache misses. This
 * implementation skips even numbers.
 *
 * Benchmark can be found here: https://ideone.com/e7TbX4
 *
 * The line `for (ll i=idx; i<S+L; idx = (i += p))` is done on purpose for performance reasons.
 * Se https://github.com/kth-competitive-programming/kactl/pull/166#discussion_r408354338
 */
const ll LIM = 1e7 + 1;
bitset<LIM> isPrime;
vi eratosthenes() {
  const ll S = (ll)round(sqrt(LIM)), R = LIM / 2;
  vi pr = {2}, sieve(S+1); pr.reserve(ll(LIM/log(LIM)*1.1));
  vector<ii> cp;
  for (ll i = 3; i <= S; i += 2) if (!sieve[i]) {
    cp.push_back({i, i * i / 2});
    for (ll j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
  }
  for (ll L = 1; L <= R; L += S) {
    array<bool, S> block{};
    for (auto &[p, idx] : cp)
      for (ll i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
    fore(i,0,min(S, R - L))
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  for (ll i : pr) isPrime[i] = 1;
  return pr;
}

vi primes;

typedef bitset<LIM> B;

vu solve(vu Ns) {
  vuu Nis(Ns.size());
  fore(j, 0, Ns.size()) {
    Nis[j] = {Ns[j], j};
  }
  sort(ALL(Nis));
  B vals;
  vu ans(Ns.size());
  ull j = 0;
  for (ll p : primes) {
    while (p > Nis[j].first) {
      ull count = 0;
      fore(i, 2, Nis[j].first + 1) if (isPrime[i]) {
        if (vals[LIM - i]) {
          count++;
        }
      }
      ans[Nis[j].second] = count;
      j++;
      if (j == Ns.size()) {
        break;
      }
    }
    vals |= isPrime << (LIM - p);
  }
  while (j < Ns.size()) {
    ull count = 0;
    fore(i, 2, Nis[j].first + 1) if (isPrime[i]) {
      if (vals[LIM - i]) {
        count++;
      }
    }
    ans[Nis[j].second] = count;
    j++;
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  primes = eratosthenes();

  ull t;
  cin >> t;

  vu Ns(t);
  for (ull& N : Ns) {
    cin >> N;
  }

  vu ans = solve(Ns);

  fore(testCase, 0, t) {

    cout << "Case #" << testCase + 1 << ": ";
    cout << ans[testCase] << '\n';
  }

}
