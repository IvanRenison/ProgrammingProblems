// https://codeforces.com/contest/1922/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;


#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

vu solve1(const vu& as, const vu& ds) {
  ull n = as.size();

  struct E {
    ull prev, next, a, d;
    bool deleted = false;
  };

  vector<E> vals(n);
  fore(i, 0, n) {
    vals[i].prev = i - 1;
    vals[i].next = i + 1;
    vals[i].a = as[i];
    vals[i].d = ds[i];
  }
  vals[0].prev = inf;
  vals[n - 1].next = inf;

  vu del;
  fore(i, 0, n) {
    ull damage = 0;
    if (i > 0) {
      damage += as[i - 1];
    }
    if (i < n - 1) {
      damage += as[i + 1];
    }
    if (damage > ds[i]) {
      del.push_back(i);
    }
  }

  vu ans(n);

  fore(i, 0, n) {
    if (del.empty()) {
      break;
    }
    ans[i] = del.size();

    set<ull> mods;

    fore(j, 0, del.size()) {
      ull d = del[j];

      vals[d].deleted = true;

      if (vals[d].prev != inf) {
        vals[vals[d].prev].next = vals[d].next;
        mods.insert(vals[d].prev);
      }
      if (vals[d].next != inf) {
        vals[vals[d].next].prev = vals[d].prev;
        mods.insert(vals[d].next);
      }
    }

    del.clear();

    for (ull j : mods) {
      if (!vals[j].deleted) {
        ull damage = 0;
        if (vals[j].prev != inf) {
          damage += vals[vals[j].prev].a;
        }
        if (vals[j].next != inf) {
          damage += vals[vals[j].next].a;
        }
        if (damage > vals[j].d) {
          del.push_back(j);
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n), ds(n);
    for (ull& a : as) {
      cin >> a;
    }
    for (ull& d : ds) {
      cin >> d;
    }

    auto ans = solve1(as, ds);
    for (ull a : ans) {
      cout << a << " ";
    }
    cout << "\n";
  }

  return EXIT_SUCCESS;
}
