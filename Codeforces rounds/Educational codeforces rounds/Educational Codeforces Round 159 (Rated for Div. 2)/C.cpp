// https://codeforces.com/contest/1902/problem/C

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


ull solve1(const vi& as) {
  ull n = as.size();

  if (n == 1) {
    return 1;
  }

  ll min_a = *min_element(all(as));

  vu bs(n);
  fore(i, 0, n) {
    bs[i] = as[i] - min_a;
  }

  ull gcd_bs = bs[0];
  fore(i, 1, n) {
    gcd_bs = gcd(gcd_bs, bs[i]);
  }

  fore(i, 0, n) {
    bs[i] /= gcd_bs;
  }

  sort(all(bs));

  ull max_b = bs[n - 1];

  ull sum_to_max_b = 0;
  fore(i, 0, n) {
    sum_to_max_b += max_b - bs[i];
  }

  // Find the biggest element smaller than max_b that is not in bs
  ull max_not = 0;
  for(ull i = n - 1; 0 < i; i--) {
    if (bs[i] != bs[i - 1] + 1) {
      max_not = bs[i] - 1;
      break;
    }
  }

  ull sum_for_extra = min(max_not == 0 ? max_b + 1 : max_b - max_not, n);

  return sum_to_max_b + sum_for_extra;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vi as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
