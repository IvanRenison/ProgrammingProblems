// https://codeforces.com/contest/2111/problem/B

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

vu fibs(21);

void init() {
  fibs[0] = 1;
  fibs[1] = 1;
  for (ull i = 2; i < 21; i++) {
    fibs[i] = fibs[i - 1] + fibs[i - 2];
  }
}


vb solve(ull n, vuuu& boxes) {
  ull m = boxes.size();
  ull f = fibs[n];
  ull fp = fibs[n - 1];

  vb ans(m);
  fore(i, 0, m) {
    auto [w, l, h] = boxes[i];

    ans[i] = (f + fp <= w && f <= l && f <= h)
            || (f + fp <= h && f <= w && f <= l)
            || (f + fp <= l && f <= w && f <= h);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vuuu boxes(m);
    for (auto& [w, l, h] : boxes) {
      cin >> w >> l >> h;
    }


    auto ans = solve(n, boxes);
    fore(i, 0, m) {
      if (ans[i]) {
        cout << '1';
      } else {
        cout << '0';
      }
    }
    cout << '\n';
  }

}
