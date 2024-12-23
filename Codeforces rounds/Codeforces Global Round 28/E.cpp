// https://codeforces.com/contest/2048/problem/E

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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


optional<vector<vu>> solve(ull n, ull m) {
  if (m >= 2 * n) return {};

  vector<vu> ans(2 * n, vu(m));
  fore(i, 0, 2 * n) {
    fore(j, 0, m) {
      ans[i][j] = ((i + j) / 2) % n;
    }
  }

  return ans;
}

bool check(const vector<vu>& ans) {
  ull n = ans.size() / 2;
  ull m = ans[0].size();

  fore(c, 0, n) {
    vb vis(2 * n + m, false);
    fore(u, 0, 2 * n + m) if (!vis[u]) {
      vuu s = {{u, inf}};
      vis[u] = false;
      for (ull i = 0; i < s.size(); i++) {
        auto [v, p] = s[i];

        if (v < 2 * n) {
          fore(j, 0, m) if (ans[v][j] == c && j + 2 * n != p) {
            if (vis[2 * n + j]) {
              return false;
            }
            vis[2 * n + j] = true;
            s.push_back({2 * n + j, v});
          }
        } else {
          fore(j, 0, 2 * n) if (ans[j][v - 2 * n] == c && j != p) {
            if (vis[j]) {
              return false;
            }
            vis[j] = true;
            s.push_back({j, v});
          }
        }
      }
    }
  }

  return true;
}

vector<vector<vu>> force(ull n, ull m) {
  //assert(n * 2 * n * m < 25);

  vector<vector<vu>> all_ans;

  fore(x, 0, 1ull << (n * 2 * n * m)) {
    vu vec(2 * n * m);
    ull y = x;
    fore(i, 0, 2 * n * m) {
      vec[i] = y % n;
      y /= n;
    }

    vector<vu> ans(2 * n, vu(m));
    fore(i, 0, 2 * n) {
      fore(j, 0, m) {
        ans[i][j] = vec[i * m + j];
      }
    }

    if (check(ans)) {
      return {ans};
    }
  }

  return all_ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    auto ans = solve(n, m);

    if (ans.has_value()) {
      assert(ans->size() == 2 * n);
      cout << "Yes\n";
      fore(i, 0, 2 * n) {
        fore(j, 0, m) {
          cout << (*ans)[i][j] + 1 << " ";
        }
        cout << "\n";
      }
      //cout << endl;
      //assert(check(*ans));
    } else {
      cout << "No\n";
    }
  }
#else

  fore(n, 1, 10) fore(m, 1, 2 * n + 1) if (2 * n * n * m <= 32) {
    auto ans = solve(n, m);
    auto ansf = force(n, m);
    if (ans.has_value() == ansf.empty()) {
      cout << n << " " << m << "\n";
      if (!ansf.empty()) {
        auto ansf_ = ansf[0];
        fore(i, 0, 2 * n) {
          fore(j, 0, m) {
            cout << ansf_[i][j] << " ";
          }
          cout << "\n";
        }
        cout << "\n";
      }
      //return 1;
    }
    if (ans.has_value()) {
      assert(check(*ans));
    }

    cout << n << " " << m << " OK" << endl;
  }
#endif
}
