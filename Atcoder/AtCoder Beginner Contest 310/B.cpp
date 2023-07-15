// https://atcoder.jp/contests/abc310/tasks/abc310_b

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(ull M, vector<ull> Ps, vector<vector<ull>> Fss) {
  ull N = Ps.size();
  vector<vector<bool>> functions(N, vector<bool>(M, false));

  fore(i, 0, N) {
    fore(j, 0, Fss[i].size()) {
      functions[i][Fss[i][j]] = true;
    }
  }

  fore(i, 0, N) {
    fore(j, 0, N) {
      if (i != j && Ps[i] >= Ps[j]) {
        bool valid = true;
        for (ull f : Fss[i]) {
          if (!functions[j][f]) {
            valid = false;
            break;
          }
        }
        if (valid) {
          if (Ps[i] > Ps[j] || Fss[j].size() > Fss[i].size()) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vector<ull> Ps(N);
  vector<vector<ull>> Fss(N);
  fore(i, 0, N) {
    ull C;
    cin >> Ps[i] >> C;
    Fss[i] = vector<ull>(C);
    fore(j, 0, C) {
      cin >> Fss[i][j];
      Fss[i][j]--;
    }
  }

  if (solve(M, Ps, Fss)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
