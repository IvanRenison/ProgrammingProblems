// https://codeforces.com/gym/105925/problem/G

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)((x).size()))
#define DBG(x) //cerr << #x << " = " << x << endl
#define pb push_back

const ull inf = 1ull << 60;
const ld eps = 1e-7;



// Devuelve todos los caminos, o vacio si hay alguno de largo más de 5
vector<vu> get_paths(ll n, vuu& edges, vuu& paths) {
    vector<vector<ull>> g(n);
    for (auto& [u, v] : edges) {
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<vector<ull>> res(SZ(paths));
    fore(i, 0, SZ(paths)) {
        auto [X, Y] = paths[i];
        vector<ll> prev(n, -1);
        queue<ull> q;
        q.push(X);
        prev[X] = X;
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            if (v == Y) break;
            for (auto& u : g[v]) {
                if (prev[u] == -1) {
                    prev[u] = v;
                    q.push(u);
                }
            }
        }
        if (prev[Y] == -1) {
            return {};
        }
        vector<ull> path;
        for (ull v = Y; v != X; v = prev[v]) {
            path.pb(v);
        }
        path.pb(X);
        reverse(ALL(path));
        res[i] = path;
        if (path.size() > 5) {
            return {};
        }
    }
    return res;
}


/** Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity O(VE\log U)$ where U = \max |\text{cap}|$.
 * O(\min(E^{1/2}, V^{2/3})E)$ if U = 1$; O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */

struct Dinic {
    struct Edge {
        ll to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }  // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(ll a, ll b, ll c, ll rcap = 0) {
        //cerr << "Adding edge " << a << " " << b << " with capacity " << c << endl;
        adj[a].pb({b, SZ(adj[b]), c, c});
        adj[b].pb({a, SZ(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(ll v, ll t, ll f) {
        if (v == t || !f) return f;
        for (ll& i = ptr[v]; i < SZ(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(ll s, ll t) {
        ll flow = 0;
        q[0] = s;
        fore(L, 0, 31) do {  // 'll L=30' maybe faster for random data
            lvl = ptr = vi(SZ(q));
            ll qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                ll v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        }
        while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(ll a) { return lvl[a] != 0; }
};

template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
            jmp.emplace_back(SZ(V) - pw * 2 + 1);
            fore(j, 0, SZ(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(ll a, ll b) {
        assert(a < b);  // or return inf if a == b
        ll dep = 63 - __builtin_clzll(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    ll T = 0;
    vi time, path, ret, depth;
    RMQ<ll> rmq;

    LCA(vector<vi>& C) : time(SZ(C)), depth(SZ(C)), rmq((depth[0] = 0, dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi>& C, ll v, ll par) {
        time[v] = T++;
        for (ll y : C[v])
            if (y != par) {
                path.pb(v), ret.pb(time[v]);
                depth[y] = depth[v] + 1;
                dfs(C, y, v);
            }
    }

    ll lca(ll a, ll b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    ll dist(ll a, ll b) { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
};



vector<vector<ull>> posibilidades(ull l){
    vector<vector<ull>> ans;

    auto f = [&](int estoy, vector<ull> tengo, auto&&f)->void{
        if(SZ(tengo) == l){
            ans.pb(tengo);
            return;
        }
        if(5-estoy+SZ(tengo) < l)return;
        f(estoy+1,tengo,f);
        tengo.push_back(estoy);
        f(estoy+1,tengo,f);
    };
    f(0,{},f);
    return ans;
}



optional<vu> solve(vu cnts, vector<vu>& vals, vuu& edges, vuu& pathsEnds) {
  ull N = vals.size(), P = pathsEnds.size();

  vu vals_bits(N);
  fore(i, 0, N) {
    for (auto& v : vals[i]) {
      vals_bits[i] |= (1ull << v);
    }
  }

  vu super_nodes(1 << 5);
  for (ull x : vals_bits) {
    super_nodes[x]++;
  }

  vector<vu> paths = get_paths(N, edges, pathsEnds);

  if (paths.empty()) {
    return {};
  }

  vu vals_bits_copy = vals_bits;

  // Solve for a possibility of numbers for the paths
  auto solve_pos = [&](vector<vu> pos) -> optional<vu> {
    vu this_super_nodes = super_nodes;
    // Actualizar super_nodes
    fore(p, 0, P) {
      fore(i, 0, paths[p].size()) {
        ull u = paths[p][i];
        ull old_x = vals_bits_copy[u];
        ull new_x = old_x & (1 << pos[p][i]);
        vals_bits_copy[u] = new_x;

        this_super_nodes[old_x]--;
        this_super_nodes[new_x]++;
      }
    }

    if (this_super_nodes[0] != 0 ||
        this_super_nodes[1 << 0] > cnts[0] ||
        this_super_nodes[1 << 1] > cnts[1] ||
        this_super_nodes[1 << 2] > cnts[2] ||
        this_super_nodes[1 << 3] > cnts[3] ||
        this_super_nodes[1 << 4] > cnts[4]
    ) {
      fore(p, 0, P) {
        fore(i, 0, paths[p].size()) {
          ull u = paths[p][i];
          vals_bits_copy[u] = vals_bits[u];
        }
      }
      return {};
    }

    Dinic dinic(1 + 5 + (1 << 5) + 1);
    fore(i, 0, 5) {
      dinic.addEdge(0, 1 + i, cnts[i]);
    }
    fore(x, 0, (1 << 5)) {
      fore(i, 0, 5) {
        if (x & (1ull << i)) {
          dinic.addEdge(1 + i, 1 + 5 + x, inf);
        }
      }
      dinic.addEdge(1 + 5 + x, 1 + 5 + (1 << 5), this_super_nodes[x]);
    }
    ll flow = dinic.calc(0, 1 + 5 + (1 << 5));

    if (flow < N) {
      fore(p, 0, P) {
        fore(i, 0, paths[p].size()) {
          ull u = paths[p][i];
          vals_bits_copy[u] = vals_bits[u];
        }
      }
      return {};
    }

    vu new_vals_bits = vals_bits;
    fore(p, 0, P) {
      fore(i, 0, paths[p].size()) {
        ull u = paths[p][i];
        ull new_x = 1 << pos[p][i];

        new_vals_bits[u] &= new_x;
      }
    }

    vector<vu> this_super_nodes_elems(1 << 5);
    fore(i, 0, N) {
      ull x = new_vals_bits[i];
      this_super_nodes_elems[x].push_back(i);
    }

    vu ans(N);
    fore(i, 0, 5) {
      for (auto& e : dinic.adj[1 + i]) {
        ll f = e.flow();
        ull x = e.to;

        while (f > 0) {
          assert(!this_super_nodes_elems[x - 6].empty());
          ull j = this_super_nodes_elems[x - 6].back();
          ans[j] = i;
          this_super_nodes_elems[x - 6].pop_back();

          f--;
        }
      }
    }


    return ans;
  };




  vector<vector<vu>> posi(P);
  fore(i, 0, P) {
    posi[i] = posibilidades(paths[i].size());
  }


  if (P == 5) {
    for (vu x0 : posi[0]) for (vu x1 : posi[1]) for (vu x2 : posi[2]) for (vu x3 : posi[3]) for (vu x4 : posi[4]) {
      auto ans = solve_pos({x0, x1, x2, x3, x4});
      if (ans.has_value()) {
        return ans;
      }
    }
  }

  if (P == 4) {
    for (vu x0 : posi[0]) for (vu x1 : posi[1]) for (vu x2 : posi[2]) for (vu x3 : posi[3]) {
      auto ans = solve_pos({x0, x1, x2, x3});
      if (ans.has_value()) {
        return ans;
      }
    }
  }

  if (P == 3) {
    for (vu x0 : posi[0]) for (vu x1 : posi[1]) for (vu x2 : posi[2]) {
      auto ans = solve_pos({x0, x1, x2});
      if (ans.has_value()) {
        return ans;
      }
    }
  }

  if (P == 2) {
    for (vu x0 : posi[0]) for (vu x1 : posi[1]) {
      auto ans = solve_pos({x0, x1});
      if (ans.has_value()) {
        return ans;
      }
    }
  }

  if (P == 1) {
    for (vu x0 : posi[0]) {
      auto ans = solve_pos({x0});
      if (ans.has_value()) {
        return ans;
      }
    }
  }



  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vu cnts(5);
  fore(i, 0, 5) {
    cin >> cnts[i];
  }
  vector<vu> vals(N);
  fore(i, 0, N) {
    ull M;
    cin >> M;
    vals[i].resize(M);
    fore(j, 0, M) {
      cin >> vals[i][j];
      vals[i][j]--;
    }
  }
  vuu edges(N - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--; v--;
  }
  ull P;
  cin >> P;
  vuu paths(P);
  for (auto& [X, Y] : paths) {
    cin >> X >> Y;
    X--; Y--;
  }

  auto ans = solve(cnts, vals, edges, paths);
  if (ans) {
    for (auto& x : *ans) {
      cout << x + 1 << " ";
    }
    cout << "\n";
  } else {
    cout << "-1\n";
  }

}


