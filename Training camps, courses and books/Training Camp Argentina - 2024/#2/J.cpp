// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/J
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

// Find a 5 clique or a 5 independet set
optional<vi> solve(ll N, const vii& edges) {
  vector<set<ll>> adj(N);
  for (auto [u, v] : edges) {
    adj[u].insert(v), adj[v].insert(u);
  }

  // Test all posibilites
  fore(u, 0, N) fore(v, 0, u) fore(w, 0, v) fore(x, 0, w) fore(y, 0, x) {
    vi us = {u, v, w, x, y};

    // Test independet set
    fore(i, 0, 5) fore(j, i + 1, 5) {
      ll a = us[i], b = us[j];
      if (!(adj[a].count(b))) goto next;
    }

    return us;

    next:

    // Test clique
    fore(i, 0, 5) fore(j, i + 1, 5) {
      ll a = us[i], b = us[j];
      if (adj[a].count(b)) goto last;
    }

    return us;

    last:
  }

  return {};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M;
  cin >> N >> M;
  vii edges(M);
  for (auto& [U, V] : edges) {
    cin >> U >> V;
    U--, V--;
  }

  auto ans = solve(N, edges);
  if (ans) {
    for (ll a : *ans) {
      cout << a + 1 << ' ';
    }
  } else {
    cout << -1;
  }
  cout << '\n';
}