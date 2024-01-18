// https://codeforces.com/gym/104848/problem/N
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

bool lt(ii a, ii b) {
  a.fst *= b.snd;
  b.fst *= a.snd;
  return a.fst < b.fst;
}

ii add(ii a, ii b) {
  return {a.fst * b.snd + b.fst * a.snd, a.snd * b.snd};
}

bool eq(ii a, ii b) {
  return !(lt(a, b) || lt(b, a));
}

int main(){FIN;
  ll a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;

  ii s1 = {1, 1}, s2 = {b, a}, s3 = {e, f};

  if (lt(s3, add(s1, s2)) && lt(s1, add(s2, s3)) && lt(s2, add(s1, s3)) && eq({b*f, a*e}, {c, d})) {
    cout << 1 << "\n";
  } else cout << -1 << "\n";

  return 0;
}