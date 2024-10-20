// https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-2/problems/C

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

typedef unsigned int ull;
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

ull diff(ull a, ull b) {
  return a > b ? a - b : b - a;
}


const ull max_RC = 800 * 800;

struct Val {
  array<ull, max_RC> cnt;
  ull sum;

  void add(ull x) {
    cnt[x]++;
    sum++;
  }
  void remove(ull x) {
    cnt[x]--;
    sum--;
  }

  ull query(ull x) {
    return sum - cnt[x];
  }
};

ull count_le(const vector<vu>& Bss, ull x) {
  ull R = Bss.size(), C = Bss[0].size();

  vector<Val> dp0(C), dp1(C);

  ull ans = 0;

  fore(i, 0, R) {
    fore(j, 0, C) {

      if (i > x) {
        fore(j1, j <= x ? 0 : j - x, j + 1) { // Sacar
          dp0[j].remove(Bss[i - x - 1][j1]);
        }
      }

      fore(j1, j <= x ? 0 : j - x, j + 1) { // Agregar
        dp0[j].add(Bss[i][j1]);
      }

      ans += dp0[j].query(Bss[i][j]);
    }

    for (ull j = C; j--; ) {

      if (i > x) {
        fore(j1, j + 1, min(C, j + x + 1)) { // Sacar
          dp1[j].remove(Bss[i - x - 1][j1]);
        }
      }

      ans += dp1[j].query(Bss[i][j]);

      fore(j1, j + 1, min(C, j + x + 1)) { // Agregar
        dp1[j].add(Bss[i][j1]);
      }
    }
  }

  return ans * 2;
}

ull solve(ull K, const vector<vu>& Bss) {
  ull R = Bss.size(), C = Bss[0].size();

  ull l = 0, r = max(R, C);

  while (l + 1 < r) {
    ull m = (l + r) / 2;
    ull c = count_le(Bss, m);
    if (c > K) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

ull force(ull K, const vector<vu>& Bss) {
  ull R = Bss.size(), C = Bss[0].size();

  vi points;
  fore(i0, 0, R) fore(j0, 0, C) {
    fore(i1, 0, R) fore(j1, 0, C) if (i0 != i1 || j0 != j1) {
      if (Bss[i0][j0] != Bss[i1][j1]) {
        points.push_back(max(diff(i0, i1), diff(j0, j1)));
      }
    }
  }

  sort(ALL(points));

  if (K >= points.size()) {
    return max(R, C);
  }

  return points[K];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST

  omp_set_num_threads(16);

  ull t;
  cin >> t;

  vector<pair<ull, vector<vu>>> inputs(t);

  fore(tc, 0, t) {
    ull R, C, K;
    cin >> R >> C >> K;
    K--;
    vector<vu> Bss(R, vu(C));
    fore(i, 0, R) {
      fore(j, 0, C) {
        cin >> Bss[i][j];
        Bss[i][j]--;
      }
    }
    inputs[tc] = {K, Bss};
  }

  vector<ull> ans(t);

  #pragma omp parallel for
  for (ull tc = 0; tc < t; tc++) {
    auto [K, Bss] = inputs[tc];
    ans[tc] = solve(K, Bss);
  }

  for (ull tc = 0; tc < t; tc++) {
    cout << "Case #" << tc + 1 << ": ";
    cout << ans[tc] << '\n';
  }

#else
  fore(_, 0, 1) {
    ull R = rand() % 20, C = rand() % 20, K = rand() % (2 * R * C);
    vector<vu> Bss(R, vu(C));
    fore(i, 0, R) {
      fore(j, 0, C) {
        Bss[i][j] = rand() % 10;
      }
    }

    ull ans = solve(K, Bss);
    cout << ans << '\n';
    ull ansf = force(K, Bss);
    if (ans != ansf) {
      cout << "ERROR:\n1\n";
      cout << R << ' ' << C << ' ' << K + 1 << '\n';
      fore(i, 0, R) {
        fore(j, 0, C) {
          cout << Bss[i][j] + 1 << ' ';
        }
        cout << '\n';
      }
      cout << ans << " != " << ansf << '\n';
      return 1;
    }
  }
#endif
}
