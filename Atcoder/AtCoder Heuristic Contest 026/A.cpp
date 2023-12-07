// https://atcoder.jp/contests/ahc026/tasks/ahc026_a

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

const ull n = 200, m = 10;


vuu solve(const vector<vu>& stacks) {

  vector<basic_string<ull>> ss(m);
  fore(i, 0, m) {
    for (ull box : stacks[i]) {
      ss[i] += box;
    }
  }

  vuu ans;

  fore(u, 0, n) {

    fore(i, 0, m) {
      fore(j, 0, ss[i].size()) {
        if (ss[i][j] == u) {
          if (j == ss[i].size() - 1) {
            ss[i].pop_back();
            ans.push_back({u, -1});
          } else {

            ull best_i = (i + 1) % m;
            fore(i_, 0, m) if (i_ != i) {
              if (ss[best_i].size() != 0 && (ss[i_].size() == 0 || ss[i_].back() > ss[best_i].back())) {
                best_i = i_;
              }
            }

            ans.push_back({ss[i][j + 1], best_i});
            // Move slice from ss[i][j + 1:] to ss[best_i]
            ss[best_i] += ss[i].substr(j + 1);
            ss[i].erase(j);
            ans.push_back({u, -1});
          }
          goto next;
        }
      }
    }

    next:;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n_, m_;
  cin >> n_ >> m_;
  vector<vu> stacks(m, vu(n/m));
  for(vu& stack : stacks) {
    for(ull& box : stack) {
      cin >> box;
      box--;
    }
  }

  auto ans = solve(stacks);
  for(auto [v, i] : ans) {
    cout << v + 1 << " " << (i == -1 ? 0 : i + 1) << '\n';
  }

  return EXIT_SUCCESS;
}
