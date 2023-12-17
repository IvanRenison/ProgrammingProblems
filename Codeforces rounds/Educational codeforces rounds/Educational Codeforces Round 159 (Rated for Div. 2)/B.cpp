// https://codeforces.com/contest/1902/problem/B

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


ull solve1(ull n, ull P, ull l, ull t) {

  ull p = 0;
  ull u = 0;

  ull d = 7;
  if (n >= d) {
    u += min((n - d + 13)/14, (P - p + l + 2 * t - 1)/(l + 2 * t));
    p += u * (l + 2 * t);
    d += u * 14;
  }
/*   for (; p < P && d < n; d += 14) {
    u++;
    p += l + 2 * t;
  } */
  d -= 7;
  if (p < P && d < n) {
    u++;
    p += l + t;
  }

  if (p >= P) {
    return n - u;
  }

  u += (P - p + l - 1) / l;

  return n - u;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull tc;
  cin >> tc;

  fore(i, 0, tc) {
    ull n, P, l, t;
    cin >> n >> P >> l >> t;

    auto ans = solve1(n, P, l, t);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
