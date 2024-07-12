// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

/** Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph g$ should be a list
 * of neighbors of the left partition, and btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. btoa[i]$ will be the match for vertex i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vi btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(\sqrt{V}E)
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
bool dfs(ll a, ll L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (ll b : g[a]) if (B[b] == L + 1) {
    B[b] = 0;
    if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
      return btoa[b] = a, 1;
  }
  return 0;
}

ll hopcroftKarp(vector<vi>& g, vi& btoa) {
  ll res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(ALL(A), 0);
    fill(ALL(B), 0);
    cur.clear();
    for (ll a : btoa) if(a != -1) A[a] = -1;
    fore(a,0,SZ(g)) if(A[a] == 0) cur.pb(a);
    for (ll lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (ll a : cur) for (ll b : g[a]) {
        if (btoa[b] == -1) {
          B[b] = lay;
          islast = 1;
        }
        else if (btoa[b] != a && !B[b]) {
          B[b] = lay;
          next.pb(btoa[b]);
        }
      }
      if (islast) break;
      if (next.empty()) return res;
      for (ll a : next) A[a] = lay;
      cur.swap(next);
    }
    fore(a,0,SZ(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}


/** Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
vi cover(vector<vi>& g, ll n, ll m) {
  vi match(m, -1);
  ll res = hopcroftKarp(g, match);
  vector<bool> lfound(n, true), seen(m);
  for (ll it : match) if (it != -1) lfound[it] = false;
  vi q, cover;
  fore(i,0,n) if (lfound[i]) q.pb(i);
  while (!q.empty()) {
    ll i = q.back(); q.pop_back();
    lfound[i] = 1;
    for (ll e : g[i]) if (!seen[e] && match[e] != -1) {
      seen[e] = true;
      q.pb(match[e]);
    }
  }
  fore(i,0,n) if (!lfound[i]) cover.pb(i);
  fore(i,0,m) if (seen[i]) cover.pb(n+i);
  assert(SZ(cover) == res);
  return cover;
}

// Returns edges indexes
vector<pair<bool, ll>> critical(ll n0, ll n1, const vii& edges) {
  ll m = edges.size();

  vector<vi> left_adj(n0);
  map<ii, ll> idx;
  fore(e, 0, m) {
    auto [x, y] = edges[e];
    left_adj[x].push_back(y);
    idx[{x, y}] = e;
  }

  vi btoa(n1, -1);

  ll tam = hopcroftKarp(left_adj, btoa);
  vi cov = cover(left_adj, n0, n1);

  vi atob(n0, -1);
  fore(i, 0, n1) {
    if (btoa[i] != -1) {
      atob[btoa[i]] = i;
    }
  }

  vector<pair<bool, ll>> ans(tam);
  fore(i, 0, tam) {
    ll u = cov[i];
    if (u < n0) {
      ll e = idx[{u, atob[u]}];
      ans[i] = {false, e};
    } else {
      ll e = idx[{btoa[u - n0], u - n0}];
      ans[i] = {true, e};
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n0, n1, m, q;
  cin >> n0 >> n1 >> m >> q;

  vii edges(m);
  for (auto& [x, y] : edges) {
    cin >> x >> y;
    x--, y--;
  }

  vector<pair<bool, ll>> cri = critical(n0, n1, edges);
  ll tam = cri.size();
  ll sum = 0;
  for (auto [_, e] : cri) {
    sum += e + 1;
  }

  ll i = 0;
  while (q--) {
    ll ty;
    cin >> ty;
    if (ty == 1) {
      cout << "1\n";
      auto [rb, re] = cri[i];
      if (rb) {
        cout << -edges[re].second - 1 << '\n';
      } else {
        cout << edges[re].first + 1 << '\n';
      }
      sum -= re + 1;
      cout << sum << endl;
      i++;
    } else {
      cout << tam - i << '\n';
      fore(j, i, tam) {
        cout << cri[j].second + 1 << ' ';
      }
      cout << endl;
    }
  }

}
