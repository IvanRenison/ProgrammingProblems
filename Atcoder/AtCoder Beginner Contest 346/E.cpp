// https://atcoder.jp/contests/abc346/tasks/abc346_e

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


vuu solve(ull H, ull W, const vuuu& queries) {
  ull M = queries.size();

  ull h = H, w = W;
  set<ull> cols, rows;

  map<ull, ull> ans;

  fore(i, 0, M) {
    auto [T, A, X] = queries[M - 1 - i];

    if (T == 0) {
      if (!rows.count(A)) {
        if (w > 0)
          ans[X] += w;
        h--;
        rows.insert(A);
      }
    } else {
      if (!cols.count(A)) {
        if (h > 0)
          ans[X] += h;
        w--;
        cols.insert(A);
      }
    }
  }

  if (w * h > 0)
    ans[0] += w * h;

  vuu ans_;
  for (auto [c, x] : ans) {
    ans_.push_back({c, x});
  }


  return ans_;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull H, W, M;
  cin >> H >> W >> M;
  vuuu queries(M);
  for (auto& [T, A, X] : queries) {
    cin >> T >> A >> X;
    T--, A--;
  }

  auto ans = solve(H, W, queries);
  cout << ans.size() << '\n';
  for (auto [c, x] : ans) {
    cout << c << ' ' << x << '\n';
  }

  return EXIT_SUCCESS;
}
