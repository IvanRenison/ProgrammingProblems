// https://codeforces.com/gym/105327/problem/B
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

const ll N_lim = 101, M_lim = 1e6 + 1;
typedef bitset<N_lim> Actor;
typedef bitset<M_lim> Movie;

vector<optional<vi>> solve(ll M, vector<vi>& movies_, vii& queries) {
  ll N = movies_.size(), Q = queries.size();

  vector<Actor> actors(M);
  vector<Movie> movies(N);

  fore(i, 0, N) {
    for (ll a : movies_[i]) {
      movies[i][a] = 1;
      actors[a][i] = 1;
    }
  }

  vector<vii> movies_adj(N);
  fore(i, 0, N) fore(j, 0, i) {
    Movie in = movies[i] & movies[j];
    if (in.any()) {
      ll a = in._Find_first();
      movies_adj[i].push_back({j, a});
      movies_adj[j].push_back({i, a});
    }
  }

  vector<optional<vi>> ret(Q);
  fore(q, 0, Q) {
    auto [x, y] = queries[q];

    vii vis(N, {-1, -1}); // {movie, actor}
    queue<ll> que;
    fore(i, 0, N) {
      if (actors[x][i]) {
        vis[i] = {-1, x};
        que.push(i);
      }
    }

    while (!que.empty()) {
      auto i = que.front();
      que.pop();

      if (actors[y][i]) {
        vi ans;
        ans.push_back(y);
        ans.push_back(i);
        while (y != x) {
          auto [j, a] = vis[i];
          ans.push_back(a);
          if (j > -1) {
            ans.push_back(j);
          }
          i = j, y = a;
        }
        reverse(ALL(ans));
        ret[q] = move(ans);
        break;
      }

      for (auto [j, a] : movies_adj[i]) {
        if (vis[j].second == -1) {
          que.push(j);
          vis[j] = {i, a};
        }
      }
    }

  }

  return ret;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, M;
  cin >> N >> M;
  vector<vi> movies(N);
  for (vi& ac : movies) {
    ll n;
    cin >> n;
    ac = vi(n);
    for (ll& a : ac) {
      cin >> a;
      a--;
    }
  }
  ll Q;
  cin >> Q;
  vii queries(Q);
  for (auto& [x, y] : queries) {
    cin >> x >> y;
    x--, y--;
  }

  auto ans = solve(M, movies, queries);
  for (auto val : ans) {
    if (val.has_value()) {
      cout << val->size() / 2 + 1 << '\n';
      for (ll f : *val) {
        cout << f + 1 << ' ';
      }
    } else {
      cout << "-1";
    }
    cout << '\n';
  }

}
