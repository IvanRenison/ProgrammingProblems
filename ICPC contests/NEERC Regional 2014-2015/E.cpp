// https://codeforces.com/gym/100553

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define ALL(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef long double ld;
typedef vector<ld> vd;
typedef vector<bool> vb;

ll toPos(char c) {
  if (c == 'R') return 0;
  if (c == 'P') return 1;
  else return 2;
}

char toChar(ll i) {
  if (i <= -1 || i >= 3) {
    return '?';
  }
  return "RPS"[i];
}

struct Node {
  ll c;
  array<ll, 3> v;
};

ll w(ll i) {
  return (i + 1) % 3;
}

vector<Node> solve(vector<Node>& g) {
  ll n = g.size();

  vector<Node> ans = {{-1, {-1, -1, -1}}};
  ans.reserve(n * n * 2);

  auto play = [&](ll i, ll u, vi& vis) -> ii { // El está en i y yo en u, retorna {en que estado queda el, en cual quedo yo}
    assert(u < ans.size());
    assert(i < n);

    auto [c_i, rps_i] = g[i];
    auto& [c_u, rps_u] = ans[u];

    if (vis[i] != -1) {
      c_u = ans[vis[i]].c;
      rps_u = ans[vis[i]].v;
      ll j = rps_i[c_u];
      ll v = rps_u[c_i];
      assert(v != -1);
      return {j, v};
    }
    vis[i] = u;

    if (c_u == -1) {
      assert(rps_u[0] == -1 && rps_u[1] == -1 && rps_u[2] == -1);
      c_u = w(c_i);
      rps_u[c_i] = ans.size();
      ll j = rps_i[c_u];
      ll v = ans.size();
      ans.push_back({-1, {-1, -1, -1}});
      return {j, v};
    } else if (c_u == w(c_i)) {
      ll j = rps_i[c_u];
      ll& v = rps_u[c_i];
      if (v == -1) {
        v = ans.size();
        ans.push_back({-1, {-1, -1, -1}});
      }
      return {j, v};
    } else if (rps_u[c_i] != -1) {
      ll j = rps_i[c_u];
      ll v = rps_u[c_i];
      vis[i] = -1;
      return {j, v};
    } else {
      vis[i] = -1;
      rps_u[c_i] = ans.size();
      ll v = ans.size();
      ans.push_back({-1, {-1, -1, -1}});
      ll j = rps_i[c_u];
      return {j, v};
    }
  };

  fore(i, 0, n) {
    vi vis(n, -1);
    ll j = i, u = 0;
    fore(k, 0, 2 * n + 5) {
      if (k <= n) {
        fill(ALL(vis), -1);
      }
      tie(j, u) = play(j, u, vis);
    }
  }

  for (auto& [c, rps] : ans) {
    if (c == -1) {
      c = 0;
    }
    for (ll& x : rps) {
      if (x == -1) {
        x = 0;
      }
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("epic.in", "r", stdin);
  freopen("epic.out", "w", stdout);
#endif

  ll n;
  cin >> n;
  vector<Node> g(n);
  for (auto& [i, rps] : g) {
    char c;
    ll r, p, s;
    cin >> c >> r >> p >> s;
    r--, p--, s--;
    i = toPos(c);
    rps = {r, p, s};
  }
  vector<Node> ans = solve(g);
  cout << ans.size() << '\n';
  for (auto [c, rps] : ans) {
    auto [r, p, s] = rps;
    cout << toChar(c) << ' ' << r + 1 << ' ' << p + 1 << ' ' << s + 1 << '\n';
  }
}
