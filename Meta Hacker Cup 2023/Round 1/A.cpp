// https://www.facebook.com/codingcompetitions/hacker-cup/2023/round-1/problems/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef vector<double> vd;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

double solve1(vu Xs) {
  sort(Xs.begin(), Xs.end());
  ull N = Xs.size();

  double d1 = (double)(Xs[1] + Xs[0])/2.0;
  double d2 = (double)(Xs[N-1] + Xs[N-2])/2.0;

  if (N != 5) {
    return d2 - d1;
  }

  double d3 = (double)(Xs[2] + Xs[0])/2.0;
  double d4 = (double)(Xs[N-1] + Xs[N-3])/2.0;

  return max(d2 - d3, d4 - d1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu Xs(N);
    fore(j, 0, N) {
      cin >> Xs[j];
    }

    auto ans = solve1(Xs);
    cout << setprecision(20);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
