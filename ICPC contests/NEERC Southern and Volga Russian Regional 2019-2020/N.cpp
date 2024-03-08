// https://codeforces.com/contest/1250/problem/N
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

viii solve(const vii& wires) {
  ll n = wires.size();

  set<ll> points_s;
  map<ll, vii> adj;

  fore(i, 0, n) {
    auto [x, y] = wires[i];
    points_s.insert(x), points_s.insert(y);
    adj[x].push_back({y, i}), adj[y].push_back({x, i});
  }

  vi points = vi(ALL(points_s));

  ll a = points[0];

  set<ll> vis;

  viii ans;

  for (ll u : points) {
    if (!vis.count(u)) {
      vi s = {u};
      vis.insert(u);

      ll last_i = -1, last_w = -1;

      while (!s.empty()) {
        ll v = s.back();
        s.pop_back();

        for (auto [w, i] : adj[v]) {
          if (!vis.count(w)) {
            vis.insert(w);
            s.push_back(w);
            last_i = i;
            last_w = w;
          }
        }
      }

      assert(last_i != -1);

      if (u != a) {
        ans.push_back({last_i, last_w, a});
      }
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vii wires(n);
    for (auto& [x, y] : wires) {
      cin >> x >> y;
      x--, y--;
    }

    viii ans = solve(wires);

    cout << ans.size() << '\n';
    for (auto [w, a, b] : ans) {
      cout << w + 1 << ' ' << a + 1 << ' ' << b + 1 << '\n';
    }
  }

  return 0;
}