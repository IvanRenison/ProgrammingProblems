// https://codeforces.com/contest/2026/problem/C

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

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(vb& s) {
  ull n = SZ(s);

  s[0] = false;

  ull ans = 0;

  rpriority_queue<ull> free, used;
  free.push(0);

  fore(i, 1, n) {
    if (s[i]) {
      if (!free.empty()) {
        ull x = free.top();
        free.pop();
        ans += x + 1;
        used.push(i);
      } else {
        assert(!used.empty());
        ull x = used.top();
        used.pop();
        used.push(i);
        free.push(x);
      }
    } else {
      free.push(i);
    }
  }

  while (!free.empty()) {
    ull x = free.top();
    free.pop();
    ans += x + 1;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vb s(n);
    fore(j, 0, n) {
      char c;
      cin >> c;
      s[j] = c == '1';
    }

    auto ans = solve(s);
    cout << ans << '\n';
  }
}
