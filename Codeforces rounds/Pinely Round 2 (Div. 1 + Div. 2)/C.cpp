// https://codeforces.com/contest/1863/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull MEX(const vector<ull>& as) {
  ull n = as.size();
  vector<bool> bs(n + 1, false);
  fore(i, 0, n) {
    bs[as[i]] = true;
  }
  fore(i, 0, n + 1) {
    if (!bs[i]) {
      return i;
    }
  }
  return n;
}

vector<ull> solve1(ull k, vector<ull>& as) {
  ull n = as.size();

  ull mex = MEX(as);
  as.push_back(mex);

  k = k % (n + 1);

  vector<ull> ans(n);
  fore(i, 0, n) {
    ans[i] = as[(i + (n + 1) - k) % (n + 1)];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vector<ull> as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(k, as);
    fore(j, 0, n) {
      cout << ans[j] << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}

/*
Example of first round:

5 3 0 4 2 1 6 9 10 8 (MEX = 7)
7 3 0 4 2 1 6 9 10 8 (MEX = 5)
7 5 0 4 2 1 6 9 10 8 (MEX = 3)
7 5 3 4 2 1 6 9 10 8 (MEX = 0)
7 5 3 0 2 1 6 9 10 8 (MEX = 4)
7 5 3 0 4 1 6 9 10 8 (MEX = 2)
7 5 3 0 4 2 6 9 10 8 (MEX = 1)
7 5 3 0 4 2 1 9 10 8 (MEX = 6)
7 5 3 0 4 2 1 6 10 8 (MEX = 9)
7 5 3 0 4 2 1 6 9 8 (MEX = 10)
7 5 3 0 4 2 1 6 9 10 (MEX = 8)

It's a rotation of the original array, but with the MEX element at the end.


*/
