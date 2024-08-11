// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/K

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

vu path(const vector<vu>& adj, ull u, ull v) {
  ull n = adj.size();

  vu par(n, inf);

  vu s = {v};
  par[v] = v;

  while (!s.empty()) {
    ull x = s.back();
    s.pop_back();

    for (ull y : adj[x]) {
      if (par[y] == inf) {
        par[y] = x;
        s.push_back(y);
      }
    }
  }

  vu ans;
  while (u != v) {
    ans.push_back(u);
    assert(ans.size() <= 1e5);
    u = par[u];
  }
  ans.push_back(v);

  return ans;
}

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};


ll solve(const vu& Cs, const vuu& edges, ull M, ull P) {
  ull N = Cs.size();

  vector<vu> adj(N);
  for (auto [U, V] : edges) {
    adj[U].push_back(V), adj[V].push_back(U);
  }

  vu pathMP = path(adj, M, P);
  ull k = pathMP.size();

  function<ull(ull, ull, ull)> dfs = [&](ull u, ull p0, ull p1) -> ull {
    ull ans = 0;
    for (ull v : adj[u]) if (v != p0 && v != p1) {
      ans = max(ans, dfs(v, u, u));
    }
    ans += Cs[u];
    return ans;
  };

  vu path_points(k);
  path_points[0] = dfs(M, pathMP[1], inf);
  fore(i, 1, k - 1) {
    path_points[i] = dfs(pathMP[i], pathMP[i - 1], pathMP[i + 1]);
  }
  path_points[k - 1] = dfs(P, pathMP[k - 2], inf);

  vu M_points(k); // i -> Points for M goes to i by path and in i has to leave path
  M_points[0] = path_points[0];
  ull C_sum = Cs[pathMP[0]];
  fore(i, 1, k) {
    M_points[i] = C_sum + path_points[i];
    C_sum += Cs[pathMP[i]];
  }

  vu P_points(k);
  P_points[k - 1] = path_points[k - 1];
  C_sum = Cs[pathMP[k - 1]];
  for (ull i = k - 1; i--;) {
    P_points[i] = C_sum + path_points[i];
    C_sum += Cs[pathMP[i]];
  }

  RMQ M_points_rmq(M_points);
  RMQ P_points_rmq(P_points);

  vu Cs_sums(k + 1);
  fore(i, 0, k) {
    Cs_sums[i + 1] = Cs_sums[i] + Cs[pathMP[i]];
  }

  function<ll(ull, ull, bool)> rec = [&](ull i, ull j, bool turn) -> ll {
    if (turn) { // M
      ll ans = 0;
      { // Leave path at i
        ll M_p = path_points[i];
        ll P_p = P_points_rmq.query(i + 1, j + 1) - (Cs_sums[k] - Cs_sums[j + 1]);
        assert(P_p >= 0);
        ans = M_p - P_p;
      }
      if (i + 1 < j) {
        ans = max(ans, (ll)Cs[pathMP[i]] + rec(i + 1, j, !turn)); // Continue
      }
      return ans;
    } else { // P
      ll ans = 0;
      { // Leave path at j
        ll P_p = path_points[j];
        ll M_p = M_points_rmq.query(i, j) - Cs_sums[i];
        assert(M_p >= 0);
        ans = M_p - P_p;
      }
      if (i + 1 < j) {
        ans = min(ans, -(ll)Cs[pathMP[j]] + rec(i, j - 1, !turn)); // Continue
      }
      return ans;
    }
  };

  ll ans = rec(0, k - 1, true);

  return ans;
}


ll force(const vu& Cs, const vuu& edges, ull M, ull P) {
  ull N = Cs.size();

  vector<vu> adj(N);
  for (auto [U, V] : edges) {
    adj[U].push_back(V), adj[V].push_back(U);
  }

  auto has_move = [&](const vu& cs, ull u) -> bool {
    if (cs[u] > 0) {
      return true;
    }
    ull found = false;
    for (ull v : adj[u]) {
      if (cs[v] > 0) {
        found = true;
        break;
      }
    }
    return found;
  };

  function<ll(vu, ull, ull, bool)> rec = [&](vu cs, ull u, ull v, bool turn) -> ll {
    if (!has_move(cs, u) && !has_move(cs, v)) {
      return 0;
    }
    if (turn) { // M
      vu ncs = cs;
      ncs[u] = 0;

      ll ans = -inf;
      for (ull U : adj[u]) if (U != v && cs[U] > 0) {
        ans = max(ans, rec(ncs, U, v, !turn));
      }
      if (ans == -inf) {
        ans = rec(ncs, u, v, !turn);
      }
      ans += cs[u];
      return ans;
    } else { // P
      vu ncs = cs;
      ncs[v] = 0;

      ll ans = inf;
      for (ull V : adj[v]) if (V != u && cs[V] > 0) {
        ans = min(ans, rec(ncs, u, V, !turn));
      }
      if (ans == inf) {
        ans = rec(ncs, u, v, !turn);
      }
      ans -= cs[v];
      return ans;
    }
  };

  ull ans = rec(Cs, M, P, true);

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
		if ( nodeCount.find(i) == nodeCount.end()) leaves.insert (i);
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
  ull N, M, P;
  cin >> N >> M >> P;
  M--, P--;
  vu Cs(N);
  for (ull& C : Cs) {
    cin >> C;
  }
  vuu edges(N - 1);
  for (auto& [U, V] : edges) {
    cin >> U >> V;
    U--, V--;
  }

  ll ans = solve(Cs, edges, M, P);
  cout << ans << '\n';
#else
  fore(_, 0, 1000) {
    ull N = rand() % 8 + 2;
    ull M = rand() % N, P = rand() % N;
    if (M == P) {
      P = (P + 1) % N;
    }
    vu Cs(N);
    for (ull& C : Cs) {
      C = rand() % 10 + 1;
    }
    vuu edges = genRandomTree(N);

    ll ans = solve(Cs, edges, M, P);
    ll ansf = force(Cs, edges, M, P);
    if (ans != ansf) {
      cerr << "FAIL" << '\n';
      cerr << N << ' ' << M + 1 << ' ' << P + 1 << '\n';
      for (ull C : Cs) {
        cerr << C << ' ';
      }
      cerr << '\n';
      for (auto [U, V] : edges) {
        cerr << U + 1 << ' ' << V + 1 << '\n';
      }
      cerr << "Found: " << ans << '\n';
      cerr << "Expected: " << ansf << endl;
      break;
    }
  }
#endif
}
