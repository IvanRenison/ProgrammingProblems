// https://cses.fi/problemset/task/2165

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


typedef array<ull, 3> St;
typedef vector<pair<ull, ull>> Ans;

ull odder(ull i, ull j) {
  bool bs[3] = {false, false, false};
  bs[i] = true, bs[j] = true;
  fore(k, 0, 3) {
    if (!bs[k]) {
      return k;
    }
  }

}

void move(St& st, ull from, ull to, ull n, Ans& ans) {
  assert(st[from] >= n);

  if (n == 0) {
    return;
  }

  ull od = odder(from, to);

  move(st, from, od, n - 1, ans);
  st[from]--, st[to]++, ans.push_back({from, to});
  move(st, od, to, n-1, ans);

}


Ans solve(ull n) {
  St st = {n, 0, 0};
  Ans ans;
  move(st, 0, 2, n, ans);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;

  auto ans = solve(n);
  cout << ans.size() << '\n';
  for (auto [a, b] : ans) {
    cout << a + 1 << ' ' << b + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
