// https://codeforces.com/gym/106054/problem/G
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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll A, B, C;
  cin >> A >> B >> C;
  bool ans = (B - A) % C == 0;
  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

}
