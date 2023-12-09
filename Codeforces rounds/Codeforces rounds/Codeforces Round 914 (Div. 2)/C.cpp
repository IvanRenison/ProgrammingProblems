// https://codeforces.com/contest/1904/problem/C

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
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

ull solve1(ull k, vu& as) {
  ull n = as.size();

  if (k >= 3) {
    return 0;
  }

  sort(all(as));

  if (k == 1) {
    ull min_diff = inf;
    fore(i, 1, n) {
      min_diff = min(min_diff, as[i] - as[i - 1]);
    }
    return min(as[0], min_diff);
  } else {

    set<ull> diffs;
    fore(i, 0, n) {
      fore(j, i + 1, n) {
        ull d = as[j] - as[i];
        diffs.insert(d);
      }
    }

    ull min_diffs = *diffs.begin();


    ull min_in_diff = inf;
    fore(i, 0, n) {
      auto it = diffs.lower_bound(as[i]);
      if (it != diffs.end()) {
        min_in_diff = min(min_in_diff, *it - as[i]);
      }
      if (it != diffs.begin()) {
        it--;
        min_in_diff = min(min_in_diff, as[i] - *it);
      }
    }

    return min({as[0], min_in_diff, min_diffs});
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(k, as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
