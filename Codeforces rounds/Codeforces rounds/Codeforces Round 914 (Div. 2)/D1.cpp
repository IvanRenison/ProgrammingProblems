// https://codeforces.com/contest/1904/problem/D1

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
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl


bool solve1(vu& as, const vu& bs) {
  ull n = as.size();

  vuu bs_i(n);
  fore(i, 0, n) {
    bs_i[i] = {bs[i], i};
  }
  sort(all(bs_i));

  for (auto [b, i] : bs_i) {
    if (as[i] > b) {
      return false;
    }
    if (as[i] == b) {
      continue;
    }

    {
      fore(j, i + 1, n) {
        if (as[j] > b || bs[j] < b) {
          break;
        }
        if (as[j] == b) {
          fore(j_, i, j) {
            as[j_] = b;
          }
          goto next;
        }
      }
    }
    {
      for (ull j = i - 1; j < n; j--) {
        if (as[j] > b || bs[j] < b) {
          break;
        }
        if (as[j] == b) {
          fore(j_, j + 1, i + 1) {
            as[j_] = b;
          }
          goto next;
        }
      }
    }
    return false;
    next:;
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n), bs(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    fore(j, 0, n) {
      cin >> bs[j];
    }

    if (solve1(as, bs)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
