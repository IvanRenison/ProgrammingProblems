// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef long long ll;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

/** Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers x$ and y$, such that ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If a$ and b$ are coprime, then x$ is the inverse of a \pmod{b}$.
 */
ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}

ll invert(ll a, ll mod) {
  ll x, y, g = euclid(a, mod, x, y);
  assert(g == 1);
  return ((x + mod) % mod);
}

// Find min x such than a x ≡ b (mod m)
optional<ull> lin_mod(ull a, ull b, ull m) {

  if (a == 0) {
    if (b == 0) {
      return 0;
    } else {
      return {};
    }
  }

  ull g = gcd(a, m);
  if (b % g != 0) {
    return {};
  }

  a /= g, b /= g, m /= g;

  ll ans = invert(a, m);
  return (ans * b) % m;
}


uu solve(ull N, const vu& Bs, const vector<vu>& Ass) {
  ull R = Bs.size(), K = Ass[0].size();

  vector<vu> As_sums(R, vu(K + 1));
  fore(i, 0, R) {
    fore(j, 0, K) {
      As_sums[i][j + 1] = (As_sums[i][j] + Ass[i][j]) % N;
    }
  }

  auto intersection_direct = [&](ull i, ull j, ull t) -> optional<ull> {
    ull Ai_sum = As_sums[i][K];
    ull Aj_sum = As_sums[j][K];
    ull delta = (N + Ai_sum - Aj_sum) % N;
    ull pi = (Bs[i] + (t / K) * Ai_sum + As_sums[i][t % K]) % N;
    ull pj = (Bs[j] + (t / K) * Aj_sum + As_sums[j][t % K]) % N;
    ull diff = (N + pj - pi) % N;

    optional<ull> tt = lin_mod(delta, diff, N);
    if (!tt.has_value()) {
      return {};
    } else {
      return t + *tt * K;
    }
  };

  auto intersection = [&](ull i, ull j, ull t) -> optional<ull> {
    ull ans = inf;
    fore(k, 0, K) {
      optional<ull> this_ans = intersection_direct(i, j, t + k);
      if (this_ans.has_value()) {
        ans = min(ans, *this_ans);
      }
    }
    if (ans == inf) {
      return {};
    } else {
      return ans;
    }
  };

  vb vis(R, false);
  rpriority_queue<uu> events;
  events.push({0, 0});
  ull last_t = 0;
  while (!events.empty()) {
    auto [t, i] = events.top();
    events.pop();

    if (vis[i]) {
      continue;
    }

    vis[i] = true;
    last_t = t;

    fore(j, 0, R) if (!vis[j]) {
      optional<ull> nt = intersection(i, j, t);
      if (nt.has_value()) {
        events.push({*nt, j});
      }
    }
  }

  ull count = accumulate(ALL(vis), 0ull);

  return {count, last_t};
}

uu force(ull N, const vu& Bs, const vector<vu>& Ass) {
  ull R = Bs.size(), K = Ass[0].size();

  vb vis(R, false);
  vu pos = Bs;

  fore(i, 0, R) {
    if (pos[i] == pos[0]) {
      vis[i] = true;
    }
  }

  ull last_t = 0;

  fore(t, 0, 1e6) {
    fore(i, 0, R) {
      pos[i] += Ass[i][t % K];
      pos[i] %= N;
    }

    fore(i, 0, R) {
      if (vis[i]) {
        fore(j, 0, R) if (j != i) {
          if (pos[i] == pos[j] && !vis[j]) {
            vis[j] = true;
            last_t = t + 1;
          }
        }
      }
    }
  }

  ull count = accumulate(ALL(vis), 0ull);

  return {count, last_t};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull N, R, K;
  cin >> N >> R >> K;
  vu Bs(R);
  for (ull& B : Bs) {
    cin >> B;
    B--;
  }
  vector<vu> Ass(R, vu(K));
  for (vu& As : Ass) {
    for (ull& A : As) {
      cin >> A;
    }
  }

  auto [m, t] = solve(N, Bs, Ass);
  cout << m << ' ' << t << '\n';
#else
  fore(_, 0, 100) {
    ull N = rand() % 10 + 2;
    ull R = rand() % 10 + 2;
    ull K = rand() % 10 + 1;

    vu Bs(R);
    for (ull& B : Bs) {
      B = rand() % N;
    }
    vector<vu> Ass(R, vu(K));
    for (vu& As : Ass) {
      for (ull& A : As) {
        A = rand() % N + 1;
      }
    }

    uu ans = solve(N, Bs, Ass);
    uu ansf = force(N, Bs, Ass);
    if (ans != ansf) {
      cerr << N << ' ' << R << ' ' << K << '\n';
      for (ull& B : Bs) {
        cerr << B + 1 << ' ';
      }
      cerr << '\n';
      for (vu& As : Ass) {
        for (ull& A : As) {
          cerr << A << ' ';
        }
        cerr << '\n';
      }
      DBG(ans.first);
      DBG(ans.second);
      DBG(ansf.first);
      DBG(ansf.second);
      return 1;
    }
  }
#endif
}

/*

Intersección entre dos sapos 0 y 1 desde el tiempo t en un múltiplo de K

Posiciones de los sapos:
p0 ≡ (t / K) * a0_sum + a0[:t % K]
p1 ≡ (t / K) * a1_sum + a1[:t % K]

para tt:
p0' ≡ p0 + a0_sum * tt
p1' ≡ p1 + a1_sum * tt

p0 + a0_sum * tt ≡ p1 + a1_sum * tt
p0 - p1 ≡ a1_sum * tt - a0_sum * tt
p0 - p1 ≡ (a1_sum - a0_sum) * tt

*/
