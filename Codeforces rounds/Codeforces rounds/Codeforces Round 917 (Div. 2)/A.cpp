// https://codeforces.com/contest/1917/problem/A

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


vector<pair<ull, ll>> solve1(vi as) {
  ull cnt0 = 0, cntNeg = 0, cntPos = 0;

  fore(i, 0, as.size()) {
    if (as[i] == 0) {
      cnt0++;
    } else if (as[i] < 0) {
      cntNeg++;
    } else {
      cntPos++;
    }
  }

  if (cnt0 > 0) {
    return {};
  } else if (cntNeg % 2 == 0) {
    return {{0, 0}};
  } else {
    return {};
  }

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
    fore(j, 0, n) { cin >> as[j]; }

    auto ans = solve1(as);
    cout << ans.size() << '\n';
    fore(j, 0, ans.size()) {
      cout << ans[j].first + 1 << ' ' << ans[j].second << '\n';
    }
  }

  return EXIT_SUCCESS;
}
