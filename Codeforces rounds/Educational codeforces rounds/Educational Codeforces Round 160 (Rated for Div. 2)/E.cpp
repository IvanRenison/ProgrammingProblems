// https://codeforces.com/contest/1913/problem/E

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) x.begin(), x.end()


/** Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
  ll N;
  vector<vi> ed, red;
  vector<VL> cap, flow, cost;
  vi seen;
  VL dist, pi;
  vector<ii> par;

  MCMF(ll N) :
    N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
    seen(N), dist(N), pi(N), par(N) {}

  void addEdge(ll from, ll to, ll cap, ll cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
    ed[from].push_back(to);
    red[to].push_back(from);
  }

  void path(ll s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0; ll di;

    __gnu_pbds::priority_queue<pair<ll, ll>> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});

    auto relax = [&](ll i, ll cap, ll cost, ll dir) {
      ll val = di - pi[i] + cost;
      if (cap && val < dist[i]) {
        dist[i] = val;
        par[i] = {s, dir};
        if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
        else q.modify(its[i], {-dist[i], i});
      }
    };

    while (!q.empty()) {
      s = q.top().second; q.pop();
      seen[s] = 1; di = dist[s] + pi[s];
      for (ll i : ed[s]) if (!seen[i])
        relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
      for (ll i : red[s]) if (!seen[i])
        relax(i, flow[i][s], -cost[i][s], 0);
    }
    rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
  }

  pair<ll, ll> maxflow(ll s, ll t) {
    ll totflow = 0, totcost = 0;
    while (path(s), seen[t]) {
      ll fl = INF;
      for (ll p,r,x = t; tie(p,r) = par[x], x != s; x = p)
        fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
      totflow += fl;
      for (ll p,r,x = t; tie(p,r) = par[x], x != s; x = p)
        if (r) flow[p][x] += fl;
        else flow[x][p] -= fl;
    }
    rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
    return {totflow, totcost};
  }

  // If some costs can be negative, call this before maxflow:
  void setpi(ll s) { // (otherwise, leave this out)
    fill(all(pi), INF); pi[s] = 0;
    ll it = N, ch = 1; ll v;
    while (ch-- && it--)
      rep(i,0,N) if (pi[i] != INF)
        for (ll to : ed[i]) if (cap[i][to])
          if ((v = pi[i] + cost[i][to]) < pi[to])
            pi[to] = v, ch = 1;
    assert(it >= 0); // negative cost cycle
  }
};


optional<ull> solve(const vector<vu>& M, const vu& As, const vu& Bs) {
  ull n = M.size(), m = M[0].size();

  ull sum_As = 0, sum_Bs = 0;
  fore(i, 0, n) {
    sum_As += As[i];
  }
  fore(j, 0, m) {
    sum_Bs += Bs[j];
  }
  if (sum_As != sum_Bs) return {};

  MCMF mcmf(n * m + n + m + 2);
  ull total_sum = 0;

  fore(i, 0, n) {
    fore(j, 0, m) {
      mcmf.addEdge(n * m + i, i * m + j, 1, 1 - M[i][j]);
      mcmf.addEdge(i * m + j, n * m + n + j, 1, 0);
      total_sum += M[i][j];
    }
  }

  fore(i, 0, n) {
    if (As[i] > 0) {
      mcmf.addEdge(n * m + n + m, n * m + i, As[i], 0);
    }
  }

  fore(j, 0, m) {
    if (Bs[j] > 0) {
      mcmf.addEdge(n * m + n + j, n * m + n + m + 1, Bs[j], 0);
    }
  }

  auto [flow, cost] = mcmf.maxflow(n * m + n + m, n * m + n + m + 1);

  if ((ull)flow != sum_As) return {};

  return cost + total_sum - (flow - cost);
}

/* optional<ull> force(const vector<vu>& M, const vu& As, const vu& Bs) {
  ull n = M.size(), m = M[0].size();

  ull sum_As = 0, sum_Bs = 0;
  fore(i, 0, n) {
    sum_As += As[i];
  }
  fore(j, 0, m) {
    sum_Bs += Bs[j];
  }

  ull ans = inf;

  fore(x, 0, (1 << (n * m))) {
    vector<vu> Mx(n, vu(m));
    ull diff = 0;
    fore(i, 0, n) {
      fore(j, 0, m) {
        Mx[i][j] = (x & (1 << (i * m + j))) ? 1 : 0;
        if (Mx[i][j] != M[i][j]) diff++;
      }
    }

    if (diff < ans) {
      bool valid = true;

      fore(i, 0, n) {
        ull sum_Mi = 0;
        fore(j, 0, m) {
          sum_Mi += Mx[i][j];
        }
        if (sum_Mi != As[i]) {
          valid = false;
          break;
        }
      }

      fore(j, 0, m) {
        ull sum_Mj = 0;
        fore(i, 0, n) {
          sum_Mj += Mx[i][j];
        }
        if (sum_Mj != Bs[j]) {
          valid = false;
          break;
        }
      }

      if (valid) {
        ans = diff;
      }
    }

  }

  if (ans != inf) {
    return ans;
  } else {
    return {};
  }
} */

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;
  vector<vu> Mss(n, vu(m));
  fore(i, 0, n) fore(j, 0, m) cin >> Mss[i][j];
  vu As(n), Bs(m);
  fore(i, 0, n) cin >> As[i];
  fore(i, 0, m) cin >> Bs[i];

  auto ans = solve(Mss, As, Bs);
  if (ans) cout << *ans << '\n';
  else cout << -1 << '\n';

/*   fore(_, 0, 100) {
    ull n = 4, m = 4;

    vector<vu> Mss(n, vu(m));
    fore(i, 0, n) fore(j, 0, m) Mss[i][j] = rand() % 2;

    vu As(n), Bs(m);
    fore(i, 0, n) As[i] = rand() % m;
    fore(i, 0, m) Bs[i] = rand() % n;

    auto ans1 = solve(Mss, As, Bs);
    auto ans2 = force(Mss, As, Bs);

    if (ans1 != ans2) {
      cerr << "ERROR:\n";
      cerr << n << ' ' << m << '\n';
      fore(i, 0, n) {
        fore(j, 0, m) {
          cerr << Mss[i][j] << ' ';
        }
        cerr << '\n';
      }
      fore(i, 0, n) cerr << As[i] << ' ';
      cerr << '\n';
      fore(i, 0, m) cerr << Bs[i] << ' ';
      cerr << '\n';

      cerr << "ans1 = " << ans1.value_or(-1) << '\n';
      cerr << "ans2 = " << ans2.value_or(-1) << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
