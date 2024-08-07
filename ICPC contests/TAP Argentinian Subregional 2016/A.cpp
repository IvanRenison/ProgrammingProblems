// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main() {
	cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;
  bool ans = false;
  for (char c : s) {
    ans = ans || c == 'i';
  }

  cout << (ans ? 'N' : 'S') << '\n';

}
