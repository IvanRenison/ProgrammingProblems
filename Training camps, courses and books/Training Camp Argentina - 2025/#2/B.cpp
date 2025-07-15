// https://codeforces.com/group/3Zw9kC8et8/contest/620982/problem/B
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
  string s;
  cin >> s;


  ll n_ver = 0, n_hor = 0;
  for (char c : s) {
    if (c == '0') { // ver
      cout << 0 + 1 << ' ' << n_ver + 1 << '\n';
      n_ver++;
      if (n_ver == 4) {
        n_ver = 0;
      }
    } else {
      cout << 3 + 1 << ' ' << 2 * n_hor + 1 << '\n';
      n_hor++;
      if (n_hor == 2) {
        n_hor = 0;
      }
    }
  }

}