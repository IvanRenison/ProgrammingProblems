// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/I

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: O(\alpha(N))$
 */
struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  bool sameSet(ll a, ll b) { return find(a) == find(b); }
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

optional<ull> solve(ull N, vector<pair<ull, vu>>& ops) {
  sort(ops.begin(), ops.end());

  UF uf(N);

  ull ans = 0;

  for (auto& [C, As] : ops) {
    set<ull> reps;
    for (ull A : As) {
      ull r = uf.find(A);
      reps.insert(r);
    }

    ull n_reps = reps.size();
    ull this_cost = (n_reps - 1) * C;
    ans += this_cost;

    fore(i, 0, As.size() - 1) {
      uf.join(As[i], As[i + 1]);
    }
  }

  ull r = uf.find(0);
  fore(i, 1, N) {
    ull ri = uf.find(i);
    if (ri != r) {
      return {};
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vector<pair<ull, vu>> ops(M);
  for (auto& [C, As] : ops) {
    ull K;
    cin >> K >> C;
    As = vu(K);
    for (ull& A : As) {
      cin >> A;
      A--;
    }
  }

  optional<ull> ans = solve(N, ops);
  if (ans) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }
}
