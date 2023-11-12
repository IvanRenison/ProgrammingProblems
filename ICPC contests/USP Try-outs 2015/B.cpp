// https://codeforces.com/gym/101047/problem/B
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool is_palindromic(vector<ll> a) {
  ll n = SZ(a);
  bool p = true;
  fore(i, 0, n) {
    p = p && a[i] == a[n - 1 - i];
  }
  return p;
}

int main() {
  FIN;
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll aux;
    vector<ll> ans;
    fore(i, 2, 17) {
      aux = n;
      vector<ll> a;
      if (aux == 0) {
        ans.pb(i);
        continue;
      }
      while (aux > 0) {
        a.pb(aux % i);
        aux /= i;
      }
      if (is_palindromic(a)) {
        ans.pb(i);
      }
    }
    if (SZ(ans) == 0) {
      cout << "-1\n";
    } else {
      for (auto i : ans)
        cout << i << " ";
      cout << "\n";
    }
  }
  return 0;
}