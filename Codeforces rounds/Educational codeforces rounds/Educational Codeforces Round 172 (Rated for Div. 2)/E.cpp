// https://codeforces.com/contest/2042/problem/E

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

/** Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

/** Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: O(N \log N + Q)$
 * Status: stress-tested
 */
struct LCA {
  ll T = 0;
  vi time, path, ret;
  RMQ<ll> rmq;

  LCA(vector<vu>& C, ull root) : time(SZ(C)), rmq((dfs(C,root,-1), ret)) {}
  void dfs(vector<vu>& C, ll v, ll par) {
    time[v] = T++;
    for (ull y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }

  ll lca(ll a, ll b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  //dist(a,b) {return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

vu solve(vu& as, vuu& edges, ull root) {
  ull n = as.size() / 2;

  vector<vu> aps(n);
  fore(i, 0, 2 * n) {
    aps[as[i]].push_back(i);
  }
  auto comp = [&](ull u) -> ull {
    return aps[as[u]][0] == u ? aps[as[u]][1] : aps[as[u]][0];
  };

  vector<vu> adj(2 * n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vu pars(2 * n);
  {
    vuu s = {{root, inf}};
    for (ull i = 0; i < s.size(); i++) {
      auto [u, p] = s[i];
      pars[u] = p;
      for (ull v : adj[u]) if (v != p) {
        s.push_back({v, u});
      }
    }
  }

  LCA lca(adj, root);

  vu ans = {root};
  vb in_ans(2 * n, false), not_in_ans(2 * n, false);
  in_ans[root] = true;

  auto add = [&](ull u) {
    while (!in_ans[u]) {
      ans.push_back(u);
      in_ans[u] = true;
      u = pars[u];
    }
  };

  fore(i, 0, n) {
    ull u = aps[i][0], v = aps[i][1];

    ull p = lca.lca(u, v);
    add(p);
  }

  for (ull u = 2 * n; u--; ) {
    if (!in_ans[u]) {
      ull v = comp(u);
      bool change = false;
      if (not_in_ans[v]) {
        assert(!not_in_ans[u]);
        v = u;
        change = true;
      }

      add(v);

      if (!change && !not_in_ans[u]) {
        vu s = {u};
        for (ull i = 0; i < s.size(); i++) {
          ull u_ = s[i];
          if (!not_in_ans[u_]) {
            add(comp(u_));
            not_in_ans[u_] = true;
            for (ull v_ : adj[u_]) if (v_ != pars[u_]) {
              s.push_back(v_);
            }
          }
        }
      }
    }
  }

  sort(ans.rbegin(), ans.rend());

  return ans;
}

vu solve(vu& as, vuu& edges) {
  ull n = as.size() / 2;

  vu ans;
  ull i = 0;
  for (;; i++) {
    if (as[i] == n - 1) {
      ans = solve(as, edges, i);
      i++;
      break;
    }
  }
  for (;; i++) {
    if (as[i] == n - 1) {
      vu new_ans = solve(as, edges, i);
      if (new_ans < ans) {
        ans = new_ans;
      }
      break;
    }
  }

  return ans;
}

/* Prufer Code to Tree
 * Complexity: O(V log V)
 */
vuu pruferCodeToTree(const vu& pruferCode) {
  // Stores number count of nodes in the prufer code
  unordered_map<ull, ull> nodeCount;

  // Set of integers absent in prufer code. They are the leaves
  set<ull> leaves;

  ull len = pruferCode.size();
  ull node = len + 2;

  // Count frequency of nodes
  fore(i, 0, len) {
    ull t = pruferCode[i];
    nodeCount[t]++;
  }

  // Find the absent nodes
  fore(i, 1, node + 1) {
    if (nodeCount.find(i) == nodeCount.end()) leaves.insert(i);
  }

  vuu edges;
  /* Connect Edges */
  fore(i, 0, len) {
    ull a = pruferCode[i]; // First node

    //Find the smallest number which is not present in prufer code now
    ull b = *leaves.begin(); // the leaf

    edges.push_back({a, b}); // Edge of the tree

    leaves.erase(b); // Remove from absent list
    nodeCount[a]--; // Remove from prufer code
    if (nodeCount[a] == 0) leaves.insert(a); // If a becomes absent
  }

  // The final edge
  edges.push_back({*leaves.begin(), *leaves.rbegin()});
  return edges;
}

vuu genRandomTree(ull n) {
  vu pruferCode;
  fore(i, 0, n - 2) {
    pruferCode.push_back(rand() % (n - 1) + 1);
  }
  auto edges = pruferCodeToTree(pruferCode);
  for (auto &[u, v] : edges) u--, v--;
  return edges;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull n;
  cin >> n;
  vu as(2 * n);
  for (ull& a : as) {
    cin >> a;
    a--;
  }
  vuu edges(2 * n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(as, edges);
  cout << ans.size() << '\n';
  for (ull a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';
#else
  fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    vu as(2 * n);
    fore(i, 0, n) {
      as[2 * i] = as[2 * i + 1] = i;
    }
    vuu edges = genRandomTree(2 * n);
    cerr << n << '\n';
    for (ull a : as) {
      cerr << a + 1 << ' ';
    }
    cerr << '\n';
    for (auto [u, v] : edges) {
      cerr << u + 1 << ' ' << v + 1 << '\n';
    }
    cerr << endl;
    auto ans = solve(as, edges);
  }
#endif
}
