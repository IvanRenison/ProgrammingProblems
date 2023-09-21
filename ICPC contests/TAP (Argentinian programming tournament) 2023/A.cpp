// https://codeforces.com/gym/104603/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

vu solve(vu As, vu Es) {
  ull N = As.size(), M = Es.size();

  vu Es_ = {Es[0]};
  fore(i, 1, M) {
    ull E = Es[i];
    if (E < Es_.back()) {
      Es_.push_back(E);
    }
  }

  vu ans(N);
  fore(i, 0, N) {
    ull A = As[i];

    while (Es_.back() <= A) {
      auto j_it = upper_bound(Es_.rbegin(), Es_.rend(), A);
      j_it--;
      ull E = *j_it;

      A = A % E;
    }

    ans[i] = A;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;

  vu As(N), Es(M);
  for (ull& A : As) {
    cin >> A;
  }
  for (ull& E : Es) {
    cin >> E;
  }

  auto ans = solve(As, Es);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
