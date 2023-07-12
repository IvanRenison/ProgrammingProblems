// https://codeforces.com/group/4zVk9dZl6Q/contest/391178/problem/K
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define MOD 998244353
#define NMAX ll(3 * 1e5 + 1)

ll fact[NMAX];

void init() {
  fact[0] = 1;
  fore(i, 1, NMAX) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }
}

ll solve(vector<pair<ll, ll>> abs) {
  ll n = abs.size();

  vector<ll> count_a(n);
  vector<ll> count_b(n);

  for (auto [a, b] : abs) {
    count_a[a]++, count_b[b]++;
  }

  ll count_a_sorted = 1;
  for (ll c : count_a) {
    count_a_sorted = (count_a_sorted * fact[c]) % MOD;
  }
  ll count_b_sorted = 1;
  for (ll c : count_b) {
    count_b_sorted = (count_b_sorted * fact[c]) % MOD;
  }

  sort(abs.begin(), abs.end());
  bool sorted = true;
  fore(i, 1, n) {
    if (abs[i].second < abs[i - 1].second) {
      sorted = false;
      break;
    }
  }

  ll count_ab_sorted = 0;
  if (sorted) {
    count_ab_sorted = 1;
    auto [last_a, last_b] = abs[0];
    ll count_equals = 1;
    fore(i, 1, n) {
      auto [a, b] = abs[i];
      if (a == last_a && b == last_b) {
        count_equals++;
      } else {
        count_ab_sorted = (count_ab_sorted * fact[count_equals]) % MOD;
        count_equals = 1;
      }
      last_a = a, last_b = b;
    }
    count_ab_sorted = (count_ab_sorted * fact[count_equals]) % MOD;
  }

  ll neg_ans =
      (((count_a_sorted + count_b_sorted) % MOD - count_ab_sorted) % MOD + MOD
      ) %
      MOD;

  return ((fact[n] - neg_ans) % MOD + MOD) % MOD;
}

int main() {
  FIN;

  init();

  ll n;
  cin >> n;
  vector<pair<ll, ll>> abs(n);
  fore(i, 0, n) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    abs[i] = {a, b};
  }

  cout << solve(abs) << '\n';

  return 0;
}