// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(vector<ull> as, vector<ull> qs) {
  vector<ull> piles(1000000);
  ull n = as.size();
  ull m = qs.size();

  ull i = 0;
  fore(j, 0, n) {
    ull a = as[j];
    fore(k, 0, a) {
      piles[i] = j;
      i++;
    }
  }

  vector<ull> ans(m);
  fore(i, 0, m) {
    ull q = qs[i];
    ans[i] = piles[q];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;

  cin >> n;
  vector<ull> as(n);
  fore(i, 0, n) {
    ull a;
    cin >> a;
    as[i] = a;
  }

  ull m;
  cin >> m;

  vector<ull> qs(m);
  fore(i, 0, m) {
    ull q;
    cin >> q;
    qs[i] = q - 1;
  }

  vector<ull> ans = solve(as, qs);
  for (ull a : ans) {
    cout << a + 1 << "\n";
  }

  return EXIT_SUCCESS;
}
