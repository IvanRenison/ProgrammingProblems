// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

tuple<ll, vector<ll>, vector<tuple<ll, ll, ll, ll, ll>>> parse1(void) {
  ll n, m, k;

  cin >> n >> m >> k;

  vector<ll> xs(n);

  fore(i, 0, n) {
    cin >> xs[i];
  }

  vector<tuple<ll, ll, ll, ll, ll>> abcdhs(k);
  fore(i, 0, k) {
    ll a, b, c, d, h;
    cin >> a >> b >> c >> d >> h;
    abcdhs[i] = {a - 1, b - 1, c - 1, d - 1, h};
  }

  return {m, xs, abcdhs};
}

/* If k is a key of the map return {{k, m[k]}}
 * If k is not a key of the map:
 *   If there is a key smaller and a key bigger then k, return
 *      {{smaller, m[smaller]}, {bigger, m[bigger]}}
 *   If there is only a key smaller then k, return {{smaller, m[smaller]}}
 *   If there is only a key bigger then k, return {{bigger, m[bigger]}}
 */
vector<pair<ll, ll>> find_in_map(map<ll, ll>& m, ll k) {
  auto it = m.find(k);
  if (it != m.end()) {
    return {{k, it->second}};
  }

  auto smaller_it = m.lower_bound(k);
  if (smaller_it == m.begin()) {
    auto bigger_it = m.upper_bound(k);
    return {{bigger_it->first, bigger_it->second}};
  }

  auto bigger_it = m.upper_bound(k);
  if (bigger_it == m.end()) {
    auto smaller_it = prev(m.upper_bound(k));
    return {{smaller_it->first, smaller_it->second}};
  }

  auto new_smaller_it = prev(m.upper_bound(k));
  return {
      {new_smaller_it->first, new_smaller_it->second},
      {bigger_it->first, bigger_it->second}};
}

optional<ll>
solve1(ll m, vector<ll>& xs, vector<tuple<ll, ll, ll, ll, ll>>& abcdhs) {
  ll n = xs.size();

  // For each room the room from where there is a ladder to it, and it h
  vector<map<ll, vector<tuple<ll, ll, ll>>>> adj_lower(n);
  vector<set<ll>> have_upper(n);
  for (auto [a, b, c, d, h] : abcdhs) {
    adj_lower[c][d].push_back({a, b, h});
    have_upper[a].insert(b);
  }
  have_upper[n - 1].insert(m - 1);

  vector<map<ll, ll>> dp(n);

  fore(j, 0, m) {
    dp[0][j] = j * xs[0];
  }

  fore(i, 1, n) {

    map<ll, ll> direct_ladders;
    for (auto [j, abhs] : adj_lower[i]) {
      for (auto [a, b, h] : abhs) {
        if (dp[a].count(b)) {
          if (direct_ladders.count(j)) {
            direct_ladders[j] = min(direct_ladders[j], dp[a][b] - h);
          } else {
            direct_ladders[j] = dp[a][b] - h;
          }
        }
      }
    }

    if (direct_ladders.empty()) {
      continue;
    }

    map<ll, ll> ladders_to_right;
    ladders_to_right[direct_ladders.begin()->first] =
        direct_ladders.begin()->second;
    for (auto it = next(direct_ladders.begin()); it != direct_ladders.end();
         it++) {
      auto prev_it = prev(it);
      ladders_to_right[it->first] =
          min(it->second, ladders_to_right[prev_it->first] +
                              abs(it->first - prev_it->first) * xs[i]);
    }

    map<ll, ll> ladders_to_left;
    ladders_to_left[direct_ladders.rbegin()->first] =
        direct_ladders.rbegin()->second;
    for (auto it = next(direct_ladders.rbegin()); it != direct_ladders.rend();
         it++) {
      auto prev_it = prev(it);
      ladders_to_left[it->first] =
          min(it->second, ladders_to_left[prev_it->first] +
                              abs(prev_it->first - it->first) * xs[i]);
    }

    map<ll, ll> ladders;
    for (auto [j, _] : ladders_to_left) {
      ladders[j] = min(ladders_to_right[j], ladders_to_left[j]);
    }

    for (auto j : have_upper[i]) {
      vector<pair<ll, ll>> ladders_to_j = find_in_map(ladders, j);
      if (ladders_to_j.size() == 1) {
        dp[i][j] =
            ladders_to_j[0].second + abs(ladders_to_j[0].first - j) * xs[i];
      } else {
        dp[i][j] =
            min(ladders_to_j[0].second + abs(ladders_to_j[0].first - j) * xs[i],
                ladders_to_j[1].second + abs(ladders_to_j[1].first - j) * xs[i]
            );
      }
    }
  }

  if (dp[n - 1].count(m - 1)) {
    return dp[n - 1][m - 1];
  } else {
    return {};
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll t;

  cin >> t;

  fore(i, 0, t) {
    auto [m, xs, abcdhs] = parse1();
    optional<ll> ans = solve1(m, xs, abcdhs);
    if (ans.has_value()) {
      cout << ans.value() << '\n';
    } else {
      cout << "NO ESCAPE" << '\n';
    }
  }

  return EXIT_SUCCESS;
}
