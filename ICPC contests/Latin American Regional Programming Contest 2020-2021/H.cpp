#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<ll> vi;

struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() {
      return max(oc - c, 0LL);
    }
  }; vi lvl, ptr, q;
  vector<vector<Edge>> adj;

  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}

  void addEdge(int a, int b, ll c, ll rcap = 0) {
    adj[a].pb({b, SZ(adj[b]), c, c});
    adj[b].pb({a, SZ(adj[a]) - 1, rcap, rcap});
  }

  ll dfs(int v, int t, ll f) {
    if (v == t || !f)
      return f;
    for (ll& i = ptr[v]; i < SZ(adj[v]); i++) {
      Edge &e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }

  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    fore(L, 0, 31) do {
      lvl = ptr = vi(SZ(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
};

int main(){
  FIN;

  ll n;
  cin >> n;

  vector<map<ll, ll>> g(n);

  fore(i, 0, n) {
    string idk;
    cin >> idk;

    if (idk == "*") {
      ll to;
      cin >> to;
      to--;
      g[i][to] = 1e15;
    } else {
      ll cnt = stoi(idk);
      fore(j, 0, cnt) {
        ll to; cin >> to;
        to--;
        g[i][to]++;
      }
    }
  }

  ll s = 0, t = n;

  Dinic d(n + 1);
  fore(i, 0, n) {
    for( auto [no, v] : g[i]) {
      d.addEdge(i, no == 0 ? t : no, v);
    }
  }

  ll f = d.calc(s, t);

  if (f + 1 > 1e12) {
    cout << "*\n";
  } else {
    cout << f+ 1 << '\n';
  }

  return 0;
}