// https://codeforces.com/contest/1895/problem/E

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


vi general_game(ull n, vii& edges) {
  vector<vu> adj_back(n);
  vu deg(n);

  for (auto [u, v] : edges) {
    //cerr << u << ' ' << v << '\n';
    adj_back[v].push_back(u);
    deg[u]++;
  }

  vi ans(n, 0);
  vu s;
  fore(u, 0, n) {
    if (deg[u] == 0) {
      s.push_back(u);
      ans[u] = 1; // Winner
    }
  }

  while (!s.empty()) {
    ull u = s.back();
    s.pop_back();

    if (ans[u] == -1) { // u is loser
      for (ull v : adj_back[u]) {
        if (ans[v] == 0) {
          ans[v] = 1; // Winner
          s.push_back(v);
        }
      }
    } else { // u is winner
      assert(ans[u] == 1);
      for (ull v : adj_back[u]) {
        if (ans[v] == 0) {
          deg[v]--;
          if (deg[v] == 0) {
            ans[v] = -1; // Loser
            s.push_back(v);
          }
        }
      }
    }
  }

  return ans;
}


template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

uuu solve(vu axs, vu ays, vu bxs, vu bys) {
  ull n = axs.size(), m = bxs.size();

  vuuu axyis(n), bxyis(m);
  fore(i, 0, n) {
    axyis[i] = {axs[i], ays[i], i};
  }
  fore(i, 0, m) {
    bxyis[i] = {bxs[i], bys[i], i};
  }

  sort(ALL(axyis)), sort(ALL(bxyis));

  vuu ayis(n), byis(m);
  fore(i, 0, n) {
    auto [ax, ay, ai] = axyis[i];
    ayis[i] = {ay, ai};
  }
  fore(i, 0, m) {
    auto [bx, by, bi] = bxyis[i];
    byis[i] = {by, bi};
  }

  RMQ<uu> a_rmq(ayis), b_rmq(byis);

  vu wins_a(n, inf), wins_b(m, inf);

  fore(i, 0, n) {
    ull ay = ays[i];

    ull j = upper_bound(ALL(bxyis), uuu{ay, inf, inf}) - bxyis.begin();
    if (j < m) {
      auto [by, k] = b_rmq.query(j, m);
      wins_a[i] = k;
    }
  }

  fore(i, 0, m) {
    ull by = bys[i];

    ull j = upper_bound(ALL(axyis), uuu{by, inf, inf}) - axyis.begin();
    if (j < n) {
      auto [ay, k] = a_rmq.query(j, n);
      wins_b[i] = k;
    }
  }

  vii edges;
  fore(i, 0, n) {
    if (wins_a[i] < m) {
      edges.push_back({i, wins_a[i] + n});
    }
  }
  fore(i, 0, m) {
    if (wins_b[i] < n) {
      edges.push_back({i + n, wins_b[i]});
    }
  }

  vi ans_game = general_game(n + m, edges);

  ull w = 0, d = 0, l = 0;
  fore(i, 0, n) {
    w += ans_game[i] == 1;
    d += ans_game[i] == 0;
    l += ans_game[i] == -1;
  }

  return {w, d, l};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu axs(n), ays(n);
    for (ull& ax : axs) {
      cin >> ax;
      ax--;
    }
    for (ull& ay : ays) {
      cin >> ay;
      ay--;
    }
    ull m;
    cin >> m;
    vu bxs(m), bys(m);
    for (ull& bx : bxs) {
      cin >> bx;
      bx--;
    }
    for (ull& by : bys) {
      cin >> by;
      by--;
    }

    auto [w, d, l] = solve(axs, ays, bxs, bys);
    cout << w << ' ' << d << ' ' << l << '\n';
  }

}
