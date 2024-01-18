// https://codeforces.com/gym/104847/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;

  ll n, a, b;
  cin >> n >> a >> b;

  ll q = b < a ? 0 : 64 - __builtin_clzll(b/a);
  if (q > n) {
    cout << "-1\n";
  } else {
    cout << q << '\n';
  }

  return 0;
}