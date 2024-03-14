// https://redprogramacioncompetitiva.com/contests/2024/02/

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


ld solve(ull m, ull k, vu ss) {
  ull n = SZ(ss);
  sort(ALL(ss));
  reverse(ALL(ss));

  ull total = 0;
  fore(i, 0, n) {
    total += ss[i];
  }

  ull got = 0;
  fore(i, 0, min(m + k, n)) {
    got += ss[i];
  }

  return (ld)got / (ld)total * 100.0;

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m, k;
  cin >> n >> m >> k;
  vu ss(n);
  fore(i, 0, n) {
    cin >> ss[i];
  }

  auto ans = solve(m, k, ss);
  cout << setprecision(10) << fixed;
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
