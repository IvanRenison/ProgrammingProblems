// https://codeforces.com/gym/106129/problem/H
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


optional<ll> solve(ll n, vii& edges, ll a, ll b) {
  vector<vi> adj(n);

  for (auto [u, v] : edges) {
    adj[u].push_back(v);
  }

  vector<bool> a_reach(n, false);
  a_reach[a] = true;
  vi s = {a};
  for (ll i = 0; i < s.size(); i++) {
    ll u = s[i];
    for (ll v : adj[u]) if (!a_reach[v]) {
      a_reach[v] = true;
      s.push_back(v);
    }
  }

  vector<bool> b_reach(n, false);
  b_reach[b] = true;
  s = {b};
  for (ll i = 0; i < s.size(); i++) {
    ll u = s[i];
    for (ll v : adj[u]) if (!b_reach[v]) {
      b_reach[v] = true;
      s.push_back(v);
    }
  }

  fore(i, 0, n) {
    if (a_reach[i] && b_reach[i]) {
      return i;
    }
  }

  return {};
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll n, m;
  cin >> n >> m;
  vii edges(m);
  for (auto& [x, y] : edges) {
    cin >> x >> y;
    x--, y--;
  }
  ll a, b;
  cin >> a >> b;
  a--, b--;

  auto ans = solve(n, edges, a, b);
  if (ans) {
    cout << "yes\n" << *ans + 1 << '\n';
  } else {
    cout << "no\n";
  }

}
