#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


vector<string> solve(ll n) {
  vector<string> ans;

  fore(x, 0, n) {
    string s;
    ll y = x;
    fore(i, 0, 4) {
      ll c = y % 10;
      y /= 10;
      s += char('0' + c);
      s += char('0' + c);
    }
    s += "!aA";
    ans.push_back(s);
  }

  return ans;
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll n;
  cin >> n;
  auto ans = solve(n);
  for (string s : ans) {
    cout << s << '\n';
  }

}
