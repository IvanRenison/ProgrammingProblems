// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m; cin >> n >> m;

  vector<vi> mat(n, vector<ll>(m));
  vector<array<ll, 3>> todo;

  fore(i, 0, n) fore(j, 0, m) {
    cin >> mat[i][j];
    if (!mat[i][j]) todo.pb({i + j, i, j});
  }

  sort(ALL(todo));
  reverse(ALL(todo));

  for (auto [w, i, j] : todo) {
    mat[i][j] = min(mat[i+1][j], mat[i][j+1]) - 1;
  }

  ll sum = 0;
  fore(i, 0, n) {
    fore(j, 1, m) {
      if (mat[i][j] <= mat[i][j-1]) {
        cout << -1 << "\n";
        return 0;
      }
    }
  }
  fore(j, 0, m) {
    fore(i, 1, n) {
      if (mat[i][j] <= mat[i - 1][j]) {
         cout << -1 << "\n";
        return 0;
      }
    }
  }
  fore(i, 0, n) fore(j, 0, m) sum += mat[i][j];

  cout << sum << "\n";

  return 0;
}