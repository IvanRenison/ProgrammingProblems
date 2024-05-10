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

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;

  while (T--) {
    ll n;
    cin >> n;
    vector<string> ss0(n), ss1(n);
    for (string& s : ss0) {
      cin >> s;
    }
    for (string& s : ss1) {
      cin >> s;
    }

    bool ans = true;

    fore(i, 0, n) {
      bool level0 = ss0[i].back() == '1' || ss0[i].back() == '2';
      bool level1 = ss1[i].back() == '1' || ss1[i].back() == '2';

      if (level0 == level1) {
        ans = false;
        break;
      }
    }

    if (ss0.back().back() == '1' || ss0.back().back() == '2') {
      ans = false;
    }

    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }


  }


}