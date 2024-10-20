// https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-2/problems/A2

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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

vector<vu> crecientes = {{}, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
vector<vu> decrecientes = {{}, {1, 2, 3, 4, 5, 6, 7, 8, 9}};

vu validos = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void init() {
  fore(k, 2, 10) {
    crecientes.push_back({});
    for (ull x : crecientes[k - 1]) {
      fore(i, x % 10, 10) {
        crecientes[k].push_back(x * 10 + i);
      }
    }
    decrecientes.push_back({});
    for (ull x : decrecientes[k - 1]) {
      fore(i, 1, x % 10 + 1) {
        decrecientes[k].push_back(x * 10 + i);
      }
    }
  }

  ull d = 1;
  fore(k, 1, 10) {
    for (ull x : crecientes[k]) {
      for (ull y : decrecientes[k]) {
        ull M = max(x % 10, y / d);
        fore(i, M + 1, 10) {
          validos.push_back(x * d * 100 + i * d * 10 + y);
        }
      }
    }

    d *= 10;
  }

  sort(ALL(validos));
}

ull solve(ull A, ull B, ull M) {

  ull i = lower_bound(ALL(validos), A) - validos.begin();

  ull ans = 0;
  for (; i < validos.size() && validos[i] <= B; i++) {
    if (validos[i] % M == 0) {
      //cerr << validos[i] << endl;
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  cerr << SZ(validos) << endl;


  ull t;
  cin >> t;

  fore(tc, 0, t) {
    cout << "Case #" << tc + 1 << ": ";

    ull A, B, M;
    cin >> A >> B >> M;

    auto ans = solve(A, B, M);
    cout << ans << '\n';
  }

}
