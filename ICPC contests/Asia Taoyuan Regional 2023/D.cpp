// https://codeforces.com/gym/105544
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  fore(tc, 1, t + 1) {
    ll n, m, d0, d1;
    cin >> n >> m >> d0 >> d1;
    vector<string> grid(n);
    for (string& s : grid) {
      cin >> s;
    }

    cout << "Airplane #" << tc << ":\n";

    auto V = [&](ll i, ll j) {
      if (i < 0 || j < 0 || i >= n || j >= m) {
        return false;
      }
      return grid[i][j] == 'V';
    };

    fore(i, 0, n) fore(j, 0, m) if (grid[i][j] == '.') {
      if (V(i-1, j) || V(i + 1, j) || V(i,j-1) || V(i,j+1)) {
        grid[i][j] = '0' + d0;
      } else if (V(i-1,j-1) || V( i-1,j+1) || V(i+1,j-1) || V(i+1,j+1)) {
        grid[i][j] = '0' + d1;
      } else {
        grid[i][j] = '0';
      }
    }

    for (string s : grid) {
      cout << s << '\n';
    }

  }

}