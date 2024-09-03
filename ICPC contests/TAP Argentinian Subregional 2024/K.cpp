// https://codeforces.com/gym/105321/problem/K
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) (ll)x.size()
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef tuple<ll,ll,ll> iii;

iii solve(vector<string>& grid) {
  ll N = grid.size();
  ll M = grid[0].size();

  vector<vi> per_row(N);
  fore(i, 0, N) fore(j, 0, M) if (grid[i][j] == '#') {
    per_row[i].pb(j);
  }
  ll T = 0, A = 0, P = 0;
  for (ll i = N - 1; i >= 0; i--) {
    for (ll j : per_row[i]) if (grid[i][j] == '#') {
      if (i >= 4 && j + 2 < M && grid[i][j+2] == '#' && grid[i-2][j+1] == '#') {
        A++;
        grid[i][j] = grid[i-1][j] = grid[i-2][j] = grid[i-3][j] = grid[i-4][j] = '.';
        grid[i][j+2] = grid[i-1][j+2] = grid[i-2][j+2] = grid[i-3][j+2] = grid[i-4][j+2] = '.';
        grid[i-4][j+1] = grid[i-2][j+1] = '.';
      } else if (i >= 4 && j + 2 < M && grid[i-2][j+1] == '#') {
        P++;
        grid[i][j] = grid[i-1][j] = grid[i-2][j] = grid[i-3][j] = grid[i-4][j] = '.';
        grid[i-2][j+2] = grid[i-3][j+2] = grid[i-4][j+2] = '.';
        grid[i-4][j+1] = grid[i-2][j+1] = '.';
      } else {
        T++;
        grid[i][j] = grid[i-1][j] = grid[i-2][j] = grid[i-3][j] = grid[i-4][j] = grid[i-4][j-1] = grid[i-4][j+1] = '.';
      }
    }
  }

  return {T, A, P};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M;
  cin >> N >> M;
  vector<string> grid(N);
  for (string& s : grid) {
    cin >> s;
  }

  auto [T, A, P] = solve(grid);

  cout << T << ' ' << A << ' ' << P << '\n';

}
