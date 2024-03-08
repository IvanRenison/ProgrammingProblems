// https://codeforces.com/contest/1250/problem/L
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll t;
  cin >> t;

  while (t--) {
    ll a, b, c;
    cin >> a >> b >> c;

    if (a < c) {
      swap(a, c);
    }

    vi arr = {c, a/2, (a + 1)/2};

    sort(ALL(arr));

    fore(_, 0, b) {
      arr[0]++;
      sort(ALL(arr));
    }

    cout << arr[2] << '\n';
  }

  return 0;
}