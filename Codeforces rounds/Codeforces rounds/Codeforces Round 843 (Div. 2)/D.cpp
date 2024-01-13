// https://codeforces.com/contest/1775/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;

const ull MAXA = 3e5;

/* For each number until N get the smallest prime that divides it */
vu small_primes(MAXA + 1);
void sieve(void) {
  for (ull i = 1; i < MAXA + 1; i++) {
    if (i % 2 == 0) {
      small_primes[i] = 2;
    } else {
      small_primes[i] = i;
    }
  }

  for (ull i = 3; i * i < MAXA + 1; i += 2) {
    if (small_primes[i] == i) {
      for (ull j = i * i; j < MAXA + 1; j += i) {
        if (small_primes[j] == j) {
          small_primes[j] = i;
        }
      }
    }
  }
}

vu primes(ull x) {
  vu ans;
  while (x > 1) {
    ull p = small_primes[x];
    ans.push_back(p);
    while (x % p == 0) {
      x /= p;
    }
  }
  return ans;
}

optional<vu> solve(const vu& as, ull s, ull t) {
  ull n = as.size();

  if (s == t) {
    return {{s}};
  }

  if (as[s] == 1 || as[t] == 1) {
    return {};
  }

  if (as[s] == as[t]) {
    return {{s, t}};
  }

  vector<vu> adj(n + MAXA + 1);

  fore(i, 0, n) {
    ull a = as[i];

    vu ps = primes(a);
    for (ull p : ps) {
      adj[i].push_back(n + p);
      adj[n + p].push_back(i);
    }
  }

  vu fathers(n + MAXA + 1, inf);
  queue<ull> q;
  q.push(s);
  fathers[s] = s;

  while (!q.empty()) {
    ull u = q.front();
    q.pop();

    if (u == t) {
      break;
    }

    for (ull v : adj[u]) {
      if (fathers[v] == inf) {
        fathers[v] = u;
        q.push(v);
      }
    }
  }

  if (fathers[t] == inf) {
    return {};
  }

  vu ans;

  for (ull u = t; u != s; u = fathers[u]) {
    if (u < n) {
      ans.push_back(u);
    }
  }
  ans.push_back(s);

  reverse(all(ans));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  sieve();

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }
  ull s, t;
  cin >> s >> t;
  s--, t--;

  auto ans = solve(as, s, t);

  if (ans.has_value()) {
    cout << ans->size() << '\n';;
    for (ull a : *ans) {
      cout << a + 1 << ' ';
    }
  } else {
    cout << "-1";
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
