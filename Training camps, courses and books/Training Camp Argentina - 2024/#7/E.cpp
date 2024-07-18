// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

string solve(string& s) {
  ll n = s.size();

  if (n == 1 || s[0] == s[1]) {
    string ans = "";
    ans += s[0];
    ans += s[0];
    return ans;
  }

  ll k = 0;
  while(k+1 < n && s[k+1] <= s[k]) {
    k++;
  }
  // cerr << k << endl;
  string res = s.substr(0, k+1);
  string inv = res;
  reverse(ALL(inv));
  res += inv;
  return res;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    string res = solve(s);
    cout << res << "\n";
  }
}