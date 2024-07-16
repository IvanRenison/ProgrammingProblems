// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  ll n, k, m;
  cin >> n >> k >> m;
  vector<string> ss(n);
  fore(i, 0, n) cin >> ss[i];
  vector<ll> cs(n);
  fore(i, 0, n) cin >> cs[i];
  map<string, ll> gs;
  vector<ll> bc(k, 1e18);
  fore(i, 0, k) {
    ll x;
    cin >> x;
    fore(j, 0, x) {
      ll wid;
      cin >> wid;
      wid--;
      bc[i] = min(bc[i], cs[wid]);
      gs[ss[wid]] = i;
    }
  }
  ll ans = 0;
  fore(i, 0, m) {
    string s;
    cin >> s;
    ans += bc[gs[s]];
  }
  cout << ans << "\n";
}