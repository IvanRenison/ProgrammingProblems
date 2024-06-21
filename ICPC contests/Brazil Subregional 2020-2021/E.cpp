// https://codeforces.com/gym/102861/problem/E

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

#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;


vector<vu> treeJump(const vu& P){
  ll on = 1, d = 1;
  while(on < SZ(P)) on *= 2, d++;
  vector<vu> jmp(d, P);
  fore(i,1,d) fore(j,0,SZ(P))
    jmp[i][j] = jmp[i-1][jmp[i-1][j]];
  return jmp;
}

ll jmp(vector<vu>& tbl, ll nod, ll steps){
  fore(i,0,SZ(tbl))
    if(steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}


vu solve(const vu& As, const vu& Bs, const vuuu& parties) {
  ull N = As.size(), M = parties.size();

  vector<vu> suns(N);
  fore(i, 1, N) {
    suns[Bs[i]].push_back(i);
  }

  vector<vu> tbl = treeJump(Bs);

  vector<vuu> new_parties(N);

  fore(i, 0, M) {
    auto [O, L, R] = parties[i];
    ull d = 0;
    while (O != 0 && As[Bs[O]] < R) {
      if (tbl.size() > d + 1 && As[tbl[d + 1][O]] < R) {
        d++;
      } else {
        O = tbl[d][O];
        d = 0;
      }
    }

    new_parties[O].push_back({L, i});
  }

  Tree<uu> current_parties;
  vu ans(N);

  function<void(ull)> dfs = [&](ull u) {
    for (auto [L, i] : new_parties[u]) {
      current_parties.insert({L, i});
    }

    ull A = As[u];

    ull k = current_parties.order_of_key({A, inf});

    ans[u] = k;

    for (ull v : suns[u]) {
      dfs(v);
    }

    for (auto [L, i] : new_parties[u]) {
      current_parties.erase({L, i});
    }
  };

  dfs(0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vu As(N), Bs(N);
  fore(i, 0, N) {
    cin >> As[i] >> Bs[i];
    As[i]--, Bs[i]--;
  }
  vuuu parties(M);
  for (auto& [O, L, R] : parties) {
    cin >> O >> L >> R;
    O--, L--;
  }

  vu ans = solve(As, Bs, parties);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

}
