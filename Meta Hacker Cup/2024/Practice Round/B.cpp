// https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/B

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

const ull inf = 1ull << 60;
const ld eps = 1e-7;

ld exp(ld x, ull e) {
  ld res = 1.0;
  while (e) {
    if (e & 1) res *= x;
    x *= x;
    e >>= 1;
  }
  return res;
}

ld solve(ull N, ld P) {

  ld N_minus_1_val = exp(P, N - 1); // Fail probability

  ld l = P, r = 1.0;
  fore(_, 0, 200) {
    ld m = (l + r) / 2.0;
    ld N_val = exp(m, N);
    if (N_val > N_minus_1_val) {
      r = m;
    } else {
      l = m;
    }
  }
  return (l + r) / 2.0 - P;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  cout << setprecision(15);
  fore(i, 0, t) {
    ull N, P;
    cin >> N >> P;

    auto ans = solve(N, (ld)P / 100.0);
    cout << "Case #" << i + 1 << ": " << (ans * 100.0) << '\n';
  }

}
