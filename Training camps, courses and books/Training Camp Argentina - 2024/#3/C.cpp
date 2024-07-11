// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

const ll mod = 998244353;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll h, w;
  cin >> h >> w;

  ll ans = 1;
  fore(i, 0, h) {
    ans *= 2;
    ans %= mod;
  }
  fore(i, 0, w) {
    ans *= 2;
    ans %= mod;
  }

  cout << ans << '\n';

}