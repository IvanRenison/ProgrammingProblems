// https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/D2

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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

ull diff(ull x, ull y) {
  return x > y ? x - y : y - x;
}

/** Author: someone on Codeforces and then modified by Iván Renison
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits, joins, queries and updates.
 *  Can also support reversals with the commented REVERSE lines and getting the
 *  position of a node with the PARENT lines.
 * Time: O(\log N)$
 * Status: stress-tested a bit and problem tested
 */
typedef ull T; typedef ull L; // T: data type, L: lazy type
const T tneut = 0; const L lneut = 0; // neutrals
T f(T a, T b) { return a + b; } // operation
// new st according to lazy
T apply(T v, L l, ll len) { return v + l * len; }
// cumulative effect of lazy
L comb(L a, L b) { return a + b; }

struct Node {
  Node *l = 0, *r = 0;
  // Node *p = 0; // PARENT
  T val, acc; L lazy = lneut;
  ll y, c = 1;
  // bool rev = false; // REVERSE
  Node(T val = tneut) : val(val), acc(val), y(rand()) {}
  void recalc() {
    c = 1, acc = tneut;
    if (l) l->push(), acc = f(acc, l->acc), c += l->c;
    acc = f(acc, val);
    if (r) r->push(), acc = f(acc, r->acc), c += r->c;
    // if (l) l->p = this; // PARENT
    // if (r) r->p = this;
  }
  void push() {
    // if (rev) { // REVERSE
    // 	swap(l, r), rev = false;
    // 	if (l) l->rev ^= 1; if (r) r->rev ^= 1;
    // }
    val = apply(val, lazy, 1), acc = apply(acc, lazy, c);
    if (l) l->lazy = comb(l->lazy, lazy);
    if (r) r->lazy = comb(r->lazy, lazy);
    lazy = lneut;
  }
  // void pullAll() { // PARENT
  // 	if (p) p->pullAll();
  // 	push();
  // }

  Node* split(ll k) {
    assert(k > 0);
    if (k >= c) return 0;
    push();
    ll cnt = l ? l->c : 0;
    if (k <= cnt) { // "k <= val" for lower_bound(k)
      Node* nl = l->split(k),* ret = l;
      l = nl;
      recalc();
      swap(*this, *ret);
      return ret;
    } else if (k == cnt + 1) { // k == val
      Node* ret = r;
      r = 0;
      recalc();
      return ret;
    } else {
      Node* ret = r->split(k - cnt - 1); // and just "k"
      recalc(), ret->recalc();
      return ret;
    }
  }
  void merge(Node* ri) {
    if (!ri) return;
    push(), ri->push();
    if (y > ri->y) {
      if (r) r->merge(ri);
      else r = ri;
    } else {
      merge(ri->l);
      ri->l = ri;
      swap(*this, *ri);
    }
    recalc();
  }
  // ll pos() { // In which position I am // PARENT
  // 	pullAll();
  // 	ll ans = l ? l->c : 0;
  // 	if (!p) return ans;
  // 	if (p->r == this) return ans + p->pos() + 1;
  // 	else return p->pos() + 1 - (r ? r->c : 0);
  // }
  T query() { // Query full range
    push();
    return acc;
  }
  T query(ull e) { // Query [0, e)
    Node* ri = split(e);
    T ans = query();
    merge(ri);
    return ans;
  }
  void upd(L v) { lazy = comb(lazy, v); } // Update full range
  // void reverse() { rev = !rev; } // REVERSE

};

uu solve(ull G, const vu& Es) {
  ull N = Es.size();

  ull len = 1;
  Node* st = new Node();

  fore(i, 0, N) {
    ull E = Es[i];

    // Get position
    ull pos;
    if (E + i >= len) {
      pos = E + i;
    } else {
      ull l = E, r = E + i + 1;
      while (l + 1 < r) {
        ull m = (l + r) / 2;

        bool can = E + st->query(m) >= m;
        if (can) {
          l = m;
        } else {
          r = m;
        }
      }
      pos = l;
    }

    while (len <= pos) {
      st->merge(new Node());
      len++;
    }
    if (len == pos + 1) {
      st = st->split(1);
      st->merge(new Node(1));
    } else {
      Node* ri = st->split(pos + 1);
      st = st->split(1);
      st->merge(new Node(1));
      st->merge(ri);
    }
  }

  Node* ri = st->split(G);
  ull ri_sum = ri ? ri->query() : 0;
  ull st_sum = st->query();

  ull ans_i = 0, ans_d = inf;
  if (ri_sum > 0) {
    ull l = 0, r = ri->c + 1;
    while (l + 1 < r) {
      ull m = (l + r) / 2;

      bool can = ri->query(m) > 0;
      if (can) {
        r = m;
      } else {
        l = m;
      }
    }
    ans_i = ri_sum - 1;
    ans_d = l;
  }
  if (st_sum > 0) {
    ull l = 0, r = st->c + 1;
    while (l + 1 < r) {
      ull m = (l + r) / 2;

      bool can = st->query(m) < st_sum;
      if (can) {
        l = m;
      } else {
        r = m;
      }
    }

    if (G - l < ans_d) {
      ans_i = ri_sum;
      ans_d = G - l;
    }
  }

  return {ans_i, ans_d};
}

uu force(ull G, const vu& Es) {
  ull N = Es.size();

  vu vals = {inf};

  function<void(ull, ull)> move = [&](ull x, ull E) {
    assert(vals.size() > x);
    assert(vals[x] != inf);

    if (E == 0) {
      return;
    }

    if (vals.size() == x + 1) {
      vals.push_back(inf);
    }

    if (vals[x + 1] == inf) {
      vals[x + 1] = vals[x];
      vals[x] = inf;
      move(x + 1, E - 1);
    } else {
      move(x + 1, E);
    }
  };

  fore(i, 0, N) {
    vals[0] = i;
    move(0, Es[i]);
  }

  ull ans_i = 0, ans_d = inf;
  fore(x, 0, vals.size()) {
    if (vals[x] != inf) {
      ull d = diff(x, G);
      if (d < ans_d || (d == ans_d && vals[x] < ans_i)) {
        ans_i = vals[x];
        ans_d = d;
      }
    }
  }

  return {ans_i, ans_d};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N, G;
    cin >> N >> G;
    vu Es(N);
    for (ull& E : Es) {
      cin >> E;
    }

    auto [j, d] = solve(G, Es);
    cout << "Case #" << i + 1 << ": " << j + 1 << ' ' << d << '\n';
  }
#else
  fore(_, 0, 10) {
    ull N = 300000; //rand() % 10 + 1;
    vu Es(N);
    for (ull& E : Es) {
      E = rand() % (1000000 - N) + N;
    }

    ull G = rand() % 1000000 + 1;

    uu ans = solve(G, Es);
/*     uu ansf = force(G, Es);
    if (ans != ansf) {
      cout << "FAIL" << endl;
      cout << N << ' ' << G << endl;
      for (ull E : Es) {
        cout << E << ' ';
      }
      cout << endl;
      cout << ans.first << ' ' << ans.second << endl;
      cout << ansf.first << ' ' << ansf.second << endl;
      return 1;
    } */
  }
  cout << "Test passed" << endl;
#endif
}
