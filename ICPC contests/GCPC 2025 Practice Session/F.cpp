//

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


vu solve(ull n, vuuu& idcs, vu& ws) {
  ull m = idcs.size(), q = ws.size();

  vector<vuu> edges_dc(n - 1);

  for (auto [i, d, c] : idcs) {
    edges_dc[i].push_back({d, c});
  }

  ull t = 0;
  for (auto& dcs : edges_dc) {
    sort(ALL(dcs));
    vuu new_dcs = {dcs[0]};
    for (auto [d, c] : dcs) {
      if (c > new_dcs.back().second) {
        new_dcs.push_back({d, c});
      }
    }
    dcs = new_dcs;
    t += dcs[0].first;
  }

  vu ruta(n - 1, 0);

  vector<tuple<ull, bool, ull>> events; // wight, {true iff edges, false iff car}, index
  fore(i, 0, n - 1) {
    for (auto [d, c] : edges_dc[i]) {
      events.push_back({c, true, i});
    }
  }
  fore(i, 0, q) {
    events.push_back({ws[i], false, i});
  }

  sort(ALL(events));

  vu ans(q, inf);

  for (auto [w, b, i] : events) {
    if (b) { // edge
      if (ruta[i] + 1 == edges_dc[i].size()) {
        break;
      } else {
        t += edges_dc[i][ruta[i] + 1].first - edges_dc[i][ruta[i]].first;
        ruta[i]++;
      }
    } else { // car
      ans[i] = t;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  vuuu idcs(m);
  for (auto& [i, d, c] : idcs) {
    cin >> i >> d >> c;
    i--;
  }
  ull q;
  cin >> q;
  vu ws(q);
  for (ull& w : ws) {
    cin >> w;
  }

  vu ans = solve(n, idcs, ws);
  for (ull a : ans) {
    if (a == inf) {
      cout << "impossible\n";
    } else {
      cout << a << '\n';
    }
  }

}
