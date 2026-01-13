// https://codeforces.com/gym/106193/problem/C
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,renison=b;i<renison;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define imp(v) {for(auto i:v)cout<<i<<" ";cout<<"\n";}
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
typedef vector<ll> vi;

int main(){
  FIN;

  ll n;

  cin >> n;

  if (n == 0) {
    cout << 0 << '\n';
    return 0;
  }

  vi bits;
  while (n > 0) {

    bits.push_back(n & 1);
    n /= 2;
  }

  assert(bits.back() == 1);

  vi secs;
  fore(i, 0, bits.size()) {
    if (i % 7 == 0) {
      secs.push_back(0);
    }
    secs.back() |= bits[i] << (i % 7);
  }

  reverse(ALL(secs));

  fore(i, 0, secs.size() - 1) {
    secs[i] |= 1 << 7;
  }

  for (ll a : secs) {
    cout << a << ' ';
  }
  cout << '\n';

  return 0;
}
