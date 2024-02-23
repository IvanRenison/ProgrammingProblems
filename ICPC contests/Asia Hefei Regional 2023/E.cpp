// https://codeforces.com/gym/104857/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cout.tie(0),cin.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

ll solve(const vector<vi>& mat) {
  ll n = mat.size(), m = mat[0].size();

  ll ans = 0;

  // Ver
  map<ll, ii> vals;
  fore(i, 0, n) {
     fore(j, 0, m) {
      ll c = mat[i][j];
      //cerr << i << ' ' << j << "    :";
      //cerr << "+= " << i * vals[c].first - vals[c].second << '\n';
      ans += i * vals[c].first - vals[c].second;
      vals[c].first++;
      vals[c].second += i;
    }
  }

  // hor
  vals.clear();
  fore(j, 0, m) {
    fore(i, 0, n) {
      ll c = mat[i][j];
      //cerr << i << ' ' << j << "    :";
      //cerr << "+= " << j * vals[c].first - vals[c].second << '\n';
      ans += j * vals[c].first - vals[c].second;
      vals[c].first++;
      vals[c].second += j;
    }
  }

  ans *= 2;

  return ans;
}

int main(){FIN;

  ll n, m;
  cin >> n >> m;
  vector<vi> mat(n, vi(m));
  for (vi& row : mat) {
    for (ll& c : row) {
      cin >> c;
    }
  }

  cout << solve(mat) << '\n';

  return 0;
}