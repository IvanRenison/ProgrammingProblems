// https://codeforces.com/contest/1948/problem/E

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


tuple<vu, ull, vu> solve1(ull n, ull k) {
  vu as(n);

  ull c = 0;

  fore(i, 0, n / k) {
    ull l = i * k, r = i * k + k - 1;
    ull m = l + (k - 3) / 2;
    ull M = l + (k - 1) / 2;
    while (m >= l && m < n) {
      as[m] = c;
      c++;
      m--;
    }
    while (M <= r && r < n) {
      as[r] = c;
      c++;
      r--;
    }
  }

  ull l = k * (n / k), r = n - 1;
  ull m = l + (r - l + 1 - 3) / 2;
  ull M = l + (r - l + 1 - 1) / 2;
  while (m >= l && m < n) {
    as[m] = c;
    c++;
    m--;
  }
  while (M <= r && r < n) {
    as[r] = c;
    c++;
    r--;
  }




  vu cliques(n);
  fore(i, 0, n) {
    cliques[i] = i / k;
  }

  return {as, (n + k - 1) / k, cliques};
}

ull diff(ull a, ull b) {
  return max(a, b) - min(a, b);
}

vu get(ull k) {
  vu as(k);
  fore(i, 0, k) {
    as[i] = i;
  }

  do {
    fore(i, 0, k) {
      fore(j, i + 1, k) {
        if (diff(i, j) + diff(as[i], as[j]) > k) {
          goto next;
        }
      }
    }

    return as;

    next:;
  } while (next_permutation(ALL(as)));

  return {};
}

bool check(const vu& as) {
  ull k = as.size();
  fore(i, 0, k) {
    fore(j, i + 1, k) {
      if (diff(i, j) + diff(as[i], as[j]) > k) {
        return false;
      }
    }
  }
  return true;
}


bool testALL() {
  fore(i, 1, 41) {
    auto [as, _, __] = solve1(i, i);
    if (!check(as)) {
      cerr << "ERROR: " << i << '\n';
      return false;
    }
  }
  return true;
}

bool check(const vu& as, ull m, const vu& cs, ull k) {
  ull n = as.size();
  vector<vu> cliques(m);
  fore(i, 0, n) {
    cliques[cs[i]].push_back(i);
  }

  for (vu& cli : cliques) {
    fore(i, 0, cli.size()) {
      fore(j, i + 1, cli.size()) {
        ull d = diff(cli[i], cli[j]) + diff(as[cli[i]], as[cli[j]]);
        if (d > k) {
          return false;
        }
      }
    }
  }

  vu as_ = as;
  sort(ALL(as_));
  fore(i, 0, n) {
    if (as_[i] != i) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  //assert(testALL());

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;

    auto [as, m, cs] = solve1(n, k);
    for (ull a : as) {
      cout << a + 1 << ' ';
    }
    cout << '\n';
    cout << m << '\n';
    for (ull c : cs) {
      cout << c + 1 << ' ';
    }
    cout << '\n';
  }

/*   fore(n, 2, 41) {
    fore(k, 1, 2 * n) {
      auto [as, m, cs] = solve1(n, k);
      if (!check(as, m, cs, k)) {
        cerr << "ERROR: " << k << ' ' << n << endl;
        return EXIT_FAILURE;
      }
    }
  } */

/*   fore(k, 1, 20) {
    auto as = get(k);
    cerr << "k = " << k << '\n';
    cerr << "as =";
    for (ull a : as) {
      cerr << ' ' << a;
    }
    cerr << endl;
  } */

  return EXIT_SUCCESS;
}
/*
0
0

0 1
0 1

0 1 2
1 0 2

0 1 2 3
0 3 2 1

0 1 2 3 4
2 4 0 1 3

0 1 2 3 4 5
2 4 5 0 1 3

0 1 2 3 4 5 6
3 5 6 0 2 1 4


*/