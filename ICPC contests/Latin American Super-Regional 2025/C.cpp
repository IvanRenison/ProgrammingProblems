// https://codeforces.com/gym/105789/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll C, N;
  cin >> C >> N;
  vi Ts(N);
  for (ll& T : Ts) {
    cin >> T;
  }

  auto can = [&](ll lim) -> bool {
    ll count = 0;
    fore(i, 0, N) {
      if (Ts[i] < lim) {
        count++;
      } else {
        count = 0;
      }
      if (count > C) {
        return false;
      }
    }
    return true;
  };

  ll l = -51, r = 51;

  while (l + 1 < r) {
    ll m = (l + r) / 2;
    if (can(m)) {
      l = m;
    } else {
      r = m;
    }
  }

  cout << l << '\n';

}