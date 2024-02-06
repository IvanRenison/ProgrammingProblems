// https://codeforces.com/contest/1919/problem/C

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

ull pen(const vu& as) {
  ull n = as.size();
  ull ans = 0;
  if (n > 0) {
    fore(i, 0, n - 1) {
      ans += as[i] < as[i + 1];
    }
  }
  return ans;
}

ull force(const vu& as) {
  ull n = as.size();

  ull ans = inf;

  fore(x, 0, 1 << n) {
    vu bs0, bs1;
    fore(i, 0, n) {
      if (x & (1 << i)) {
        bs0.push_back(as[i]);
      } else {
        bs1.push_back(as[i]);
      }
    }
    ans = min(ans, pen(bs0) + pen(bs1));
  }

  return ans;
}

ull solve1(vu as) {
  ull n = as.size();

  if (n == 1) {
    return 0;
  }

  ull ans = 0;

  ull m = 0, M = as[0];
  fore(i, 1, n) {
    ull a = as[i];
    if (a > M) {
      ans += m > 0;
      m = M, M = a;
    } else {
      if (a <= m) {
        m = a;
      } else {
        M = a;
      }
    }
  }


  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    for (ull& a : as) {
      cin >> a;
    }

    auto ans = solve1(as);
    cout << ans << '\n';
  }

/*   fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    vu as(n);
    fore(i, 0, n) {
      as[i] = rand() % n + 1;
    }
    ull ans = solve1(as);
    ull ans2 = force(as);
    if (ans != ans2) {
      cerr << "FAIL\n";
      for (ull a : as) {
        cerr << a << ' ';
      }
      cerr << '\n';
      DBG(ans);
      DBG(ans2);
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
