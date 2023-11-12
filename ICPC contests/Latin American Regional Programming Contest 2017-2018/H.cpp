// https://codeforces.com/gym/101889
#include<bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ull> vull;

int main(){FIN;
  ll a1, b1, c1, a2, b2, c2;
  cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

  ll res = 0;
  if (a2 > a1) res += a2 - a1;
  if (b2 > b1) res += b2 - b1;
  if (c2 > c1) res += c2 - c1;

  cout << res << "\n";

  return 0;
}