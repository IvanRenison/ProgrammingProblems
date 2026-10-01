// https://codeforces.com/gym/106682/problem/C
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef vector<ull> vu;

ll inf = 1ll << 60;

ll solve(vi& As, vi& Bs) {
  ull N = As.size();

  vi dpA(N); // dpA[y] = Brian jugó y, le toca a Agus, el máximo puntaje que puede obtener
  vi dpB(N); // dpB[y] = Agus jugó y, le toca a Brian, el mínimo puntaje que puede obtener

  vi dpA_mins(N); // dpA_mins[i] = min entre i...N-1
  vi dpA_maxs(N);
  vi dpB_mins(N);
  vi dpB_maxs(N);

  auto upd = [&](ull i) {
    if (i == N - 1) {
      dpA_mins[i] = dpA_maxs[i] = dpA[i];
      dpB_mins[i] = dpB_maxs[i] = dpB[i];
    } else {
      dpA_mins[i] = min(dpA[i], dpA_mins[i + 1]);
      dpA_maxs[i] = max(dpA[i], dpA_maxs[i + 1]);
      dpB_mins[i] = min(dpB[i], dpB_mins[i + 1]);
      dpB_maxs[i] = max(dpB[i], dpB_maxs[i + 1]);
    }
  };

  dpA[N-1] = Bs[N-1];
  dpB[N-1] = As[N-1];

  upd(N-1);

  for (ull i = N - 1; i--; ) {
    dpA[i] = max({
      dpB_maxs[i+1], // Jugar
      min(dpA_mins[i+1], Bs[i]), // No jugar
      Bs[i]
    });

    dpB[i] = min({
      dpA_mins[i+1],
      max(dpB_maxs[i+1], As[i]),
      As[i]
    });

    upd(i);
  }

  ll ans = max(
    dpB_maxs[0], // Jugar
    min(0ll, dpA_mins[0])
  );

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ull N;
  cin >> N;
  vi As(N), Bs(N);
  for (ll& A : As) {
    cin >> A;
  }
  for (ll& B : Bs) {
    cin >> B;
  }

  auto ans = solve(As, Bs);
  cout << ans << '\n';

}

