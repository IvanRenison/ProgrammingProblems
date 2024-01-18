// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool solve(ll M, ll N, vector<tuple<ll, ll, ll>> XYS) {
  ull K = XYS.size();

  vector<vector<ull>> adj(K+2);
  // K = top left
  // K+1 = down right

  fore(u, 0, K) {
    auto [Xu, Yu, Su] = XYS[u];

    // Top || left
    if (Xu <= Su || Yu + Su >= N) {
      adj[K].push_back(u);
      adj[u].push_back(K);
    }

    // Down || right
    if (Xu + Su >= M || Yu <= Su) {
      adj[K+1].push_back(u);
      adj[u].push_back(K+1);
    }

    fore(v, u+1, K) {
      auto [Xv, Yv, Sv] = XYS[v];
      ll d2 = (Xv - Xu)*(Xv - Xu) + (Yv - Yu)*(Yv - Yu);
      if (d2 <= (Su + Sv)*(Su + Sv)) {
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
    }
  }

  // traverse
  vector<ull> s = {K};
  vector<bool> visited(K+2, false);
  visited[K] = true;

  while (!s.empty()) {
    ull u = s.back();
    s.pop_back();

    for(ull v : adj[u]) {
      if (v == K+1) {
        return false;
      }
      if (!visited[v]) {
        visited[v] = true;
        s.push_back(v);
      }
    }
  }

  return true;
}

int main(){FIN;
  ll M, N, K;
  cin >> M >> N >> K;
  vector<tuple<ll, ll, ll>> XYS(K);
  for(auto& [X, Y, S] : XYS) {
    cin >> X >> Y >> S;
  }

  if (solve(M, N, XYS)) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

  return 0;
}