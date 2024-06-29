// https://codeforces.com/gym/102861/problem/K

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()

const ull inf = 1ull << 60;

/** Author: Simon Lindholm
 * Date: 2016-08-27
 * License: CC0
 * Source: own work
 * Description: Solves Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily.
 *  Returns rank, or -1 if no solutions. Destroys A$ and b$.
 * Time: O(n^2 m)
 * Status: bruteforce-tested for n, m <= 4
 */
typedef bitset<101> bs;
ll solveLinear(vector<bs>& A, vi& b, bs& x, ll m) {
  ll n = SZ(A), rank = 0, br;
  assert(m <= SZ(x));
  vi col(m); iota(ALL(col), 0);
  fore(i,0,n) {
    for (br=i; br<n; ++br) if (A[br].any()) break;
    if (br == n) {
      fore(j,i,n) if(b[j]) return -1;
      break;
    }
    ll bc = (ll)A[br]._Find_next(i-1);
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    fore(j,0,n) if (A[j][i] != A[j][bc]) {
      A[j].flip(i); A[j].flip(bc);
    }
    fore(j,i+1,n) if (A[j][i]) {
      b[j] ^= b[i];
      A[j] ^= A[i];
    }
    rank++;
  }

  x = bs();
  for (ll i = rank; i--;) {
    if (!b[i]) continue;
    x[col[i]] = 1;
    fore(j,0,i) b[j] ^= A[j][i];
  }
  return rank; // (multiple solutions if rank < m)
}

bool solve(ull N, const vuu& edges) {
  vector<vu> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<bs> A(N);
  vi b(N);

  fore(i, 0, N) {
    for (ull u : adj[i]) {
      A[i][u] = 1;
    }
    if (adj[i].size() % 2 == 0) {
      b[i] = 1;
    } else {
      A[i][i] = 1;
    }
  }

  bs x;
  ll ans = solveLinear(A, b, x, N);

  return ans != -1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vuu edges(M);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--; v--;
  }

  bool ans = solve(N, edges);
  if (ans) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

}
