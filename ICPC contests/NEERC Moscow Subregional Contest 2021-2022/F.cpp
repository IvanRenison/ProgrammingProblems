// https://codeforces.com/gym/104848/problem/F
#include <bits/stdtr1c++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;

int main(){FIN;
  ll n; cin >> n;

  if (n <= 3) {
    cout << -1 << "\n";
    return 0;
  }

  cout << n + 1 << "\n";

  cout << "1 2\n"
  << "2 3\n"
  << "3 4\n"
  << "4 1\n"
  << "2 4\n";

  fore(i, 5, n+1) cout << i - 1 << " " << i << "\n";

  return 0;
}