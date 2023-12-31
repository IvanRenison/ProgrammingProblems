// https://codeforces.com/contest/1916/problem/C

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
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


vu solve1(const vu& as) {
  ull n = as.size();

  vu ans(n);

  ull sum = 0;
  ull countEven = 0, countOdd = 0;

  fore(i, 0, n) {
    ull a = as[i];

    sum += a;
    if (a % 2 == 0) {
      countEven++;
    } else {
      countOdd++;
    }

    if (i == 0) {
      ans[i] = a;
    } else if (i == 2) {
      if (countEven == 0 || countEven == 2) {
        ans[i] = sum - 1;
      } else if (countEven == 1) {
        ans[i] = sum;
      } else {
        ans[i] = sum;
      }
    } else if (i == 3) {
      if (countEven == 0) {
        ans[i] = sum - 2;
      } else if (countEven == 1 || countEven == 3) {
        ans[i] = sum - 1;
      } else {
        ans[i] = sum;
      }
    } else {

      ull d = countOdd / 3 + (countOdd % 3 == 1);
      ans[i] = sum - d;
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
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(as);
    for (auto a : ans) {
      cout << a << " ";
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
