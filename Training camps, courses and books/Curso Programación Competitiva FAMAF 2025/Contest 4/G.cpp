// https://codeforces.com/group/Xaa6lwRoge/contest/635590/problem/G

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

string solve(vector<string>& names) {
  ull n = names.size();

  vuu edges;

  fore(i, 0, n - 1) {
    string& name0 = names[i], name1 = names[i+1];

    ull l0 = name0.size(), l1 = name1.size();

    bool diff = false;
    fore(j, 0, min(l0, l1)) {
      ull c0 = name0[j] - 'a', c1 = name1[j] - 'a';
      if (c0 != c1) {
        edges.push_back({c0, c1});
        diff = true;
        break;
      }
    }

    if (!diff && l1 < l0) {
      return "Impossible";
    }
  }

  vector<vi> adj(26);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
  }

  vi topo = topoSort(adj);

  if (topo.size() != 26) {
    return "Impossible";
  }

  string ans;
  for (ull c : topo) {
    ans.push_back('a' + c);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vector<string> names(n);
  for (string& name : names) {
    cin >> name;
  }

  auto ans = solve(names);
  cout << ans << '\n';

}
