// https://codeforces.com/gym/106054/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

bool solve(string& s) {
  ll n = s.size();

  ll i = 0;
  while (i < n && s[i] != 'T') {
    i++;
  }
  if (i == n) {
    return false;
  }
  i++;
  while (i < n && s[i] != 'A') {
    i++;
  }
  if (i == n) {
    return false;
  }
  i++;
  while (i < n && s[i] != 'P') {
    i++;
  }
  if (i == n) {
    return false;
  }
  return true;

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;

  if (solve(s)) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }
}
