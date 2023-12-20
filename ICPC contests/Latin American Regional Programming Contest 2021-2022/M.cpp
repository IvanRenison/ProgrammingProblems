// https://codeforces.com/gym/103640/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
#define fore(i, a, b) for (ull i = a; i < b; i++)


optional<vu> solve(vuu TDs) {
  ull N = TDs.size();

  ull time = 0;
  for(auto [T, D] : TDs) {
    time += T;
  }

  vector<bool> used(N, false);
  vu ans(N, -1);

  for(ull i = N - 1; i < N; i--) {
    for(ull j = N - 1; j < N; j--) {
      if (!used[j]) {
        auto [Tj, Dj] = TDs[j];

        if (Dj >= time) {
          used[j] = true;
          ans[i] = j;
          time -= Tj;
          break;
        }
      }
    }

    if (ans[i] == -1) {
      return {};
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vuu TDs(N);
  for(auto& [T, D] : TDs) {
    cin >> T >> D;
  }

  auto ans = solve(TDs);

  if (ans.has_value()) {
    for(ull a : *ans) {
      cout << a + 1 << ' ';
    }
  } else {
    cout << '*';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
