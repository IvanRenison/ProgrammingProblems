// https://codeforces.com/gym/105327/problem/K
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

optional<vi> solve(const vi& as) {
  ll N = as.size();
  ll sum = accumulate(ALL(as), 0ll);

  if (sum % 2 == 1) {
    return {};
  }

  vector<vii> dp(N + 1, vii(sum / 2 + 1, {-1, -1}));
  // dp[i][j] = puede Alice tener j
  dp[0][0] = {0, 0};

  fore(i, 0, N) {
    dp[0][0] = {0, 0};
    dp[i + 1] = dp[i]; // Darle a Bob
    ll a = as[i];
    fore(j, 0, sum / 2 + 1 - a) {
      if (dp[i][j].first != -1) {
        dp[i + 1][j + a] = {i, j};
      }
    }
  }

  if (dp[N][sum / 2].first == -1) {
    return {};
  }

  vi alice;
  for (ll j = sum / 2, i = N; i > 0; tie(i, j) = dp[i][j], alice.push_back(i)) {
  }

  ll acc = 0;
  for (ll i : alice) {
    acc += as[i];
  }
  if (acc != sum / 2) {
    alice.pop_back();
  }

  vector<bool> alice_(N, false);
  for (ll i : alice) {
    alice_[i] = true;
  }

  vi bob;
  fore(i, 0, N) {
    if (!alice_[i]) {
      bob.push_back(i);
    }
  }

  ll sum_alice = 0, sum_bob = 0;
  vi ans;
  for (ll i = 0, j = 0; i < alice.size() || j < bob.size(); ) {
    if (sum_alice <= sum_bob) {
      assert(i < alice.size());
      ans.push_back(as[alice[i]]);
      sum_alice += as[alice[i]];
      i++;
    } else {
      assert(j < bob.size());
      ans.push_back(as[bob[j]]);
      sum_bob += as[bob[j]];
      j++;
    }
  }

  return ans;
}

bool check(const vi& as) {
  ll A = 0, B = 0;
  for (ll a : as) {
    if (A <= B) {
      A += a;
    } else {
      B += a;
    }
  }
  return A == B;
}

bool force(vi as) {
  sort(ALL(as));

  do {
    if (check(as)) {
      return true;
    }
  } while (next_permutation(ALL(as)));

  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  ll N;
  cin >> N;
  vi as(N);
  for (ll& a : as) {
    cin >> a;
  }

  auto ans = solve(as);
  if (ans.has_value()) {
    for (ll a : *ans) {
      cout << a << ' ';
    }
  } else {
    cout << "-1";
  }
  cout << '\n';
#else
  fore(_, 0, 10000) {
    ll N = rand() % 5 + 1;
    vi as(N);
    for (ll& a : as) {
      a = rand() % 5 + 1;
    }

    cerr << N << '\n';
    for (ll a : as) {
      cerr << a << ' ';
    }
    cerr << '\n' << endl;
    bool ansf = force(as);
    optional<vi> ans = solve(as);
    if ((!ansf && ans.has_value()) || (ansf && !ans.has_value()) || (ans.has_value() && !check(*ans))) {
      return 1;
    }
  }
#endif
}
