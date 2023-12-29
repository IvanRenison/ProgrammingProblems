// https://codeforces.com/contest/1917/problem/C

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

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


ull solve1(vu& as, const vu& vs, ull d) {
  ull n = as.size(), k = vs.size();

  ull best_start = (d - 1) / 2;
  fore(i, 0, n) {
    if (as[i] == i + 1) {
      best_start++;
    }
  }

  fore(i, 0, min(d - 1, 2 * n + 10)) {
    ull b = vs[i % k];
    fore(j, 0, b) {
      as[j]++;
    }

    ull this_start = (d - i - 2) / 2;
    fore(j, 0, n) {
      if (as[j] == j + 1) {
        this_start++;
      }
    }

    best_start = max(best_start, this_start);
  }

  return best_start;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k, d;
    cin >> n >> k >> d;
    vu as(n), vs(k);
    fore(j, 0, n) {
      cin >> as[j];
    }
    fore(j, 0, k) {
      cin >> vs[j];
    }

    auto ans = solve1(as, vs, d);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
