// https://codeforces.com/gym/100801

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

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

template<typename T>
struct priority_dqueue {
  set<T> s;

  void push(T x) {
    s.insert(x);
  }
  T front() const {
    return *s.begin();
  }
  T back() const {
    return *s.rbegin();
  }
  void pop_front() {
    s.erase(s.begin());
  }
  void pop_back() {
    s.erase(prev(s.end()));
  }

  ull size() const {
    return s.size();
  }
  bool empty() {
    return s.empty();
  }
};

pair<vu, vuu> solve(ull n, ull k, const vuu& edges) {

  vector<vu> adj(n);
  vu indeg(n);

  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    indeg[v]++;
  }

  priority_dqueue<ull> pdq;

  fore(u, 0, n) {
    if (indeg[u] == 0) {
      pdq.push(u);
    }
  }

  priority_queue<ull> to_add;
  vuu add;

  vu ord;

  while (true) {
    while (k > 0 && pdq.size() > 1) {
      ull u = pdq.front();
      pdq.pop_front();

      to_add.push(u);
      k--;
      indeg[u]++;
    }

    if (pdq.size() > 1) {
      ull u = pdq.front();
      pdq.pop_front();
      ord.push_back(u);
    } else if (!pdq.empty() && !to_add.empty()) {
      ull u = pdq.front();
      ull v = to_add.top();
      if (k == 0 || u > v) {
        pdq.pop_front();
        ord.push_back(u);
      } else {
        to_add.pop();
        add.push_back({ord.back(), v});
        ord.push_back(v);
        pdq.pop_front();
        to_add.push(u);
        k--;
        indeg[u]++;
      }
    } else if (!pdq.empty()) {
      ull u = pdq.front();
      pdq.pop_front();
      ord.push_back(u);
    } else if (!to_add.empty()) {
      ull v = to_add.top();
      to_add.pop();
      add.push_back({ord.back(), v});
      ord.push_back(v);
    } else {
      break;
    }

    ull v = ord.back();
    for (ull w : adj[v]) {
      indeg[w]--;
      if (indeg[w] == 0) {
        pdq.push(w);
      }
    }
  }

  return {ord, add};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);
#endif

  ull n, m, k;
  cin >> n >> m >> k;
  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    --u, --v;
  }


  auto [ord, add] = solve(n, k, edges);
  for (ull a : ord) {
    cout << a + 1 << ' ';
  }
  cout << '\n';
  cout << add.size() << '\n';
  for (auto [u, v] : add) {
    cout << u + 1 << ' ' << v + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
