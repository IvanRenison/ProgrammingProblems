// https://codeforces.com/contest/1833/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

pair<vector<ll>, vector<ll>> parse1(void) {
  ll n, k;
  cin >> n >> k;

  vector<ll> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  vector<ll> bs(n);
  fore(i, 0, n) {
    cin >> bs[i];
  }

  return {as, bs};
}

vector<ll> solve1(vector<ll> as, vector<ll> bs) {
  ll n = as.size();

  vector<pair<ll, ll>> as_indexed(n);
  fore(i, 0, n) {
    as_indexed[i] = {as[i], i};
  }

  sort(as_indexed.begin(), as_indexed.end());

  sort(bs.begin(), bs.end());

  vector<ll> ans(n);

  fore(i, 0, n) {
    ans[as_indexed[i].second] = bs[i];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll t;

  cin >> t;

  fore(i, 0, t) {
    auto [as, bs] = parse1();
    vector<ll> ans = solve1(as, bs);
    fore(i, 0, ans.size()) {
      cout << ans[i] << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
