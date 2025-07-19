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
typedef vector<ii> vii;

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vii points(n);
  for (auto& [x, y] : points) {
    cin >> x >> y;
  }

  sort(ALL(points));
  cout << "YES\n";

  fore(i, 0, n - 1) {
    auto [x, y] = points[i];
    cout << x << ' ' << y << '\n';
  }

}