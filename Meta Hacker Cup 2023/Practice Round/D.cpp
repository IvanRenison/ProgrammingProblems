// https://www.facebook.com/codingcompetitions/hacker-cup/2023/practice-round/problems/D?source=codeforces

#include <bits/stdc++.h>

using namespace std;

/* typedef __uint128_t ull;
typedef __int128_t ll; */
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define sz(x) (x.size())
#define all(x) x.begin(), x.end()

istream& operator>>(istream& is, __uint128_t& value) {
  unsigned long long x;
  is >> x;
  value = x;
  return is;
}

ostream& operator<<(ostream& os, __uint128_t value) {
  if (value == 0) {
    os << '0';
  } else {
    while (value > 0) {
      os << (int)(value % 10);
      value /= 10;
    }
  }
  return os;
}

istream& operator>>(istream& is, __int128_t& value) {
  unsigned long long x;
  is >> x;
  value = x;
  return is;
}

ostream& operator<<(ostream& os, __int128_t value) {
  if (value == 0) {
    os << '0';
  } else {
    if (value < 0) {
      os << '-';
      value = -value;
    }
    while (value > 0) {
      os << (int)(value % 10);
      value /= 10;
    }
  }
  return os;
}

constexpr ll inf = 1ull << 60;

typedef ull Vertex;
typedef pair<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vi> adj;

  Graph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};

pair<ull, vector<Edge>> readGraph() {
  ull n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  return {n, edges};
}

struct Biconnected {
  vi num, st;
  vector<vector<ii>> ed;
  ll Time;
  Graph g;
  vector<bool> bridges;
  Biconnected(Graph g) : g(g), Time(0), bridges(g.m, false) {
    ll N = g.n;
    ll eid = 0; ed.resize(N);
    for (auto [a, b] : g.edges) {
      ed[a].emplace_back(b, eid);
      ed[b].emplace_back(a, eid++);
    }
  }
  ll dfs(ll at, ll par) {
    assert(at < g.n);
    ll me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      assert(y < g.n);
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        ll si = sz(st);
        ll up = dfs(y, e);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else { /* e is a bridge */
          bridges[e] = true;
        }
      }
    }
    return top;
  }

  void bicomps() {
    num.assign(sz(ed), 0);
    fore(i,0,sz(ed)) if (!num[i]) dfs(i, -1);
  }

};

tuple<Graph, vu, vector<bool>> compressBCC(const Graph& g) {
  Biconnected bcc(g);
  bcc.bicomps();

  //assert(false);

  ull n = 0;
  vector<bool> isOdd;

  vu comp(g.n, inf);

  vector<bool> colors(g.n);

  fore(u, 0, g.n) {
    if (comp[u] == inf) {
      isOdd.push_back(false);
      comp[u] = n;
      colors[u] = false;

      vu s = {u};

      while (!s.empty()) {
        ull v = s.back();
        s.pop_back();

        for (auto [w, eid] : bcc.ed[v]) {
          if (!bcc.bridges[eid]) {
            if (comp[w] == inf) {
              comp[w] = n;
              colors[w] = !colors[v];
              s.push_back(w);
            } else if (colors[w] == colors[v]) {
              isOdd[n] = true;
            }
          }
        }
      }

      n++;
    }
  }

  vuu edges;
  fore(i, 0, g.m) {
    if (bcc.bridges[i]) {
      auto [u, v] = g.edges[i];
      if (comp[u] != comp[v]) {
        edges.emplace_back(comp[u], comp[v]);
      }
    }
  }

  return {Graph(n, edges), comp, isOdd};
}

struct Node {
	typedef ll T; // data type
	struct L { ll mset, madd; }; // lazy type
	const T tneut = -inf;     // neutral elements
	const L lneut = {inf, 0};
	T f (T a, T b) { return max(a, b); } // (any associative fn)
	T apply (T a, L b) {
		return b.mset != inf ? b.mset + b.madd : a + b.madd;
	} // Apply lazy
	L comb(L a, L b) {
		if (b.mset != inf) return b;
		return {a.mset, a.madd + b.madd};
	} // Combine lazy

	Node *l = 0, *r = 0;
	ll lo, hi; T val = tneut; L lazy = lneut;
	Node(ll lo,ll hi):lo(lo),hi(hi){}//Large interval of tneut
	Node(vector<T>& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	T query(ll L, ll R) {
		if (R <= lo || hi <= L) return tneut;
		if (L <= lo && hi <= R) return apply(val, lazy);
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void upd(ll Le, ll Ri, L x) {
		if (Ri <= lo || hi <= Le) return;
		if (Le <= lo && hi <= Ri) lazy = comb(lazy, x);
		else {
			push(), l->upd(Le, Ri, x), r->upd(Le, Ri, x);
			val = f(l->query(lo, hi), r->query(lo, hi));
		}
	}
	void set(ll L, ll R, ll x) { upd(L, R, {x, 0}); }
	void add(ll L, ll R, ll x) { upd(L, R, {inf, x}); }
	void push() {
		if (!l) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(lo, mid), r = new Node(mid, hi);
		}
		l->lazy = comb(l->lazy, lazy);
		r->lazy = comb(r->lazy, lazy);
		lazy = lneut;
		val = f(l->query(lo, hi), r->query(lo, hi));
	}
};


template <bool VALS_EDGES> struct HLD {
	ll N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(new Node(0, N)){ dfsSz(0); dfsHld(0); }
	void dfsSz(ll v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (ll& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(ll v) {
		pos[v] = tim++;
		for (ll u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(ll u, ll v, B op) {
    assert(u < N);
    assert(v < N);
    assert(rt[v] < N);
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(ll u, ll v, ll val) {
		process(u, v, [&](ll l, ll r) { tree->add(l, r, val); });
	}
	ll queryPath(ll u, ll v) { // Modify depending on problem
		ll res = -1e9;
		process(u, v, [&](ll l, ll r) {
				res = max(res, tree->query(l, r));
		});
		return res;
	}
	ll querySubtree(ll v) { // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

ll solve1(const Graph& g, const vii& querys) {
  ull Q = querys.size();

  auto [g2, comp, isOdd] = compressBCC(g);

  HLD<false> hld(g2.adj);

  {
    queue<ull> q;
    vi dist(g2.n, -1);

    fore(u, 0, g2.n) {
      if(isOdd[u]) {
        q.push(u);
        dist[u] = 0;
      }
    }

    if (q.empty()) {
      return -Q;
    }

    while(!q.empty()) {
      ull u = q.front();
      q.pop();

      for(auto v : g2.adj[u]) {
        if(dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }

    fore(u, 0, g2.n) {
      hld.tree->set(hld.pos[u], hld.pos[u] + 1, -dist[u]);
    }
  }


  ll ans = 0;
  for(auto [u, v] : querys) {
    ans += -hld.queryPath(comp[u], comp[v]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    auto [n, edges] = readGraph();
    Graph g(n, edges);
    ull Q;
    cin >> Q;
    vii querys(Q);
    for(auto &[u, v] : querys) {
      cin >> u >> v;
      u--, v--;
    }

    auto ans = solve1(g, querys);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
