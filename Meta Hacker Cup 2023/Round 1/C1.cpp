//

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

ull solve1(vu& Ss, vu& Bs) {
  ull N = Ss.size(), Q = Bs.size();

  sort(Bs.begin(), Bs.end());

  vu adds(N);

  ull j = 0;
  fore(i, 1, N+1) {
    if (i < Bs[j]) {
      continue;
    }

    ull B = Bs[j];
    ull count = 0;

    while (j < Q && Bs[j] == B) {
      j++;
      count++;
    }

    for (ull k = i; k <= N; k += i) {
      adds[k-1] += count;
    }
  }

  fore(i, 0, N) {
    Ss[i] = (Ss[i] + adds[i]) % 2;
  }

  ull ans = 0;
  fore(i, 0, N) {
    if (Ss[i] != 0) {
      ans++;
      Ss[i] = 0;
      for(ull k = i + 1; k <= N; k += i + 1) {
        Ss[k-1] = 1 - Ss[k-1];
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu Ss(N);
    fore(j, 0, N) {
      char c;
      cin >> c;
      Ss[j] = c - '0';
    }
    ull Q;
    cin >> Q;
    vu Bs(Q);
    fore(j, 0, Q) {
      cin >> Bs[j];
    }

    auto ans = solve1(Ss, Bs);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
