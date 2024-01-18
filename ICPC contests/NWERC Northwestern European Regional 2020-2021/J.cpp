// https://codeforces.com/gym/103049/problem/J
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;


tuple<vi, vi, vi> solve(ll n, const vii& edges) {

  vector<vi> adj(n);

  for(auto [a, b] : edges) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  set<ll> A, B;
  fore(i, 1, n) {
    A.insert(i);
  }

  vii stack = {{0, 0}};
  vector<bool> vis(n, false);
  vis[0] = true;

  while(A.size() != B.size()) {
    assert(!stack.empty());
    auto& [u, i] = stack.back();
    if (i >= adj[u].size()) {
      stack.pop_back();
      B.insert(u);
    } else {
      ll v = adj[u][i];
      i++;
      if (!vis[v]) {
        vis[v] = true;
        stack.push_back({v, 0});
        A.erase(v);
      }
    }
  }

  vi path, set0, set1;
  for(auto [u, _] : stack) {
    path.push_back(u);
  }
  for(ll u : A) {
    set0.push_back(u);
  }
  for(ll u : B) {
    set1.push_back(u);
  }

  return {path, set0, set1};
}

int main(){FIN;

  ll n, m;
  cin >> n >> m;
  vii edges(m);
  for(auto& [a, b] : edges) {
    cin >> a >> b;
    a--, b--;
  }

  auto [mom, kid0, kid1] = solve(n, edges);
  cout << mom.size() << ' ' << kid0.size() << '\n';
  for(ll u : mom) {
    cout << u + 1 << ' ';
  }
  cout << '\n';
  for(ll u : kid0) {
    cout << u + 1 << ' ';
  }
  cout << '\n';
  for(ll u : kid1) {
    cout << u + 1 << ' ';
  }
  cout << '\n';

	return 0;
}
