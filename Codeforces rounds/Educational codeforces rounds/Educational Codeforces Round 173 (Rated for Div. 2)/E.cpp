// https://codeforces.com/contest/2043/problem/E

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

/** Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than n$ -- nodes reachable
 * from cycles will not be returned.
 * Time: O(|V|+|E|)$
 * Status: stress-tested
 */
vi topoSort(const vector<vi>& g) {
  vi d(SZ(g)), q;
  for (auto& li : g) for (ll x : li) d[x]++;
  fore(i,0,SZ(g)) if (!d[i]) q.push_back(i);
  for (ll j = 0; j < SZ(q); j++) for (ll x : g[q[j]])
    if (!--d[x]) q.push_back(x);
  return q;
}

bool solve1(vector<vb>& A, vector<vb>& B) {
  ull n = A.size(), m = A[0].size();

  vb on(n + m, false);

  vu s;

  fore(i, 0, n) { // Filas
    fore(j, 0, m) {
      if (A[i][j] && ! B[i][j]) {
        s.push_back(i);
      }
    }
  }

  fore(j, 0, m) { // Columnas
    fore(i, 0, n) {
      if (!A[i][j] && B[i][j]) {
        s.push_back(n + j);
      }
    }
  }

  vector<vi> g(n + m);

  while (!s.empty()) {
    ull u = s.back();
    s.pop_back();

    if (!on[u]) {
      on[u] = true;

      if (u < n) {
        fore(j, 0, m) {
          if (B[u][j]) {
            s.push_back(n + j);
            g[u].push_back(n + j);
          }
        }
      } else {
        fore(i, 0, n) {
          if (!B[i][u - n]) {
            s.push_back(i);
            g[u].push_back(i);
          }
        }
      }
    }
  }

  vi order = topoSort(g);
  if (order.size() != n + m) {
    return false;
  } else {
    return true;
  }



}

bool solve(vector<vu>& A, vector<vu>& B) {
  ull n = A.size(), m = A[0].size();

  fore(i, 0, 22) {
    vector<vb> A2(n, vb(m)), B2(n, vb(m));
    fore(j, 0, n) {
      fore(k, 0, m) {
        A2[j][k] = (A[j][k] >> i) & 1;
        B2[j][k] = (B[j][k] >> i) & 1;
      }
    }

    if (!solve1(A2, B2)) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vector<vu> A(n, vu(m)), B(n, vu(m));
    fore(j, 0, n) {
      fore(k, 0, m) {
        cin >> A[j][k];
      }
    }
    fore(j, 0, n) {
      fore(k, 0, m) {
        cin >> B[j][k];
      }
    }

    bool ans = solve(A, B);
    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

}
