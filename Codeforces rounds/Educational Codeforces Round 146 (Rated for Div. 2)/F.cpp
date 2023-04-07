// https://codeforces.com/contest/1814/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

// stores disjoint intervals as [first, second)
typedef struct _s_disjoint_intervals {
  set<pair<ull, ull>> s;
  bool insert(pair<ull, ull> v) { // Return true if inserted, false if not
    if (v.first > v.second)
      return false;
    auto at = s.lower_bound(v);
    auto it = at;
    bool ans = false;
    if (at != s.begin() && (--at)->second >= v.first) {
      v.first = at->first, --it;
      ans = true;
    }
    ull n = 0;
    for (; it != s.end() && it->first <= v.second; s.erase(it++)) {
      v.second = max(v.second, it->second);
      n++;
    }
    s.insert(v);
    ans = ans || n > 1;
    return ans;
  }
  bool insert_many(const struct _s_disjoint_intervals& other) {
    bool ans = false;
    for (auto v : other.s) {
      insert(v);
      ans = ans || insert(v);
    }
    return ans;
  }
  struct _s_disjoint_intervals intersect(pair<ull, ull> v) const {
    struct _s_disjoint_intervals ans;
    if (v.first > v.second)
      return ans;
    auto at = s.lower_bound(v);
    auto it = at;
    if (at != s.begin() && (--at)->second >= v.first)
      ans.insert({at->first, min(at->second, v.second)});
    for (; it != s.end() && it->first <= v.second; ++it)
      ans.insert({it->first, min(it->second, v.second)});
    return ans;
  }
} disjoint_intervals;

enum visited_status { not_visited, in_queue, visited };

vector<ull> solve(vector<pair<ull, ull>> lrs, vector<pair<ull, ull>> edges) {
  ull n = lrs.size();
  ull m = edges.size();

  vector<vector<ull>> adj(n);
  fore(i, 0, m) {
    ull u = edges[i].first;
    ull v = edges[i].second;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<visited_status> visits(n, not_visited);
  vector<disjoint_intervals> reachable(n);

  set<ull> ans;

  reachable[0].insert({lrs[0].first, lrs[0].second});

  vector<ull> this_level = {0};
  visits[0] = in_queue;

  vector<ull> next_level;

  while (this_level.size() > 0) {
    for (ull u : this_level) {
      visits[u] = visited_status::visited;
      auto [l, r] = lrs[u];

      reachable[u] = reachable[u].intersect({l, r});

      if (reachable[u].s.size() == 0) {
        // No intersection
        continue;
      }

      ans.insert(u);

      for (ull v : adj[u]) {
        if (visits[v] == visited) {
          bool inserted = reachable[v].insert_many(reachable[u]);
          if (inserted) {
            visits[v] = in_queue;
            next_level.push_back(v);
          }
        }
        if (visits[v] == in_queue) {
          reachable[v].insert_many(reachable[u]);
        }
        if (visits[v] == not_visited) {
          visits[v] = in_queue;
          next_level.push_back(v);
          reachable[v].insert_many(reachable[u]);
        }
      }
    }

    this_level = next_level;
    next_level = {};
  }

  // Get a ordered vector of the set
  vector<ull> ans_(ans.begin(), ans.end());

  return ans_;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;

  cin >> n >> m;

  vector<pair<ull, ull>> lrs(n);
  fore(i, 0, n) {
    ull l, r;
    cin >> l >> r;
    lrs[i] = {l, r};
  }

  vector<pair<ull, ull>> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  vector<ull> ans = solve(lrs, edges);
  ull a = ans.size();

  cout << ans[0] + 1;
  fore(i, 1, a) {
    cout << " " << ans[i] + 1;
  }
  cout << endl;

  return EXIT_SUCCESS;
}
