// https://www.facebook.com/codingcompetitions/hacker-cup/2023/round-1/problems/C2

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
  ull N = Ss.size();

  vector<bool> press(N, false);
  ull count = 0;
  fore(i, 0, N) {
    if (Ss[i] == 1) {
      press[i] = true;
      count++;
      for (ull j = i; j < N; j += i + 1) {
        Ss[j] = 1 - Ss[j];
      }
    }
  }

  ull ans = 0;

  for (ull B : Bs) {
    if (press[B]) {
      count--;
      press[B] = false;
    } else {
      count++;
      press[B] = true;
    }
    ans += count;
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
      Bs[j]--;
    }

    auto ans = solve1(Ss, Bs);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
