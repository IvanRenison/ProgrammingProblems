// https://codeforces.com/gym/103049/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;

  ll n, k, d, s;
  cin >> n >> k >> d >> s;

  if (d*n < k*s || (d*n - k*s) > (n-k)*100) {
    cout << "impossible\n";
  } else {
    cout << setprecision(10);
    double ans = (double)(d*n - k*s) / ((double)(n-k));
    cout << ans << '\n';
  }

	return 0;
}
