// https://codeforces.com/gym/105297/problem/E
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef pair<ll,ll> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll,ll,ll,ll,ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;

const ld inf = numeric_limits<ld>::max();
const ld eps = 1e-11;

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

bool eq(ld a, ld b) {
  return abs(a - b) < eps;
}

ld ymin(ld a, ld b, ld c) {
  ld x = - b / (2 * a);
  return a * x * x + b*x + c;
}

/*
a0 t² + b0 t + c0 = a1 t² + b1 t + c1
(a0 - a1) t² + (b0 - b1) t + (c0 - c1) = 0
*/
vector<ld> intersection(ld a0, ld b0, ld c0, ld a1, ld b1, ld c1) {
  ld a = a0 - a1, b = b0 - b1, c = c0 - c1;

  if (a == 0) {
    if (b == 0) {
      return {};
    } else {
      return {-c / b};
    }
  } else {
    ld d = b * b - 4 * a * c;
    if (d < -eps) {
      return {};
    } else if (d > eps) {
      ld x1 = (-b + sqrt(d)) / (2 * a);
      ld x2 = (-b - sqrt(d)) / (2 * a);
      return {x1, x2};
    } else {
      return {-b / (2 * a)};
    }
  }
}

ld solve(ll N, viiiii& edges) {
  ll M = edges.size();

  vector<viiii> adj(N);
  for (auto [x, y, a, b, c] : edges) {
    adj[x].push_back({y, a, b, c});
    adj[y].push_back({x, a, b, c});
  }


  vector<ld> inter_;
  fore(e, 0, M) {
    fore(f, 0, e) {
      auto [x0, y0, a0, b0, c0] = edges[e];
      auto [x1, y1, a1, b1, c1] = edges[f];
      vector<ld> ts = intersection(a0, b0, c0, a1, b1, c1);
      for (ld t : ts) {
        inter_.push_back(t);
      }
    }
  }

  sort(ALL(inter_));
  vector<ld> inters;
  if (!inter_.empty()) {
    inters.push_back(inter_[0]);
  }
  fore(i, 1, inter_.size()) {
    if (!eq(inter_[i], inter_[i - 1])) {
      inters.push_back(inter_[i]);
    }
  }

  vector<ld> times;
  if (inters.empty()) {
    times.push_back(0);
  } else {
    times.push_back(inters[0] - 1);
    fore(i, 0, inters.size() - 1) {
      ld t = (inters[i] + inters[i + 1]) / 2;
      times.push_back(t);
    }
    times.push_back(inters.back() + 1);
  }

  ld ans = inf;

  for (ld t : times) {
    vi edges_ids(M);
    iota(ALL(edges_ids), 0);

    sort(ALL(edges_ids), [&](ll e, ll f) {
      auto [xe, ye, ae, be, ce] = edges[e];
      auto [xf, yf, af, bf, cf] = edges[f];

      ld c_e = (ld)ae * t * t + (ld)be * t + (ld)ce;
      ld c_f = (ld)af * t * t + (ld)bf * t + (ld)cf;

      return c_e < c_f || (c_e == c_f && e < f);
    });

    ll a = 0, b = 0, c = 0;
    UF uf(N);

    for (ll e : edges_ids) {
      auto [x, y, ae, be, ce] = edges[e];
      if (uf.join(x, y)) {
        a += ae;
        b += be;
        c += ce;
      }
    }

    ld this_ans = ymin(a, b, c);
    ans = min(ans, this_ans);
  }


  return ans;
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M;
  cin >> N >> M;
  viiiii edges(M);
  for (auto& [x, y, a, b, c] : edges) {
    cin >> x >> y >> a >> b >> c;
    x--, y--;
  }

  ld ans = solve(N, edges);
  cout << setprecision(10) << fixed;
  cout << ans << '\n';

}
