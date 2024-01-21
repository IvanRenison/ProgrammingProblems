// https://atcoder.jp/contests/arc170/tasks/arc170_d

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;

/* bool force(vu As, vu Bs) {
  ull N = As.size();

  fore(i, 0, N) {
    ull Ai = As[i];
    bool valid = true;
    fore(j, 0, N) {
      ull Bj = Bs[j];
      bool found = false;
      fore(k, 0, N) if (k != i) {
        ull Ak = As[k];

        vu vs = {Ai, Bj, Ak};
        sort(all(vs));
        if (vs[2] < vs[0] + vs[1]) {
          found = true;
          break;
        }
      }
      if (!found) {
        valid = false;
        break;
      }
    }
    if (valid) {
      return true;
    }
  }

  return false;
} */

bool solve1(vu As, vu Bs) {
  ull N = As.size();

  sort(all(As));
  sort(all(Bs));

  ull found_i = inf;
  fore(i, 0, N) {
    ull Ai = As[i];
    ull B = Bs[0];
    vu vs = {Ai, B};
    sort(all(vs));
    ull v0 = vs[0], v1 = vs[1];

    ull m = v1 - v0 + 1, M = v1 + v0 - 1;
    auto it = lower_bound(all(As), m);
    if (it != As.end()) {
      if (it - As.begin() == i) {
        it++;
      }
      if (it != As.end() && *it <= M) {
        found_i = i;
      }
    }
  }

  if (found_i == inf) {
    return false;
  }

  ull A = As[found_i];

  fore(j, 1, N) {
    ull B = Bs[j];
    if (A != B) {
      vu vs = {A, B};
      sort(all(vs));
      ull v0 = vs[0], v1 = vs[1];

      ull m = v1 - v0 + 1, M = v1 + v0 - 1;
      auto it = lower_bound(all(As), m);
      if (it == As.end()) {
        return false;
      }
      if (it - As.begin() == found_i) {
        it++;
      }
      if (it == As.end() || *it > M) {
        return false;
      }
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu As(N), Bs(N);
    fore(j, 0, N) {
      cin >> As[j];
    }
    fore(j, 0, N) {
      cin >> Bs[j];
    }

    if (solve1(As, Bs)) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }

  /*   fore(i, 0, 10000) {
    ull N = 3;
    vu As(N), Bs(N);
    fore(j, 0, N) {
      As[j] = rand() % 5 + 1;
      Bs[j] = rand() % 5 + 1;
    }

    bool ans1 = solve1(As, Bs);
    bool ans2 = force(As, Bs);

    if (ans1 != ans2) {
      cerr << "ERROR\n";
      cerr << N << '\n';
      for (ull A : As) {
        cerr << A << ' ';
      }
      cerr << '\n';
      for (ull B : Bs) {
        cerr << B << ' ';
      }
      cerr << '\n';
      cerr << "ans1: " << ans1 << '\n';
      cerr << "ans2: " << ans2 << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
