// https://atcoder.jp/contests/abc301/tasks/abc301_b

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(vector<ull> as) {
  ull n = as.size();

  vector<ull> ans = {as[0]};

  fore(i, 1, n) {
    ull a = as[i];

    ull last = ans.back();

    if (last < a) {
      fore(j, last + 1, a) {
        ans.push_back(j);
      }
    } else {
      for (ull j = last - 1; j > a; j--) {
        ans.push_back(j);
      }
    }

    ans.push_back(a);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vector<ull> as(N);
  fore(i, 0, N) {
    cin >> as[i];
  }

  vector<ull> ans = solve(as);

  for (ull a : ans) {
    cout << a << " ";
  }
  cout << "\n";

  return EXIT_SUCCESS;
}
