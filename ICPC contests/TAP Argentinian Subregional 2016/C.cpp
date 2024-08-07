// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/C
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

vi solve(const vii& edges, const vi& Ps) {
  ll M = edges.size(), N = Ps.size();

  vector<vi> adj_ford(N);
  vector<ll> adj_back_count(N, 0);
  for (auto [u, v] : edges) {
    adj_ford[u].push_back(v);
    adj_back_count[v]++;
  }

  vector<bool> passed(N, false);

  vi ans(N);
  ll count = 0;
  fore(i, 0, N) {
    ll P = Ps[i];

    passed[P] = true;
    if (adj_back_count[P] == 0) {
      vi s = {P};
      while (!s.empty()) {
        count++;
        ll u = s.back();
        s.pop_back();
        for (ll v : adj_ford[u]) {
          adj_back_count[v]--;
          if (adj_back_count[v] == 0 && passed[v]) {
            s.push_back(v);
          }
        }
      }
    }


    ans[i] = count;
  }

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll N, M;
  cin >> N >> M;
  vii edges(M);
  for (auto& [A, B] : edges) {
    cin >> A >> B;
    A--, B--;
  }
  vi Ps(N);
  for (ll& P : Ps) {
    cin >> P;
    P--;
  }
  vi ans = solve(edges, Ps);
  for (ll a : ans) {
    cout << a << '\n';
  }

}
