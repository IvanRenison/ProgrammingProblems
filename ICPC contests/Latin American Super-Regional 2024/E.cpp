// https://codeforces.com/gym/105053/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

vi solve(const vector<pair<char, ll>>& Xs) {
  ll N = Xs.size() / 2;

  vii times(N);
  fore(i, 0, 2*N) {
    auto [c, X] = Xs[i];
    if (c == '+') {
      times[X].first = i;
    } else {
      times[X].second = i;
    }
  }

  vector<vi> adj(N);

  fore(i, 0, N) {
    auto [i0, i1] = times[i];
    fore(j, i + 1, N) {
      auto [j0, j1] = times[j];
      if ((i0 < j0 && j0 < i1 && i1 < j1) || (j0 < i0 && i0 < j1 && j1 < i1)) {
        adj[i].push_back(j), adj[j].push_back(i);
      }
    }
  }

  vi vis(N, -1);

  fore(u, 0, N) {
    if (vis[u] == -1) {
      vi s = {u};
      vis[u] = 0;

      while (!s.empty()) {
        ll v = s.back();
        s.pop_back();

        ll c = 1 - vis[v];

        for (ll w : adj[v]) {
          if (vis[w] == -1) {
            vis[w] = c;
            s.push_back(w);
          } else {
            if (vis[w] != c) {
              return {};
            }
          }
        }
      }
    }
  }

  return vis;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;

  vector<pair<char, ll>> Xs(2*N);

  for (auto& [c, X] : Xs) {
    cin >> c >> X;
    X--;
  }

  auto ans = solve(Xs);

  if (ans.empty()) {
    cout << "*";
  } else {
    fore(i, 0, N) {
      if (ans[i]) {
        cout << 'G';
      } else {
        cout << 'S';
      }
    }
  }
  cout << '\n';

}