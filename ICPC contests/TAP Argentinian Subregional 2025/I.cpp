// https://codeforces.com/gym/106054/problem/I
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

vi solve(ll N, ll M, vector<tuple<ll, ll, vi>>& games) {

  vi ans(N + 1);
  fore(i, 0, M) {
    auto& [X, Y, others] = games[i];
    ll count0 = 0;
    for (ll o : others) {
      count0 += o == 0;
    }

    ll win0 = X / (count0 + 1);
    if (win0 >= Y) { // Ella elije 0
      ans[N] += win0;
      fore(i, 0, N) {
        if (others[i] == 0) {
          ans[i] += win0;
        } else {
          ans[i] += Y;
        }
      }
    } else {
      ans[N] += Y;
      fore(i, 0, N) {
        if (others[i] == 0) {
          ans[i] += X / count0;
        } else {
          ans[i] += Y;
        }
      }
    }
  }

  return ans;

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, M;
  cin >> N >> M;
  vector<tuple<ll, ll, vi>> games(M);
  for (auto& [X, Y, ops] : games) {
    cin >> X >> Y;
    ops = vi(N);
    for (ll& o : ops) {
      cin >> o;
      o--;
    }
  }

  vi ans = solve(N, M, games);
  for (ll a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

}