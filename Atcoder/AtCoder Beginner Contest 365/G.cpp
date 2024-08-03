// https://atcoder.jp/contests/abc365/tasks/abc365_g

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

vu solve(ull N, const vuu& events, const vuu& queries) {
  ull Q = queries.size();

  vector<vu> events_per_node(N);
  for (auto [T, P] : events) {
    events_per_node[P].push_back(T);
  }
  vector<vu> in_times(N);
  fore(i, 0, N) {
    ull k = events_per_node[i].size();
    in_times[i] = vu(k + 1);
    fore(j, 0, k) {
      in_times[i][j + 1] = in_times[i][j];
      if (j % 2 == 1) {
        in_times[i][j + 1] += events_per_node[i][j] - events_per_node[i][j - 1];
      }
    }
  }

  auto in_time = [&](ull i, ull t) -> ull {
    ull k = events_per_node[i].size();
    ull j = lower_bound(ALL(events_per_node[i]), t) - events_per_node[i].begin();
    if (j == k) {
      return in_times[i][k];
    }
    ull ans = in_times[i][j];
    if (j % 2 == 1) {
      ans += t - events_per_node[i][j - 1];
    }
    return ans;
  };

  map<uu, ull> mem;
  vu ans;
  ans.reserve(Q);
  for (auto [A, B] : queries) {
    if (mem.count(minmax(A, B))) {
      ans.push_back(mem[minmax(A, B)]);
    } else {
      if (events_per_node[A].size() > events_per_node[B].size()) {
        swap(A, B);
      }
      ull k = events_per_node[A].size();
      ull this_ans = 0;
      for (ull i = 1; i < k; i += 2) {
        ull t = events_per_node[A][i - 1], nt = events_per_node[A][i];
        this_ans += in_time(B, nt) - in_time(B, t);
      }

      mem[minmax(A, B)] = this_ans;
      ans.push_back(this_ans);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vuu events(M);
  for (auto& [T, P] : events) {
    cin >> T >> P;
    P--;
  }
  ull Q;
  cin >> Q;
  vuu queries(Q);
  for (auto& [A, B] : queries) {
    cin >> A >> B;
    A--, B--;
  }

  vu ans = solve(N, events, queries);
  for (ull x : ans) {
    cout << x << '\n';
  }
}
