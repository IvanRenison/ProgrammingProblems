// https://codeforces.com/gym/101047/problem/M
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

optional<vector<ull>> solve1(vector<bool>& cs) {
  ull N = cs.size();
  vector<ull> ans;
  vector<bool> taken(N, false);

  fore(i, 0, N) {
    if (cs[i]) {
      ans.push_back(i);
      taken[i] = true;
      if (i == N - 1) {
        return ans;
      }
      cs[i + 1] = !cs[i + 1];
    } else {
      break;
    }
  }

  for (ull i = N - 1; i < N; i--) {
    if (taken[i]) {
      return ans;
    }
    if (cs[i]) {
      ans.push_back(i);
      taken[i] = true;
      if (i == 0) {
        return ans;
      }
      cs[i - 1] = !cs[i - 1];
    } else {
      break;
    }
  }

  fore(i, 0, N) {
    if (taken[i] || !cs[i]) {
      continue;
    }

    ans.push_back(i);
    taken[i] = true;
    if (i > 0) {
      cs[i - 1] = !cs[i - 1];
    }
    if (i + 1 < N) {
      cs[i + 1] = !cs[i + 1];
    }
    for (ull j = i - 1; j < N; j--) {
      if (taken[j]) {
        break;
      }
      if (!cs[j]) {
        return {};
      }
      taken[j] = true;
      ans.push_back(j);
      if (j > 0) {
        cs[j - 1] = !cs[j - 1];
      }
    }
  }

  if (ans.size() == N) {
    return ans;
  }
  return {};
}

int main() {
  FIN;

  ull T;
  cin >> T;
  while (T--) {
    ull N;
    cin >> N;
    vector<bool> cs(N);
    fore(i, 0, N) {
      char a;
      cin >> a;
      cs[i] = a == 'D';
    }

    auto ans = solve1(cs);
    if (ans.has_value()) {
      cout << "Y\n";
      for (ull a : *ans) {
        cout << a + 1 << ' ';
      }
      cout << "\n";
    } else {
      cout << "N\n";
    }
  }

  return 0;
}