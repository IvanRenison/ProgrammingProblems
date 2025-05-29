// https://codeforces.com/gym/105925/problem/E

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

//const ull inf = 1ull << 60;
const ld eps = 1e-7;

vector<ii> factor(ull n) {
  vector<ii> res;
  for (ull i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ll k = 0;
      while (n % i == 0) {
        n /= i;
        k++;
      }
      res.push_back({i, k});
    }
  }
  if (n > 1) res.push_back({n, 1});
  return res;
}


ull solve(ull Y, ull K) {

  vii Y_facts = factor(Y);

  ull X = 1;

  for (auto [p, e] : Y_facts) {
    fore(i, 0, e) {
      ull count = p - 1;
      if (K <= count) {
        X += gcd(X, Y) * K;
        goto end;
      }

      X += gcd(X, Y) * count;
      K -= count;
    }


  }

  X += gcd(X, Y) * K;
end:
  return X;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull Y, K;
  cin >> Y >> K;

  auto ans = solve(Y, K);
  cout << ans << '\n';

}
