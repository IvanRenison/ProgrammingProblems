// https://codeforces.com/gym/106054/problem/E
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

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
    assert(a < b);
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  ll T = 0;
  vi time, path, ret;
  RMQ<ll> rmq;

  LCA(vector<vi>& C) : time(SZ(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vi>& C, ll v, ll par) {
    time[v] = T++;
    for (ll y : C[v]) if (y != par) {
      path.pb(v), ret.pb(time[v]);
      dfs(C, y, v);
    }
  }

  ll lca(ll a, ll b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
};

ii solve(vi& Ts, vii& edges) {
  ll N = Ts.size() + 1;

  vector<vi> adj(N);
  for (auto [U, V] : edges) {
    adj[U].push_back(V), adj[V].push_back(U);
  }

  LCA lca(adj);

  vi depth(N);
  vector<vi> Pos;
  vector<vi> this_Pos(N);
  vector<bool> vis(N, false);

  auto dfs = [&](ll u, ll p, ll d, auto&& dfs) -> void {
    this_Pos[d].push_back(u);
    vis[d] = true;
    depth[u] = d;

    for (ll v : adj[u]) if (v != p) {
      dfs(v, u, d + 1, dfs);
    }
  };

  for (ll r : adj[0]) {
    dfs(r, 0, 0, dfs);

    fore(i, 0, N) {
      if (!vis[i]) {
        break;
      } else {
        Pos.push_back(this_Pos[i]);
        this_Pos[i] = {};
        vis[i] = false;
      }
    }

  }

  ll ans = 0, turnos = 0;
  for (vi& vs : Pos) {
    ll this_ans = 0;
    for (ll v : vs) {
      this_ans += Ts[v - 1];
    }

    vi vs2;
    for (ll v : vs) {
      if (Ts[v - 1] != 0) {
        vs2.push_back(v);
      }
    }
    if (vs2.empty()) {
      continue;
    }
    ll a = vs2[0];
    fore(i, 1, vs2.size()) {
      a = lca.lca(a, vs2[i]);
    }
    assert(a != 0);
    ll this_turnos = depth[vs2[0]] - depth[a] + 1;

    if (this_ans > ans || (this_ans == ans && this_turnos < turnos)) {
      ans = this_ans;
      turnos = this_turnos;
    }

  }

  return {ans, turnos};
}

ii force(vi Ts, vii edges) {
  ll N = Ts.size() + 1;

  vector<vi> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vi ps(N, -1);

  vi s = {0};
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();

    for (ll v : adj[u]) if (v != ps[u]) {
      ps[v] = u;
      s.push_back(v);
    }
  }


  ll ans = 0, turnos = 0;

  fore(t, 0, N) {
    ll this_ans = 0;
    fore(i, 1, N) {
      this_ans = max(this_ans, Ts[i - 1]);
    }

    if (this_ans > ans) {
      ans = this_ans;
      turnos = t + 1;
    }

    vi new_Ts(N - 1);
    fore(i, 1, N) {
      if (ps[i] != 0) {
        new_Ts[ps[i] - 1] += Ts[i - 1];
      }
    }

    Ts = new_Ts;
  }

  return {ans, turnos};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  ll N;
  cin >> N;
  vi Ts(N - 1);
  for (ll& T : Ts) {
    cin >> T;
  }
  vii edges(N - 1);
  for (auto& [U, V] : edges) {
    cin >> U >> V;
    U--, V--;
  }

  auto [ans, turnos] = solve(Ts, edges);
  cout << ans << ' ' << turnos << '\n';

#else
  fore(_, 0, 10000) {
    ll N = rand() % 10 + 2;

    vi Ts(N - 1);
    for (ll& T : Ts) {
      T = rand() % 10;
    }

    vii edges(N - 1);
    fore(i, 1, N) {
      edges[i - 1] = {rand() % i, i};
    }

    ii ans = solve(Ts, edges);
    ii ansf = force(Ts, edges);

    if (ans != ansf) {
      cout << N << '\n';
      for (ll T : Ts) {
        cout << T << ' ';
      }
      cout << '\n';
      for (auto [u, v] : edges) {
        cout << u + 1 << ' ' << v + 1 << '\n';
      }

      cout << "ans: " << ans.first << ' ' << ans.second << '\n';
      cout << "ansf: " << ansf.first << ' ' << ansf.second << '\n';
      return 1;
    }
  }
#endif
}