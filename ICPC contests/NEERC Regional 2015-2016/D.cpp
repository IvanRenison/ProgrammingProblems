// https://codeforces.com/gym/100851

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint inf = 1 << 30;

struct Problem {
  uint n;

  Problem* left;
  Problem* right;
  uint split_a, split_b;
  vu dists_a, dists_b;

  uint diagonal_size(uint a, uint b) {
    if (a > b) {
      swap(a, b);
    }
    uint ans0 = b - a;
    uint ans1 = a + n - b;
    uint ans = min(ans0, ans1);
    return ans;
  }

  Problem(uint n, vuu& diagonals) : n(n) {
    assert(diagonals.size() + 3 == n);
    if (n <= 3) {
      return;
    }

    uint large_diag = 0;
    uint size_large_diag = 0;
    fore(i, 0, n - 3) {
      auto& [a, b] = diagonals[i];
      if (a > b) {
        swap(a, b);
      }
      uint d = diagonal_size(a, b);
      if (d > size_large_diag) {
        large_diag = i;
        size_large_diag = d;
      }
    }

    tie(split_a, split_b) = diagonals[large_diag];
    if (split_a > split_b) {
      swap(split_a, split_b);
    }

    vector<vu> adj(n);
    fore(u, 0, n) {
      adj[u].push_back((u + 1) % n);
      adj[(u + 1) % n].push_back(u);
    }
    for (auto [u, v] : diagonals) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    dists_a = vu(n, inf), dists_b = vu(n, inf);
    {
      vu q = {split_a};
      dists_a[split_a] = 0;
      for (uint i = 0; i < q.size(); i++) {
        uint u = q[i];
        for (uint v : adj[u]) {
          if (dists_a[v] == inf) {
            dists_a[v] = dists_a[u] + 1;
            q.push_back(v);
          }
        }
      }
    }
    {
      vu q = {split_b};
      dists_b[split_b] = 0;
      for (uint i = 0; i < q.size(); i++) {
        uint u = q[i];
        for (uint v : adj[u]) {
          if (dists_b[v] == inf) {
            dists_b[v] = dists_b[u] + 1;
            q.push_back(v);
          }
        }
      }
    }

    uint left_n = left_pos(n - 1) + 1;
    uint right_n = right_pos(split_b) + 1;

    vuu left_diagonals, right_diagonals;
    for (auto [a, b] : diagonals) {
      if (a != split_a || b != split_b) {
        if (in_left(a) && in_left(b)) {
          left_diagonals.push_back({left_pos(a), left_pos(b)});
        } else {
          assert(in_right(a) && in_right(b));
          right_diagonals.push_back({right_pos(a), right_pos(b)});
        }
      }
    }

    left = new Problem(left_n, left_diagonals);
    right = new Problem(right_n, right_diagonals);
  }

  bool in_left(uint x) {
    return x <= split_a || x >= split_b;
  }
  bool in_right(uint x) {
    return split_a <= x && x <= split_b;
  }

  uint left_pos(uint x) {
    assert(in_left(x));
    if (x <= split_a) {
      return x;
    } else {
      return x - split_b + 1 + split_a;
    }
  }
  uint right_pos(uint x) {
    assert(in_right(x));
    return x - split_a;
  }

  uint query(uint x, uint y) {
    if (x == y) return 0;
    if (n <= 3) {
      return 1;
    }

    if (in_left(x) && in_left(y)) {
      uint ans = left->query(left_pos(x), left_pos(y));
      return ans;
    } else if (in_right(x) && in_right(y)) {
      uint ans = right->query(right_pos(x), right_pos(y));
      return ans;
    } else {
      uint ans_a = dists_a[x] + dists_a[y];
      uint ans_b = dists_b[x] + dists_b[y];
      uint ans = min(ans_a, ans_b);
      return ans;
    }
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
    freopen("distance.in", "r",stdin);
    freopen("distance.out","w",stdout);
#endif

  uint n;
  cin >> n;
  vuu diagonals(n - 3);
  for (auto& [a, b] : diagonals) {
    cin >> a >> b;
    a--, b--;
  }

  Problem p(n, diagonals);

  uint q;
  cin >> q;
  while (q--) {
    uint x, y;
    cin >> x >> y;
    x--, y--;
    uint ans = p.query(x, y);
    cout << ans << '\n';
  }
}
