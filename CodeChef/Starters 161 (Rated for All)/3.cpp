// https://www.codechef.com/problems/TMPTMP

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

ii intersect(ii r0, ii r1) {
  return {max(r0.first, r1.first), min(r0.second, r1.second)};
}

bool empty(ii r) {
  return r.first >= r.second;
}

ull count(vi& As, ll x) {
  ull N = As.size();

  ull cnt = 0;
  ii range = {As[0] - x, As[0] + x + 1};

  fore(i, 1, N) {
    ull A = As[i];

    ii this_range = {A - x, A + x + 1};

    range = intersect(range, this_range);

    if (empty(range)) {
      cnt++;
      range = this_range;
    }
  }

  return cnt;
}

ull solve(ull K, vi& As) {
  ull N = As.size();

  ull l = 0, r = 1e9 + 1;

  if (count(As, 0) <= K) {
    return 0;
  }

  while (l + 1 < r) {
    ll m = (l + r) / 2;
    if (count(As, m) <= K) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    ull N, K;
    cin >> N >> K;
    vi As(N);
    fore(i, 0, N) {
      cin >> As[i];
    }


    auto ans = solve(K, As);
    cout << ans << '\n';
  }

}
