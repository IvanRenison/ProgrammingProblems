// https://codeforces.com/gym/100553
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("alter.in", "r", stdin);
  freopen("alter.out", "w", stdout);
#endif

  ll n, m;
  cin >> n >> m;
  ll count = n / 2 + m / 2;
  cout << count << '\n';
  for (ll i = 2; i <= n; i += 2) {
    cout << i << " 1 " << i << " " << m << '\n';
  }
  for (ll j = 2; j <= m; j += 2) {
    cout << "1 " << j << ' ' << n << ' ' << j << '\n';
  }

}