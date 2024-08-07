// https://codeforces.com/gym/102861/problem/J

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif
 */
#include <bits/stdc++.h>

#pragma GCC optimize ("Ofast")

#define assert(x) ;

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

// Based on ModularArithmetic of kactl
constexpr ull mod = (1e9 + 7); // Prime number for division to work
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
  }
  Mod operator*(Mod b) const {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) const {
    return x == b.x;
  }
  bool operator!=(Mod b) const {
    return x != b.x;
  }
  bool operator<(Mod b) const {
    return x < b.x;
  }
  bool operator>(Mod b) const {
    return x > b.x;
  }
  bool operator<=(Mod b) const {
    return x <= b.x;
  }
  bool operator>=(Mod b) const {
    return x >= b.x;
  }

  Mod invert(Mod a) const {
    Mod r = a ^ (mod - 2);
    return r;
  }
  Mod operator^(ull e) const {
    Mod r = Mod(1);
    Mod b = *this;
    while (e > 0) {
      if (e & 1) {
        r *= b;
      }
      b *= b;
      e /= 2;
    }
    return r;
  }
  Mod operator/(Mod b) const {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    is >> m.x;
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

template <typename T> ll signum(T val) {
  return (T(0) < val) - (val < T(0));
}

struct Ratio {
  ll num;
  ull den;
  Ratio(ll num = 0, ull den = 1) {
    ull g = gcd((ull)abs(num), den);
    this->num = num / ((ll)g);
    this->den = den / g;
  }

  Ratio operator+(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den + o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator-(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den - o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator*(Ratio o) const {
    return Ratio(num * o.num, den * o.den);
  }
  Ratio operator/(Ratio o) const {
    assert(o.num != 0);
    return Ratio(num * (ll)o.den * signum(o), den * abs(o.num));
  }

  void operator+=(Ratio o) {
    *this = *this + o;
  }
  void operator-=(Ratio o) {
    *this = *this - o;
  }
  void operator*=(Ratio o) {
    *this = *this * o;
  }
  void operator/=(Ratio o) {
    *this = *this / o;
  }

  bool operator==(Ratio o) const {
    return num == o.num && den == o.den;
  }
  bool operator!=(Ratio o) const {
    return !(*this == o);
  }
  bool operator<(Ratio o) const {
    return num * (ll)o.den < o.num * (ll)den;
  }
  bool operator<=(Ratio o) const {
    return *this < o || *this == o;
  }
  bool operator>(Ratio o) const {
    return o < *this;
  }
  bool operator>=(Ratio o) const {
    return o <= *this;
  }

  friend ostream& operator<<(ostream& os, Ratio r) {
    os << r.num;
    if (r.den != 1) {
      os << "/" << r.den;
    }
    return os;
  }
};



typedef pair<Ratio, Ratio> rr;

Mod countInGraph(Ratio a, Ratio b, const vu& counter, const vuu& edges) {
  assert(a != 0);
  ull N = counter.size();

  if (a == Ratio(1) && b == Ratio(0)) {
    fore(i, 0, N) {
      if (counter[i] % 2 == 1) {
        return 0;
      }
    }
    return 1;
  }

  vector<vu> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    if (u != v) {
      adj[v].push_back(u);
    }
  }

  if (a == Ratio(1) && b == Ratio(0)) {

    fore(u, 0, N) {
      assert(adj[u].size() == 1);
      assert(u == adj[u][0]);
      if (counter[u] % 2 != 0) {
        return 0;
      }
    }

    return 1;
  }

  if (a == Ratio(-1)) {
    vb vis(N, false);
    Mod ans = 1;

    fore(u, 0, N) if (!vis[u]) {
      if (adj[u].size() == 0) {
        return 0;
      }
      assert(adj[u].size() == 1);
      ull v = adj[u][0];
      if (v == u) {
        if (counter[u] % 2 == 1) {
          return 0;
        }
        vis[u] = true;
        continue;
      }
      vis[u] = vis[v] = true;
      if (counter[u] != counter[v]) {
        return 0;
      }
      Mod this_ans = Mod(counter[u] + 1);
      ans *= this_ans;
    }

    return ans;
  }

  vb vis(N, false);
  fore(u, 0, N) if (!vis[u]) {
    if (adj[u].size() == 0) {
      return 0;
    }
    assert(adj[u].size() == 1 || adj[u].size() == 2);
    if (adj[u].size() == 2) {
      continue;
    }
    if (adj[u][0] == u) {
      vis[u] = true;
      continue;
    }

    ull c = 0;
    ull v = u;
    while (true) {
      if (counter[v] < c) {
        return 0;
      }
      c = counter[v] - c;
      vis[v] = true;
      if (adj[v].size() == 1) {
        if (vis[adj[v][0]]) {
          break;
        }
        v = adj[v][0];
      } else {
        assert(adj[v].size() == 2);
        if (vis[adj[v][0]]) {
          assert(!vis[adj[v][1]]);
          v = adj[v][1];
        } else {
          v = adj[v][0];
        }
      }
    }

    if (c != 0) {
      return 0;
    }
  }

  return 1;
}

Mod countInGraph(Ratio a, Ratio b, const map<ll, ull>& counter, const set<ii>& edges) {
  ull N = counter.size();
  unordered_map<ll, ull> compression;
  vu counter_compressed(N);
  for (auto [k, c] : counter) {
    ull i = compression.size();
    compression[k] = compression.size();
    counter_compressed[i] = c;
  }

  vuu edges_compressed;
  edges_compressed.reserve(edges.size());
  for (auto [k, c] : edges) {
    edges_compressed.push_back({compression[k], compression[c]});
  }

  Mod ans = countInGraph(a, b, counter_compressed, edges_compressed);
  return ans;
}

Mod force(vi I);

Mod solve(const vi& I) {
  ull N = I.size();

  map<ll, ull> counter;
  for (ll x : I) {
    counter[x]++;
  }

  if (counter.size() == 1) { // Only one point with N/2 repetitions
    return Mod(1);
  }

  if (counter.size() == 2) { // Only for different points maximum
    ull c0 = counter.begin()->second;
    ull c1 = counter.rbegin()->second;
    if (c0 == c1) {
      if (c0 % 2 == 0) {
        return N / 2 + 2;
      } else {
        return N / 2 + 1;
      }
    } else {
      if (c0 % 2 == 1) {
        return Mod(2);
      } else {
        return Mod(3);
      }
    }
  }

  Mod ans = 0;

  ull max_c = 0;
  for (auto [_, c] : counter) {
    max_c = max(max_c, c);
  }
  if (max_c >= N / 2) { // Count vertical or horizontal lines as answers
    ans += 2;
  }
  // Now we don't have to count that vertical and horizontal

  set<rr> lines;

  ll k0 = counter.begin()->first;
  ll k1 = counter.rbegin()->first;

  for (auto [k2, _] : counter) {
    if ((k2 == k0 && counter[k2] == 1) || (k2 == k1 && counter[k2] == 1)) {
      continue;
    }
    for (auto [k3, _] : counter) {
      if ((k3 == k0 && counter[k3] == 1) || (k3 == k1 && counter[k3] == 1) || (k3 == k2 && counter[k3] == 1)) {
        continue;
      }

      vi ks = {k0, k1, k2, k3};
      sort(ALL(ks));
      do {
        ll x0 = ks[0], y0 = ks[1], x1 = ks[2], y1 = ks[3];
        // Line through (x0, y0) and (x1, y1)
        if (x0 != x1 && y0 != y1) { // We know that vertical or horizontal lines are not the answer
          Ratio a = Ratio(y1 - y0) / Ratio(x1 - x0);
          assert(a != 0);
          Ratio b = Ratio(y0) - a * x0;
          lines.insert({a, b});
        }
      } while (next_permutation(ALL(ks)));
    }
  }

  for (auto [a, b] : lines) {
    assert(a != 0);

    auto f = [&](Ratio x) -> Ratio {
      return a * x + b;
    };
    auto inv = [&](Ratio y) -> Ratio {
      return (y - b) / a;
    }; // y = a * x + b iff x = (y - b) / a

    set<ii> edges;
    for (auto [k, _] : counter) {
      bool enter = false;
      {
        ll x = k;
        Ratio y = f(x);
        if (y.den == 1 && counter.count(y.num)) {
          edges.insert(minmax(x, y.num));
          enter = true;
        }
      }
      {
        ll y = k;
        Ratio x = inv(y);
        if (x.den == 1 && counter.count(x.num)) {
          edges.insert(minmax(x.num, y));
          enter = true;
        }
      }

      if (!enter) {
        goto next;
      }
    }

    //Mod this_ans = countInGraph(a, b, counter, edges);
    //cerr << this_ans << '\n';
    ans += countInGraph(a, b, counter, edges);;

    next:;
  }

  return ans;
}

Mod force(vi I) {
  ull N = I.size();

  auto colinear = [&](vii& points) -> bool {
    ull k = points.size();
    if (k <= 2) {
      return true;
    }

    auto [x0, y0] = points[0];
    auto [x1, y1] = points[k - 1];

    if (x0 == x1 && y0 == y1) {
      return true;
    }

    if (x0 == x1) { // Horizontal line
      //cerr << "Horizontal line at " << y0 << ' ';
      fore(i, 2, k) {
        if (points[i].first != x0) {
          return false;
        }
      }
      return true;
    }

    Ratio a = Ratio(y1 - y0) / Ratio(x1 - x0);
    Ratio b = Ratio(y0) - a * x0;
    //cerr << a << ' ' << b << ' ';

    fore(i, 1, k - 1) {
      auto [xi, yi] = points[i];
      Ratio y = a * Ratio(xi) + b;
      if (y.den != 1 || y.num != yi) {
        return false;
      }
    }
    return true;
  };

  set<vii> ans;

  sort(ALL(I));
  do {
    vii points;
    fore(i, 0, N / 2) {
      points.push_back({I[2 * i], I[2 * i + 1]});
      //cerr << I[2 * i] << ' ' << I[2 * i + 1] << "  ";
    }
    sort(ALL(points));
    if (!ans.count(points) && colinear(points)) {
      ans.insert(points);
      //cerr << endl;
    } else if (ans.count(points)) {
      //cerr << "repeated" << endl;
    } else {
      //cerr << "not colinear" << endl;
    }

  } while (next_permutation(ALL(I)));

  return ans.size();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull N;
  cin >> N;
  vi I(N);
  for (ll& k : I) {
    cin >> k;
  }

  Mod ans = solve(I);
  cout << ans << '\n';
#else
  fore(_, 0, 10000) {
    ull N = (rand() % 3) * 2 + 4;
    vi I(N);
    for (ll& k : I) {
      k = rand() % 21 - 10;
    }

    Mod ans = solve(I);
    Mod ansf = force(I);
    if (ans != ansf) {
      cerr << N << '\n';
      for (ll k : I) {
        cerr << k << ' ';
      }
      cerr << '\n';
      DBG(ans);
      DBG(ansf);
      return 1;
    }
  }
#endif
}
