// https://codeforces.com/gym/104871/problem/K

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef vector<bool> vb;
typedef pair<ull, bool> ub;
typedef vector<ub> vub;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()

const ull inf = 1ull << 60;

optional<vuu>
findPath(const vector<vuu>& adj, ull from, ull to) {
  ull n = adj.size();

  vuu added_by(n, {inf, inf});

  added_by[to] = {inf, inf};

  uu found_cicle = {inf, inf};

  function<bool(ull, ull)> dfs = [&](ull u, ull e) -> bool {
    for (auto [v, f] : adj[u]) {
      if (e != f) {
        if (v == from) {
          found_cicle = {u, f};
          return true;
        } else if (added_by[v].first == inf) {
          added_by[v] = {u, f};
          bool rec = dfs(v, f);
          if (rec) {
            return true;
          }
        }
      }
    }
    return false;
  };

  dfs(to, inf);

  if (found_cicle.first == inf) {
    return {};
  }

  vuu path;

  path.push_back(found_cicle);

  for (ull u = found_cicle.first; u != 1; u = added_by[u].first) {
    path.push_back(added_by[u]);
  }

  return path;
}

optional<tuple<vu, vu, vector<pair<ull, vu>>, vub>>
solve(ull n, const vuu& edges) {
  ull m = edges.size();

  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }

  // Find cicle including node 1
  vuu next_in_cicle;
  {
    auto next_in_cicle_ = findPath(adj, 1, 1);
    if (!next_in_cicle_.has_value()) {
      return {};
    }
    next_in_cicle = *next_in_cicle_;
  }

  vu in_cicle(n, inf);
  fore(i, 0, next_in_cicle.size()) {
    auto [u, _] = next_in_cicle[i];
    in_cicle[u] = i;
  }

  // Find path from 0 to 1
  vuu next_in_path = *findPath(adj, 0, 1);


  vu kAlice, kBob;
  vector<pair<ull, vu>> Alice;
  vub Bob;

  ull pos_in_cicle = inf;

  if (in_cicle[0] != inf) {
    pos_in_cicle = in_cicle[0];
  } else {
    for (auto [u, e] : next_in_path) {
      kAlice.push_back(e);
      Alice.push_back({u, {}});
      if (u != 1 && in_cicle[u] != inf) {
        pos_in_cicle = in_cicle[u];
        break;
      }
    }
  }

  ull cicle_size = next_in_cicle.size();
  assert(cicle_size > 2);

  if (pos_in_cicle != inf) {

    ull path_size = Alice.size();

    Alice.push_back({inf, kAlice});

    fore(i, pos_in_cicle + 1, cicle_size) {
      auto [u, e] = next_in_cicle[i];
      Alice.push_back({u, {}});
      kAlice.push_back(e);
    }

    fore(i, 0, pos_in_cicle) {
      auto [u, e] = next_in_cicle[i];
      Bob.push_back({u, false});
      kBob.push_back(e);
    }
    kBob.push_back(next_in_cicle[pos_in_cicle].second);
    Bob.push_back({next_in_cicle[pos_in_cicle].first, true});

    fore(i, 1, path_size) {
      auto [u, _] = Alice[path_size - 1 - i];
      Bob.push_back({u, false});
    }
    if (path_size > 0) {
      Bob.push_back({0, false});
    }

    return {{kAlice, kBob, Alice, Bob}};
  } else {
    ull path_size = Alice.size();
    auto [_, last_e] = next_in_cicle.back();
    auto [last_u, __] = next_in_cicle[cicle_size - 2];

    Alice.push_back({last_u, {kAlice}});
    Alice.push_back({1, {}});
    kAlice.push_back(last_e);

    fore(i, 0, cicle_size - 2) {
      auto [u, e] = next_in_cicle[i];
      kBob.push_back(e);
      Bob.push_back({u, false});
    }
    Bob.push_back({next_in_cicle[cicle_size - 2].first, true});
    kBob.push_back(next_in_cicle[cicle_size - 2].second);
    fore(i, 0, cicle_size - 2) {
      auto [u, e] = next_in_cicle[cicle_size - 3 - i];
      Bob.push_back({u, false});
    }

    Bob.push_back({1, false});

    fore(i, 1, path_size) {
      auto [u, _] = Alice[path_size - 1 - i];
      Bob.push_back({u, false});
    }
    Bob.push_back({0, false});

    return {{kAlice, kBob, Alice, Bob}};
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
  }

  auto ans = solve(n, edges);
  if (ans.has_value()) {
    auto [kalice, kbob, alice, bob] = *ans;
    for (ull k : kalice) {
      cout << k << ' ';
    }
    cout << '\n';
    for (ull k : kbob) {
      cout << k << ' ';
    }
    cout << '\n';
    for (auto& [u, ks] : alice) {
      if (u != inf) {
        cout << "MOVE " << u << '\n';
      }
      if (!ks.empty()) {
        cout << "DROP";
        for (ull k : ks) {
          cout << ' ' << k;
        }
        cout << '\n';
      }
    }
    cout << "DONE\n";

    for (auto& [u, grab] : bob) {
      cout << "MOVE " << u << '\n';
      if (grab) {
        cout << "GRAB\n";
      }
    }
    cout << "DONE\n";

  } else {
    cout << "No solution\n";
  }

  return EXIT_SUCCESS;
}
