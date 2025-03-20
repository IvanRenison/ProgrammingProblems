// https://codeforces.com/contest/2070/problem/C

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

/* struct Seg {
  ull cost;
  char color;
  ull pos, prev, next;

  bool operator<(const Seg& o) const {
    return tie(cost, pos) < tie(o.cost, o.pos);
  }
}; */



ull solve(ull k, string& s, vu& as) {
  ull n = s.size();

  auto can = [&](ull lim) -> bool {
    string s2;
    vu as2;
    fore(i, 0, n) {
      if (as[i] > lim) {
        s2.push_back(s[i]);
        as2.push_back(as[i]);
      }
    }

    ull segs = s2[0] == 'B';
    fore(i, 1, s2.size()) {
      if (s2[i-1] == 'R' && s2[i] == 'B') {
        segs++;
      }
    }

    return segs <= k;
  };

  ull l = 0, r = *max_element(ALL(as));

  if (can(0)) {
    return 0;
  }

  while (l + 1 < r) {
    ull m = (l + r) / 2;

    if (can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
 /*  bool hasB = false;
  for (char c : s) {
    if (c == 'B') {
      hasB = true;
      break;
    }
  }

  if (!hasB) {
    return 0;
  }

  vector<Seg> segs;
  segs.push_back({as[0], s[0], inf, inf});
  fore(i, 1, n) {
    if (s[i] == s[i-1]) {
      segs.back().cost += as[i];
    } else {
      segs.back().next = segs.size();
      segs.push_back({as[i], s[i], segs.size(), segs.size() - 1, inf});
    }
  }

  set<Seg> pq;
  for (Seg& seg : segs) {
    if (seg.color == 'B' || (seg.prev != inf && seg.next != inf)) {
      pq.insert(seg);
    }
  }

  assert(pq.size() % 2 == 1);

  ull ans = 0;

  while (pq.size() / 2 + 1 > k) {
    auto it = pq.begin();
    Seg seg = *it;
    pq.erase(it);

    ans += seg.cost;

    if (seg.prev == inf) {

    }
    pq.erase(segs[seg.prev]);
  }

  seg.prev */

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve(k, s, as);
    cout << ans << '\n';
  }

}
