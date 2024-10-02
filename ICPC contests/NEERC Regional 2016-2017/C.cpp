// https://codeforces.com/gym/101190

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

vector<vu> findCycles(const vector<vu>& adj) {
  ull n = adj.size();

  vector<vu> ans;

  vb vis(n, false);
  vector<set<ull>> cycle_added(n);
  vu par(n, inf);

  function<void(ull)> dfs = [&](ull u) {
    vis[u] = true;
    for (ull v : adj[u]) if (!cycle_added[u].count(v)) {
      if (!vis[v]) {
        par[v] = u;
        dfs(v);
      } else if (v != par[u]) {
        vu cycle;
        for (ull x = u; x != v; x = par[x]) {
          //assert(x != inf);
          cycle.push_back(x);
        }
        cycle.push_back(v);
        cycle_added[v].insert(u);
        ans.push_back(move(cycle));
      }
    }
  };

  dfs(0);
  //fore(u, 0, n) {
  //  //assert(vis[u]);
  //}

  return ans;
}

struct Cactus {
  ull head; // Id of head node
  vector<Cactus> children;
  vector<vector<Cactus>> cycles;
};

Cactus constructCactus(ull n, const vuu& edges) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<vu> cycles = findCycles(adj);
  vector<vu> cycles_per_node(n);
  fore(i, 0, cycles.size()) {
    for (ull u : cycles[i]) {
      cycles_per_node[u].push_back(i);
    }
  }

  vb vis(n, false);
  vb cycle_vis(cycles.size(), false);

  function<void(Cactus&)> dfs = [&](Cactus& t) {
    ull u = t.head;
    //assert(vis[u]);

    for (ull i : cycles_per_node[u]) if (!cycle_vis[i]) {
      cycle_vis[i] = true;
      t.cycles.push_back({});
      //assert(!cycles[i].empty());
      ull j = 0;
      while (cycles[i][j] != u) j++;
      //assert(cycles[i][j] == u);
      ull sz = cycles[i].size();
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        //assert(!vis[v]);
        vis[v] = true;
      }
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        t.cycles.back().push_back({v, {}, {}});
        dfs(t.cycles.back().back());
      }
    }

    for (ull v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        t.children.push_back({v, {}, {}});
        dfs(t.children.back());
      }
    }
  };

  Cactus ans = {0, {}, {}};
  vis[0] = true;
  dfs(ans);

  return ans;
}

enum OpType {
  JOIN, RECOLOR, CONNECT
};
struct Op {
  OpType ty;
  ull a, b, c0, c1;
};

vector<Op> solve(ull n, const vuu& edges) {

  Cactus cactus = constructCactus(n, edges);

  vector<Op> ans;

  auto join = [&](ull a, ull b) {
    assert(a < n && b < n);
    ans.push_back({JOIN, a, b, inf, inf});
  };
  auto recolor = [&](ull a, ull c0, ull c1) {
    assert(a < n);
    assert(c0 < 4 && c1 < 4);
    ans.push_back({RECOLOR, a, inf, c0, c1});
  };
  auto connect = [&](ull a, ull c0, ull c1) {
    assert(a < n);
    assert(c0 < 4 && c1 < 4);
    ans.push_back({CONNECT, a, inf, c0, c1});
  };

  /*
    0: Already constructed
    1: Points to join
  */
  function<void(Cactus&)> dfs = [&](Cactus& cactus) {
    if (cactus.children.empty() && cactus.cycles.empty()) {
      recolor(cactus.head, 0, 1);
      return;
    }

    // First construct subcactus not in a cycle
    for (Cactus& child : cactus.children) {
      dfs(child);
    }

    // Now construct subcactus in cycles
    for (vector<Cactus>& cycle : cactus.cycles) {
      assert(cycle.size() > 1);
      for (Cactus& child : cycle) {
        dfs(child);
      }

      recolor(cycle[0].head, 1, 2);
      fore(i, 1, cycle.size()) {
        join(cycle[i-1].head, cycle[i].head);
        connect(cycle[i].head, 2, 1);
        if (i > 1) {
          recolor(cycle[i-1].head, 2, 0);
        } else {
          recolor(cycle[0].head, 2, 3);
        }
        recolor(cycle[i].head, 1, 2);
      }
      recolor(cycle[0].head, 3, 1);
      recolor(cycle[0].head, 2, 1);
    }

    // Now connect every thing
    recolor(cactus.head, 0, 2);
    for (Cactus& child : cactus.children) {
      join(cactus.head, child.head);
    }
    for (vector<Cactus>& cycle : cactus.cycles) {
      join(cactus.head, cycle[0].head);
    }
    connect(cactus.head, 2, 1);
    recolor(cactus.head, 1, 0);
    recolor(cactus.head, 2, 1);
  };

  dfs(cactus);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("cactus.in", "r", stdin);
  freopen("cactus.out", "w", stdout);
#endif

  ull n, m;
  cin >> n >> m;
  vuu edges;
  fore(i, 0, m) {
    ull s;
    cin >> s;
    vu path(s);
    for (ull& u : path) {
      cin >> u;
      u--;
    }
    fore(i, 0, s - 1) {
      edges.push_back({path[i], path[i + 1]});
    }
  }

  vector<Op> ans = solve(n, edges);
  cout << ans.size() << '\n';
  for (Op op : ans) {
    if (op.ty == JOIN) {
      cout << "j " << op.a + 1 << ' ' << op.b + 1 << '\n';
    } else if (op.ty == RECOLOR) {
      cout << "r " << op.a + 1 << ' ' << op.c0 + 1 << ' ' << op.c1 + 1 << '\n';
    } else {
      cout << "c " << op.a + 1 << ' ' << op.c0 + 1 << ' ' << op.c1 + 1 << '\n';
    }
  }
}
