// https://www.codechef.com/problems/ONETOTHREE

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


ull solve(vu& As) {
  ull N = SZ(As);

  fore(i, 0, N - 2) {
    if (As[i] == 1 && As[i + 1] == 3 && As[i + 2] == 3) {
      As[i + 1] = 1;
    } else if (As[i] == 3 && As[i + 1] == 3 && As[i + 2] == 1) {
      for (ull j = i + 1; j--; ) {
        if (As[j] == 3 && As[j + 1] == 3 && As[j + 2] == 1) {
          As[j + 1] = 1;
        } else {
          break;
        }
      }
    } else if (As[i] == 2 && As[i + 1] == 3 && As[i + 2] == 2) {
      As[i + 1] = 1;
    }


  }

  ull sum = accumulate(ALL(As), 0ull);

  return sum;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    ull N;
    cin >> N;
    vu As(N);
    fore(i, 0, N) {
      cin >> As[i];
    }


    auto ans = solve(As);
    cout << ans << '\n';
  }

}
