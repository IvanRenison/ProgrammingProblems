// https://codeforces.com/gym/104736/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define sz(x) (x).size()

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
    for (ll pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      fore(j,0,sz(jmp[k]))
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
  vi time, path, ret, depth;
  RMQ<ll> rmq;

  LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vi>& C, ll v, ll par) {
    if (par != -1) {
      depth[v] = depth[par] + 1;
    }
    time[v] = T++;
    for (ll y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }

  ll lca(ll a, ll b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }

  ll dist(ll a, ll b) {
    return depth[a] + depth[b] - 2*depth[lca(a,b)];
  }
};

// centroid of a tree is a node that is at the middle of the Nodes
// It has trees of size at most n/2 at each side
struct CentroidTree {
  vector<vi> g;
  ll n;
  vb tk;
  vi fat; // father in centroid decomposition, -1 for total father
  vi szt; // size of subtree
  CentroidTree(vector<vi> g) : g(g), n(g.size()), tk(n, false), fat(n), szt(n)  {
    cdfs();
  }
  ll calcsz(ll x, ll f){
    szt[x]=1;
    for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
    return szt[x];
  }
  void cdfs(ll x=0, ll f=-1, ll sz=-1){ // O(nlogn)
    if(sz<0)sz=calcsz(x,-1);
    for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
      szt[x]=0;cdfs(y,f,sz);return;
    }
    tk[x]=true;fat[x]=f;
    for(auto y:g[x])if(!tk[y])cdfs(y,x);
  }
};


vu solve(ull N, const vuu& edges) {

  vector<vi> adj(N);

  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  CentroidTree ct(adj);
  LCA lca(adj);

  // cerr << "CentroidTree: \n";
  // fore(i, 0, ct.fat.size()) {
  //   cerr << i << ' ' << ct.fat[i] << '\n';
  // }

  vu subtree_anss(N, inf);
  vu subtree_dist(N, inf);

  vu ans(N);

  for (ull i = N - 1; i < N; i--) {
    if (i == N - 1) {
      ans[i] = i;
    } else {
      ull v = inf;
      ull v_dist = inf;

      for (ll j = i; j != -1; j = ct.fat[j]) {
        ull u = subtree_anss[j];
        if (u != inf) {
          ull u_dist = lca.dist(i, u);

          if (u_dist < v_dist || (u_dist == v_dist && u < v)) {
            v = u, v_dist = u_dist;
          }
        }
      }

      assert(v != inf);

      ans[i] = v;
    }

    for (ll j = i; j != -1; j = ct.fat[j]) {
      ull this_dist = lca.dist(i, j);
      if (subtree_anss[j] == inf || this_dist < subtree_dist[j] || (this_dist == subtree_dist[j] && i < subtree_anss[j])) {
        subtree_anss[j] = i;
        subtree_dist[j] = this_dist;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vuu edges(N - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(N, edges);
  for (ull u : ans) {
    cout << u + 1 << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
