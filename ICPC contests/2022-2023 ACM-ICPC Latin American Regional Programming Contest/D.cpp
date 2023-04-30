// https://codeforces.com/gym/104252/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

static inline vector<pair<bool, bool>>
solve(ull H, ull W, vector<pair<bool, bool>> weather) {
  ull N = weather.size();
  vector<pair<bool, bool>> ans(N);

  fore(i, 0, N) {
    auto [wg, wb] = weather[i];
    if (wg || W == 0) {
      ans[i].first = true;
      H--;
      W++;
    } else {
      ans[i].first = false;
    }

    if (wb || H == 0) {
      ans[i].second = true;
      W--;
      H++;
    } else {
      ans[i].second = false;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, H, W;

  cin >> N >> H >> W;

  vector<pair<bool, bool>> weather(N);

  fore(i, 0, N) {
    char c0, c1;
    cin >> c0 >> c1;
    weather[i] = {c0 == 'Y', c1 == 'Y'};
  }

  vector<pair<bool, bool>> ans = solve(H, W, weather);

  fore(i, 0, N) {
    cout << (ans[i].first ? 'Y' : 'N') << ' ' << (ans[i].second ? 'Y' : 'N')
         << endl;
  }

  return EXIT_SUCCESS;
}
