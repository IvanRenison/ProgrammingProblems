// https://codeforces.com/gym/100851
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef long double ld;

const ll inf = 1ll << 60;

struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  ll find(ll x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

ll sq(ll x) {
  return x * x;
}

ld dist(ii p0, ii p1) {
  auto [x0, y0] = p0;
  auto [x1, y1] = p1;
  return sqrtl((ld)(sq(x0 - x1) + sq(y0 - y1)));
}

pair<ld, ld> solve(ll ww, vii& xys) {
  ll n = xys.size();

  if (n == 0) {
    return {(ld)ww / 2.l, 0.l};
  }

  vector<tuple<ld, ll, ll>> edges;
  fore(u, 0, n) {
    fore(v, 0, u) {
      edges.push_back({dist(xys[u], xys[v]), v + 1, u + 1});
    }
    edges.push_back({xys[u].first, 0, u + 1});
    edges.push_back({ww - xys[u].first, u + 1, n + 1});
  }

  sort(ALL(edges));

  vector<tuple<ld, ll, ll>> tree_edges;

  UF uf(n + 2);
  for (auto [w, u, v] : edges) {
    if (uf.join(u, v)) {
      tree_edges.push_back({w, u, v});
    }
  }

  vector<vector<pair<ll, ld>>> adj(n + 2);
  for (auto [w, u, v] : tree_edges) {
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  }

  vector<ld> dist0(n + 2, inf);
  {
    dist0[0] = 0;
    vi s = {0};
    while (!s.empty()) {
      ll u = s.back();
      s.pop_back();

      for (auto [v, w] : adj[u]) {
        if (dist0[v] == inf) {
          dist0[v] = max(dist0[u], w);
          s.push_back(v);
        }
      }
    }
  }
  vector<ld> dist1(n + 2, inf);
  {
    dist1[n + 1] = 0;
    vi s = {n + 1};
    while (!s.empty()) {
      ll u = s.back();
      s.pop_back();

      for (auto [v, w] : adj[u]) {
        if (dist1[v] == inf) {
          dist1[v] = max(dist1[u], w);
          s.push_back(v);
        }
      }
    }
  }

  ld ans_val = 1e30, ans_x, ans_y;

  fore(u, 0, n) {
    auto [xu, yu] = xys[u];
    ld du = dist0[u + 1];
    fore(v, 0, n) if (v != u) {
      auto [xv, yv] = xys[v];
      ld dv = (ld)dist1[v + 1];

      ld d = dist(xys[u], xys[v]);
      ld this_ans = max({du, dv, d / 2.l});

      if (this_ans < ans_val) {
        ans_val = this_ans;
        ans_x = (ld)(xu + xv) / 2.l;
        ans_y = (ld)(yu + yv) / 2.l;
      }
    }

    ld this_ans = max(du, (ld)(ww - xu) / 2.l);
    if (this_ans < ans_val) {
      ans_val = this_ans;
      ans_x = (ld)(ww + xu) / 2.l;
      ans_y = yu;
    }

    du = dist1[u + 1];
    this_ans = max(du, (ld)xu / 2.l);
    if (this_ans < ans_val) {
      ans_val = this_ans;
      ans_x = (ld)xu / 2.l;
      ans_y = yu;
    }
  }

  return {ans_x, ans_y};
}


int main(){
    ios::sync_with_stdio(0);cin.tie(0);
#ifdef ONLINE_JUDGE
    freopen("froggy.in", "r",stdin);
    freopen("froggy.out","w",stdout);
#endif

  ll w, n;
  cin >> w >> n;
  vii xys(n);
  for (auto& [x, y] : xys) {
    cin >> x >> y;
  }

  auto [x, y] = solve(w, xys);
  cout << setprecision(10);
  cout << x << ' ' << y << '\n';

}