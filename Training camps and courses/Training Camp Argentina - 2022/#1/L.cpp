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

struct Tree {
  typedef bool T;
  static constexpr T unit = false;
  T f(T a, T b) { return a || b; } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

vector<ull> solve(ull p, vector<ull> ts) {
  ull n = ts.size();

  vector<pair<ull, ull>> ti(n);
  fore(i, 0, n) {
    ti[i] = {ts[i], i};
  }

  sort(ALL(ti));

  vector<ull> ans(n);

  priority_queue<ull, vector<ull>, greater<ull>> wating;
  queue<ull> in_queue;
  Tree in_queue_t(n);
  ull time = 0;
  ull i = 0;

  while (i < n || in_queue.size() > 0 || wating.size() > 0) {
    if (in_queue.size() > 0) {
      ull j = in_queue.front();
      in_queue.pop();

      time += p;
      ans[j] = time;

      while (i < n && ti[i].first <= time) {
        if (in_queue_t.query(0, ti[i].second)) {
          wating.push(ti[i].second);
        } else {
          in_queue.push(ti[i].second);
          in_queue_t.update(ti[i].second, true);
        }
        i++;
      }

      in_queue_t.update(j, false);

    } else if (wating.size() > 0) {
      ull j = wating.top();
      wating.pop();

      in_queue.push(j);
      in_queue_t.update(j, true);

    } else {
      wating.push(ti[i].second);
      time = ti[i].first;
      i++;
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
