// https://codeforces.com/gym/105327/problem/C
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;


struct SuffixArray {
  vi sa, lcp;
  SuffixArray(basic_string<ll>& s, ll lim) {
    ll n = SZ(s) + 1, k = 0, a, b;
    vi x(ALL(s)+1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y, iota(ALL(sa), 0);
    for (ll j = 0, p = 0; p < n; j = max(1ll, j*2), lim = p) {
      p = j, iota(ALL(y), n - j);
      fore(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(ALL(ws), 0);
      fore(i, 0, n) ws[x[i]]++;
      fore(i, 1, lim) ws[i] += ws[i - 1];
      for (ll i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      fore(i, 1, n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a+j] == y[b+j]) ? p - 1 : p++;
    }
    fore(i, 1, n) rank[sa[i]] = i;
    for (ll i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1]; s[i+k] == s[j+k]; k++);
  }
};



ii solve(basic_string<ll>& Vs) {
  ll N = Vs.size();

  SuffixArray sa(Vs, N + 1);

  vii lcp;
  fore(i, 2, N + 1) {
    lcp.push_back({sa.lcp[i], i - 1});
  }
  sort(ALL(lcp));

  ll sum = N * (N + 1) / 2;

  set<ll> used;
  for (auto [x, i] : lcp) {
    auto it = used.lower_bound(i);
    assert(it == used.end() || *it != i);

    ll i2 = it == used.end() ? N : *it;
    ll i0 = it == used.begin() ? 0 : *prev(it);

    ll diff0 = i - i0;
    ll diff1 = i2 - i;

    sum += (diff0 * diff1 * 2) * x;

    used.insert(i);
  }

  ll den = N * N;

  ll g = gcd(sum, den);

  return {sum/g, den/g};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  basic_string<ll> Vs;
  fore(_, 0, N) {
    ll V;
    cin >> V;
    Vs += V;
  }

  auto [P, Q] = solve(Vs);
  cout << P << '/' << Q << '\n';

}
