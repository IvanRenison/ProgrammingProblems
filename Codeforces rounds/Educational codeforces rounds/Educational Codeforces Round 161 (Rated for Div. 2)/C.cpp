// https://codeforces.com/contest/1922/problem/C

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

ull dist(ull a, ull b) {
  return a > b ? a - b : b - a;
}

vu solve1(vu& as, vuu& querys) {
  ull n = as.size(), m = querys.size();

  vu costs_ford(n - 1);
  costs_ford[0] = 1;
  fore(i, 1, n - 1) {
    if (dist(as[i], as[i + 1]) < dist(as[i - 1], as[i])) {
      costs_ford[i] = 1;
    } else {
      costs_ford[i] = as[i + 1] - as[i];
    }
  }

  reverse(all(as));
  for (ull& a : as) {
    a = 1e9 + 1 - a;
  }
  vu costs_back(n - 1);
  costs_back[0] = 1;
  fore(i, 1, n - 1) {
    if (dist(as[i], as[i + 1]) < dist(as[i - 1], as[i])) {
      costs_back[i] = 1;
    } else {
      costs_back[i] = as[i + 1] - as[i];
    }
  }

  vu pre_sums(n), rev_pre_sums(n);
  fore(i, 0, n - 1) {
    pre_sums[i + 1] = pre_sums[i] + costs_ford[i];
  }
  fore(i, 0, n - 1) {
    rev_pre_sums[i + 1] = rev_pre_sums[i] + costs_back[i];
  }

  vu ans(m);

  fore(i, 0, m) {
    auto [a, b] = querys[i];
    if (b > a) {
      ans[i] = pre_sums[b] - pre_sums[a];
    } else {
      ans[i] = rev_pre_sums[n - 1 - b] - rev_pre_sums[n - 1 - a];
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
    fore(i, 0, n) {
      cin >> as[i];
    }
    ull m;
    cin >> m;
    vuu querys(m);
    for (auto& [a, b] : querys) {
      cin >> a >> b;
      a--, b--;
    }

    auto ans = solve1(as, querys);
    for (auto a : ans) {
      cout << a << '\n';
    }
  }

  return EXIT_SUCCESS;
}
