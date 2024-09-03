// https://codeforces.com/gym/105321/problem/L
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll) x.size()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

struct Problem {
  vi As;
  ll N;

  vi ones_sums, odds_sums, pow2_sums;

  Problem(vi& As_) : As(As_), N(As.size()), ones_sums(N + 1), odds_sums(N + 1), pow2_sums(N + 1) {
    fore(i, 0, N) {
      ones_sums[i + 1] = ones_sums[i];
      odds_sums[i + 1] = odds_sums[i];
      pow2_sums[i + 1] = pow2_sums[i];
      if (As[i] == 1) {
        ones_sums[i + 1]++;
      } else if (As[i] % 2 == 1) {
        odds_sums[i + 1] += As[i];
      } else if ((As[i] & (As[i] - 1)) == 0) {
        pow2_sums[i + 1] += As[i];
      }
    }
  }

  char query(ll L, ll R) {
    ll ones = ones_sums[R] - ones_sums[L];
    ll odds = odds_sums[R] - odds_sums[L];
    ll pow2 = pow2_sums[R] - pow2_sums[L];

    ll agustin = (ones + 1) / 2 + pow2;
    ll braian = ones / 2 + odds;
    if (agustin == braian) {
      return 'E';
    } else if (agustin > braian) {
      return 'A';
    } else {
      return 'B';
    }
  }
};

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll N, Q;
  cin >> N >> Q;
  vi As(N);
  for (ll& A : As) {
    cin >> A;
  }

  Problem p(As);

  while (Q--) {
    ll L, R;
    cin >> L >> R;
    L--;
    cout << p.query(L, R) << '\n';
  }

}
