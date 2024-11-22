// https://www.codechef.com/problems/MINMAXSUB

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



ull solveBobLast(vu& Ps) {
  ull N = Ps.size();

  ull ans = 0;
  fore(i, 0, N) {
    ull P = Ps[i];
    ull cost = min(i, N - i - 1);
    if (P > cost) {
      ull this_ans = P - cost;
      ans = max(ans, this_ans);
    }
  }

  return ans;
}

ull solveAliceLast(vu& Ps) {
  ull N = Ps.size();

  vuu Ps_i(N);
  fore(i, 0, N) {
    Ps_i[i] = {Ps[i], i};
  }
  sort(ALL(Ps_i));
  reverse(ALL(Ps_i));

  ull ans = 0;
  ull first_i = Ps_i[0].second, last_i = first_i;

  fore(j, 1, N) {
    auto [P, i] = Ps_i[j];

    ull cost_first = inf, cost_last = inf;
    if (first_i < i) {
      cost_first = N - i - 1 + first_i;
    } else {
      first_i = i;
    }
    if (last_i > i) {
      cost_last = i + N - last_i - 1;
    } else {
      last_i = i;
    }

    ull cost = min(cost_first, cost_last);
    assert(cost < inf);

    if (P > cost) {
      ull this_ans = P - cost;
      ans = max(ans, this_ans);
    }
  }

  return ans;
}

ull solve(vu& Ps) {
  ull N = Ps.size();
  if (N % 2 == 0) {
    return solveAliceLast(Ps);
  } else {
    return solveBobLast(Ps);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu Ps(N);
    for (ull& P : Ps) {
      cin >> P;
      P--;
    }

    auto ans = solve(Ps);
    cout << ans + 1 << '\n';
  }

}
