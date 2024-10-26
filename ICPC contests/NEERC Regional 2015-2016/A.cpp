// https://codeforces.com/gym/100851
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
#ifdef ONLINE_JUDGE
    freopen("adjustment.in", "r",stdin);
    freopen("adjustment.out","w",stdout);
#endif

  ll n, q;
  cin >> n >> q;

  ll rows_sum = n * (n + 1) / 2;
  ll cols_sum = n * (n + 1) / 2;

  vector<bool> used_rows(n, false), used_cols(n, false);
  ll count_rows = 0, cont_cols = 0;

  while (q--) {
    char t;
    cin >> t;
    if (t == 'R') {
      ll r;
      cin >> r;
      if (!used_rows[r - 1]) {
        ll ans = cols_sum + r * (n - cont_cols);
        cout << ans << '\n';
        count_rows++;
        used_rows[r - 1] = true;
        rows_sum -= r;
      } else {
        cout << "0\n";
      }
    } else {
      ll c;
      cin >> c;
      if (!used_cols[c - 1]) {
        ll ans = rows_sum + c * (n - count_rows);
        cout << ans << '\n';
        cont_cols++;
        used_cols[c - 1] = true;
        cols_sum -= c;
      } else {
        cout << "0\n";
      }
    }
  }

}