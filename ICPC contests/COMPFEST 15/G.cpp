// https://codeforces.com/contest/1866/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/* Find the minimum index for witch f is true or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(vector<ull> As, vector<ull> Ds) {
  ull N = As.size();

  ull max_A = 0;
  vector<vector<pair<ull, ull>>> starts(N);
  fore(i, 0, N) {
    ull s = Ds[i] > i ? 0 : i - Ds[i];
    ull e = min(i + Ds[i], N - 1);
    starts[s].push_back({e, As[i]});
    max_A = max(max_A, As[i]);
  }

  function<bool(ull)> can = [&](ull k) {
    rpriority_queue<pair<ull, ull>> pq;

    fore(i, 0, N) {
      for (auto [e, a] : starts[i]) {
        pq.push({e, a});
      }

      ull here = 0;
      while (!pq.empty()) {
        auto [e, a] = pq.top();
        pq.pop();
        if (e < i) {
          return false;
        }
        if (here + a <= k) {
          here += a;
        } else {
          pq.push({e, a - (k - here)});
          break;
        }
      }
    }

    return pq.empty();
  };

  ull ans = binary_search(can, 0, max_A);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<ull> As(N), Ds(N);
  for (ull& a : As) {
    cin >> a;
  }
  for (ull& d : Ds) {
    cin >> d;
  }

  auto ans = solve(As, Ds);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}

/*

Búsqueda binaria

Hacer el can de forma greedy tratando de poner todo lo mas antes posible
Usar priority queue para implementarlo eficientemente


*/