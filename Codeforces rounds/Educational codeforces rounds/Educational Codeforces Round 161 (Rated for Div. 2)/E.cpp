// https://codeforces.com/contest/1922/problem/E

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

// count number of increasing subsequences
ull nis(const vu& as) {
  ull n = as.size();
  vu dp(n, 1);

  fore(i, 0, n) {
    fore(j, 0, i) {
      if (as[j] < as[i]) {
        dp[i] += dp[j];
      }
    }
  }

  ull sum = 0;
  fore(i, 0, n) {
    sum += dp[i];
  }

  return sum + 1;
}

optional<vu> solve1(ull X) {

  ull n = 63 - __builtin_clzll(X);

  vu ans(n);
  fore(i, 0, n) {
    ans[i] = i + 500;
  }

  ull x = 1ull << n;
  assert(x <= X);
  assert(X & x);

  X ^= x;

  for (ull i = n - 1; i < n && X > 0; i--) {
    /* if (X == (1ull << i)) {
      fore(j, 0, i + 1) {
        ans.push_back(j);
      }
    } else */ if (X & (1ull << i)) {
      ans.push_back(i + 500);
      X ^= 1ull << i;
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
    ull X;
    cin >> X;

    auto ans = solve1(X);
    if (ans) {
      cout << ans->size() << '\n';
      for (ull a : *ans) {
        cout << a << " ";
      }
      cout << '\n';
      //ull ni = nis(*ans);
      //cerr << ni << endl;
      //assert(nis(*ans) == X);
    } else {
      cout << -1 << '\n';
    }
  }

  return EXIT_SUCCESS;
}
