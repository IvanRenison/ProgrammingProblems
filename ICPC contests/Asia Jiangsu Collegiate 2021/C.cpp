#include <bits/stdc++.h>
#define fst fist
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

string solve(vi as) {
  ll n = accumulate(ALL(as), 0ll);


  ll m = 0;
  ll first = -1;

  fore(i, 0, 10) {
    if (as[i] > as[m]) {
      m = i;
    }
    if (first == -1 && as[i] > 0) {
      first = i;
    }
  }
  if (n == 1) {
    string ans = "";
    ans.push_back('0' + first);
    return ans;
  }

  if (as[m] * 2 > n + 1 - (m == 0)) {
    return "-1";
  }

  string ans = "";
  int last = 0;

  while (n--) {
    ll m = 0;
    ll first = -1;

    fore(i, 0, 10) {
      if (i != last && as[i] > as[m]) {
        m = i;
      }
      if (i != last && first == -1 && as[i] > 0) {
        first = i;
      }
    }

    assert(first != -1);

    if (as[m] * 2 > n + 1) {
      ans.push_back('0' + m);
      as[m]--;
      last = m;
    } else {
      ans.push_back('0' + first);
      as[first]--;
      last = first;
    }

  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while(T--) {
    vi as(10);
    for (ll& a : as) {
      cin >> a;
    }

    cout << solve(as) << '\n';
  }

}