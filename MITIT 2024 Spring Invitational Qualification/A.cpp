// https://codeforces.com/gym/105125/problem/A

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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

bool check(ull N, const vuuu& vals, vu ans) {
  ull count = 0;

  for (auto [a, b, c] : vals) {
    count += ans[a] * ans[b] * ans[c];
  }

  return count % 2 == 1;
}


optional<vu> solve(ull N, const vuuu& vals) {
  ull M = SZ(vals);

  map<vu, ull> m;
  fore(i, 0, M) {
    auto [a, b, c] = vals[i];
    vu v = {a};
    if (b != a) {
      v.push_back(b);
    }
    if (c != a && c != b) {
      v.push_back(c);
    }
    sort(ALL(v));
    m[v]++;
  }

  for (auto [v, c] : m) {
    ull tam = SZ(v);
    fore(x, 1, (1 << tam) - 1) {
      vu v2;
      fore(i, 0, tam) {
        if (x & (1 << i)) {
          v2.push_back(v[i]);
        }
      }

      if (m.count(v2)) {
        c += m[v2];
      }
    }
    if (c % 2 == 1) {
      vu ans(N);
      for (ull a : v) {
        ans[a] = 1;
      }
      return ans;
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N, M;
    cin >> N >> M;
    vuuu vals(M);
    fore(j, 0, M) {
      ull a, b, c;
      cin >> a >> b >> c;
      a--, b--, c--;
      vals[j] = {a, b, c};
    }

    auto ans = solve(N, vals);

    if (ans.has_value()) {
      cout << "Yes\n";
      //assert(check(N, vals, ans.value()));
      for (auto& x : ans.value()) {
        cout << x << ' ';
      }
      cout << '\n';
    } else {
      cout << "No\n";
    }
  }

/*   fore(_, 0, 10000) {
    ull N = rand() % 10 + 1;
    ull M = rand() % 10 + 1;

    vuuu vals(M);
    fore(i, 0, M) {
      vu v(3);
      fore(j, 0, 3) {
        v[j] = rand() % N;
      }
      sort(ALL(v));

      vals[i] = {v[0], v[1], v[2]};
    }

    auto ans = solve(N, vals);
    if (ans.has_value()) {
      if (!check(N, vals, ans.value())) {
        cerr << "FAIL\n";
        cerr << N << ' ' << M << '\n';
        for (auto [a, b, c] : vals) {
          cerr << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
        }
        cerr << "ANS\n";
        for (auto x : ans.value()) {
          cerr << x << ' ';
        }
        cerr << '\n';
        return EXIT_FAILURE;
      }
    }
  } */

  return EXIT_SUCCESS;
}
