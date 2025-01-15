// https://codeforces.com/contest/2043/problem/B

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


vu solve(ull n, ull d) {
  vu ans = {1};

  if (n >= 3 || d == 3 || d == 6 || d == 9)  {
    ans.push_back(3);
  }

  if (d == 5) {
    ans.push_back(5);
  }

  if (d == 7 || n >= 3) {
    ans.push_back(7);
  }

  if (d == 9 || n >= 6 || ((d == 3 || d == 6) && n >= 3)) {
    ans.push_back(9);
  }

  return ans;
}

vu force(ull n, ull d) {
  ull fact = 1;
  fore(i, 1, n + 1) {
    fact *= i;
  }


  ull val = 0;
  fore(_, 0, fact) {
    val = val * 10 + d;
  }

  vu ans;

  for (ull u = 1; u < 10; u += 2) {
    if (val % u == 0) {
      ans.push_back(u);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

/*   fore(d, 1, 10) {
    ull val = d;
    fore(n, 1, 20) {
      cout << val << " " << val % 9 << endl;
      val = val * 10 + d;
      continue;
      vu ans;
      for (ull u = 1; u < 10; u += 2) {
        if (val % u == 0) {
          ans.push_back(u);
        }
      }
      for (auto x : ans) {
        cout << x << " ";
      }
      cout << '\n';
      val = val * 10 + d;
    }
  }
  return 0; */

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, d;
    cin >> n >> d;

    auto ans = solve(n, d);
    for (auto x : ans) {
      cout << x << " ";
    }
    cout << '\n';
  }
#else
  fore(n, 2, 4) {
    fore(d, 1, 10) {
      auto ans = solve(n, d);
      auto ans2 = force(n, d);
      if (ans != ans2) {
        cout << "n = " << n << " d = " << d << endl;
        for (auto x : ans) {
          cout << x << " ";
        }
        cout << endl;
        for (auto x : ans2) {
          cout << x << " ";
        }
        cout << endl;
        return 1;
      }
    }
  }
#endif
}
