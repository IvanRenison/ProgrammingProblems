// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x)  (ll(x.size()))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

ll dist2(ll x0, ll y0, ll x1, ll y1) {
  return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
}

/** Author: Iván Renison
 * Date: 2024-03-05
 * License: CC0
 * Source: notebook el vasito
 * Description: Segment tree with ability to add values of large intervals, and compute the sum of intervals.
 * Ranges are [s, e).
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Tree st(n);
 *  st.init(x);
 *  st.upd(s, e, v);
 *  st.query(s, e);
 * Status: Tested on SPOJ HORRIBLE, stress-tested a bit
 */
typedef vector<int> T; typedef pair<vector<int>, vector<int>> L; // T: data type, L: lazy type
// neutrals
const T tneut = {}; const L lneut = {};
/* T f(const T& a, const T& b) {
  if (a.empty()) return b;
  if (b.empty()) return a;
  return {};
} // operation */
// new st according to lazy
T app(const T& v, const L& l) {
  T ans;
  for (int x : v) {
    if (!count(ALL(l.second), x)) {
      ans.push_back(x);
    }
  }
  for (int x : l.first) {
    ans.push_back(x);
  }

  return ans;
}
// cumulative effect of lazy
L comb(const L& a, const L& b) {
  L ans;
  for (int x : a.first) {
    if (!count(ALL(b.second), x)) {
      ans.first.push_back(x);
    }
  }
  for (int x : b.first) {
    if (!count(ALL(a.second), x)) {
      ans.first.push_back(x);
    }
  }

  for (int x : a.second) {
    if (!count(ALL(b.first), x)) {
      ans.second.push_back(x);
    }
  }
  for (int x : b.second) {
    if (!count(ALL(a.first), x)) {
      ans.second.push_back(x);
    }
  }

  return ans;
}

struct Tree { // example: range sum with range addition
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
/*   Tree(vector<T> &a) : n(SZ(a)), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ll k, ll s, ll e, vector<T> &a) {
    lazy[k] = lneut;
    if (s + 1 == e) { st[k] = a[s]; return; }
    ll m = (s + e) >> 1;
    init((k<<1), s, m, a), init((k<<1)|1, m, e, a);
    st[k] = f(st[(k<<1)], st[(k<<1)|1]);
  } */
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return; // if neutral, nothing to do
    st[k] = app(st[k], lazy[k]);
    if (s + 1 < e) { // propagate to children
      lazy[(k<<1)] = comb(lazy[(k<<1)], lazy[k]);
      lazy[(k<<1)|1] = comb(lazy[(k<<1)|1], lazy[k]);
    }
    lazy[k] = lneut; // clear node lazy
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L& v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v); // accumulate lazy
      push(k, s, e);
      return;
    }
    ll m = (s + e) >> 1;
    upd((k<<1), s, m, a, b, v), upd((k<<1)|1, m, e, a, b, v);
    //st[k] = f(st[(k<<1)], st[(k<<1)|1]);
  }
/*   T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) >> 1;
    return f(query((k<<1), s, m, a, b),query((k<<1)|1, m, e, a, b));
  } */
  T& pointQuery(ll k, ll s, ll e, ll a) {
    if (s >= a+1 || e <= a) assert(false);
    push(k, s, e);
    if (s >= a && e <= a+1) return st[k];
    ll m = (s + e) >> 1;
    if (m <= a) {
      return pointQuery((k<<1)|1, m, e, a);
    } else {
      return pointQuery((k<<1), s, m, a);
    }
  }
  T& pointQuery(ll a) {
    return pointQuery(1, 0, n, a);
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  //T query(ll a, ll b) { return query(1, 0, n, a, b); }
};

void solve(const viii& events) {
  ll n = events.size();

  vi xs(n);
  fore(i, 0, n) {
    auto [t, x, y] = events[i];
    xs[i] = x;
  }

  sort(ALL(xs));
  xs.erase(unique(ALL(xs)), xs.end());

  Tree circles(SZ(xs));

  fore(i, 0, n) {
    auto [t, x, y] = events[i];
    if (t == 1) {
      ll x_comp0 = lower_bound(ALL(xs), x - y + 1) - xs.begin();
      ll x_comp1 = lower_bound(ALL(xs), x + y) - xs.begin();
      circles.upd(x_comp0, x_comp1, {{(int)i}, {}});
    } else {
      ll x_comp = lower_bound(ALL(xs), x) - xs.begin();

      ll j = -1;

      for (ll j2 : circles.pointQuery(x_comp)) {
        auto [_, x1, y1] = events[j2];

        ll d = dist2(x, y, x1, y1);
        if (d < y1 * y1) {
          j = j2;
          break;
        }
      }

      cout << (j == -1 ? -1 : j + 1) << '\n';
      if (j != -1) {
        auto [_, xj, yj] = events[j];
        ll x_comp0 = lower_bound(ALL(xs), xj - yj + 1) - xs.begin();
        ll x_comp1 = lower_bound(ALL(xs), xj + yj) - xs.begin();
        circles.upd(x_comp0, x_comp1, {{}, {(int)j}});
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  viii events(n);
  for (auto& [t, x, y] : events) {
    cin >> t >> x >> y;
  }
  solve(events);
}