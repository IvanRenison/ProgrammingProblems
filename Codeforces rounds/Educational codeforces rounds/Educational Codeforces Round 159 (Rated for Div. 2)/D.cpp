// https://codeforces.com/contest/1902/problem/D

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


vb solve(const string& s, const vuuuu& querys) {
  ull n = s.size(), q = querys.size();

  map<ii, set<ull>> m;
  vii poss(n + 1);

  ii xy = {0, 0};
  m[xy].insert(0);
  poss[0] = xy;
  fore(i, 0, n) {
    if (s[i] == 'U') {
      xy.second++;
    } else if (s[i] == 'D') {
      xy.second--;
    } else if (s[i] == 'L') {
      xy.first--;
    } else if (s[i] == 'R') {
      xy.first++;
    }

    m[xy].insert(i + 1);
    poss[i + 1] = xy;
  }

  vb ans(q);
  fore(i, 0, q) {
    auto [x, y, l, r] = querys[i];

    {
      const set<ull>& ss = m[{x, y}];

      if (ss.size() == 0) {
        ans[i] = false;
        goto next;
      }

      ull fst = *ss.begin();
      ull lst = *ss.rbegin();

      if (fst <= l || lst > r) {
        ans[i] = true;
        continue;
      } else {
        ans[i] = false;
        goto next;
      }
    }

    next:
    {
      ii xyl = poss[l];
      auto [xl, yl] = xyl;
      ii xyr = poss[r + 1];
      auto [xr, yr] = xyr;

      ll x_ = xl + xr - x;
      ll y_ = yl + yr - y;

      ii xy_ = {x_, y_};

      const set<ull>& ss = m[xy_];

      auto it_l = ss.lower_bound(l + 1);
      if (it_l == ss.end()) {
        ans[i] = false;
        continue;
      }

      ull l_time = *it_l;
      if (l_time <= r) {
        ans[i] = true;
        continue;
      } else {
        ans[i] = false;
        continue;
      }

    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  vuuuu querys(q);
  for (auto& [x, y, l, r] : querys) {
    cin >> x >> y >> l >> r;
    l--, r--;
  }

  auto ans = solve(s, querys);
  for (auto a : ans) {
    cout << (a ? "YES" : "NO") << '\n';
  }

  return EXIT_SUCCESS;
}
