//https://codeforces.com/group/4zVk9dZl6Q/contest/390414/problem/L

#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

vector<ull> solve(ull p, vector<ull> ts) {
  ull n = ts.size();

  vector<pair<ull, ull>> ti(n);
  fore(i, 0, n) {
    ti[i] = {ts[i], i};
  }

  sort(ALL(ti));

  vector<ull> ans(n);

  priority_queue<ull, vector<ull>, greater<ull>> wating;
  ull time = 0;
  ull i = 0;

  while (i < n || wating.size() > 0) {
    if (wating.size() > 0) {
      ull j = wating.top();
      wating.pop();

      time += p;
      ans[j] = time;

      while (i < n && ti[i].first <= time) {
        wating.push(ti[i].second);
        i++;
      }
    } else {
      wating.push(ti[i].second);
      time = ti[i].first;
      i++;
      while (i < n && ti[i].first <= time) {
        wating.push(ti[i].second);
        i++;
      }
    }
  }

  return ans;
}

int main(void) {
  FIN;

  ull n, p;

  cin >> n >> p;

  vector<ull> ts(n);

  fore(i, 0, n) {
    cin >> ts[i];
  }

  vector<ull> ans = solve(p, ts);

  for (ull a : ans) {
    cout << a << ' ';
  }

  cout << '\n';

  return 0;
}
