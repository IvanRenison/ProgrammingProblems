// https://matcomgrader.com/problem/9542/a-symmetrical-pizza/
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

ll solve(ll r100) {
  // if (r >)
// ll r100 = (ll)(r * 100);

  // cout << 36000 / __gcd((int)36000, (int)r100) << "\n";
  return 36000 / __gcd((int)36000, (int)r100);
}

int main(){FIN;
  string rs; cin >> rs;
  ll r100 = 0;
  if (rs[1] == '.')
  {
    r100 += (rs[0] - '0') * 100;
    r100 += (rs[2] - '0') * 10;
    r100 += (rs[3] - '0');
  } else if (rs[2] == '.')
  {
    r100 += (rs[0] - '0') * 1000;
    r100 += (rs[1] - '0') * 100;
    r100 += (rs[3] - '0') * 10;
    r100 += (rs[4] - '0');
  } else
  {
    r100 += (rs[0] - '0') * 10000;
    r100 += (rs[1] - '0') * 1000;
    r100 += (rs[2] - '0') * 100;
    r100 += (rs[4] - '0') * 10;
    r100 += (rs[5] - '0');
  }

  if (r100 > 18000) r100 = 36000 - r100;

  cout << solve(r100) << "\n";

  // vi a;
  // for(ld i = 0.01; i < 360; i += 0.01)
  // {
  //   a.pb(solve(i));
  // }

  // fore(i, 0, SZ(a))
  // {
  //   if (a[i] != a[SZ(a) - i]) {cout << i << ": a[i] = " << a[i] << " a[n-1-i]=" << a[SZ(a)-i] << "\n"; return 0;}
  // }

  // cout << "idk\n";

  return 0;
}