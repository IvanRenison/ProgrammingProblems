// https://codeforces.com/contest/1798/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

vector<vector<ll>> parse1(void) {
  ll m;
  cin >> m;

  vector<vector<ll>> v(m);

  fore(i, 0, m) {
    ll n;
    cin >> n;
    vector<ll> as(n);
    fore(j, 0, n) {
      ll a;
      cin >> a;
      as[j] = a - 1;
    }
    v[i] = as;
  }

  return v;
}

vector<ll> solve1(vector<vector<ll>> ass) {
  ll m = ass.size();

  vector<ll> ans(m);

  fore(i, 0, m) {
    ans[i] = -1;
  }

  vector<bool> participants(50000);

  for (ll i = m - 1; i >= 0; i--) {
    vector<ll> as_i = ass[i];
    for (ll a : as_i) {
      if (!participants[a]) {
        participants[a] = true;
        ans[i] = a + 1;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;

  cin >> t;

  for (ll i = 0; i < t; i++) {
    vector<ll> ans = solve1(parse1());
    bool has_neg1 = false;
    for (ll p : ans) {
      if (p == -1) {
        has_neg1 = true;
        break;
      }
    }
    if (has_neg1) {
      cout << -1 << endl;
      continue;
    }
    for (ll p : ans) {
      cout << p << " ";
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
}
