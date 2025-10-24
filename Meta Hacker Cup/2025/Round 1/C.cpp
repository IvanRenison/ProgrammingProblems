// https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/C

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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


ull solve(const vu& As) {
  ull N = As.size();

  ull ans = 0;
  fore(l, 1, N + 1) {
    ull amnt = N - l + 1;
    ans += amnt * l;
  }

  vu xors(N + 1);
  fore(i, 0, N) {
    xors[i + 1] = xors[i] ^ As[i];
  }

  map<ull, ull> counts;

  for (ull x : xors) {
    counts[x]++;
    ull cnt = counts[x];
    ans -= cnt * (cnt - 1) / 2;
  }

  return ans;
}

ull force(const vu& As) {
  ull N = As.size();
  assert(N <= 100);
  ull ans = 0;

  fore(i, 0, N) fore(j, i + 1, N + 1) {
    if (j == i + 1) {
      ans += (As[i] != 0);
    } else {
      ull this_ans = 0;
      ull x = As[i];
      fore(k, i + 1, j - 1) {
        if (x != 0) {
          this_ans += 1;
        }
        x ^= As[k];
      }
      if (x != As[j - 1]) {
        this_ans = j - i;
      } else {
        this_ans += (x != 0);
      }
      ans += this_ans;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull t;
  cin >> t;

  fore(testCase, 0, t) {
    ull N;
    cin >> N;
    vu As(N);
    for (ull& A : As) {
      cin >> A;
    }

    auto ans = solve(As);

    cout << "Case #" << testCase + 1 << ": ";
    cout << ans << '\n';
  }
#else
  fore(_, 0, 10000) {
    ull N = rand() % 50 + 1;
    vu As(N);
    fore(i, 0, N) {
      As[i] = rand() % 10;
    }

    ull ans = solve(As);
    ull ansf = force(As);

    if (ans != ansf) {
      cerr << "Error!" << endl;
      cerr << N << endl;
      for (ull A : As) {
        cerr << A << " ";
      }
      cerr << endl;
      cerr << "solve = " << ans << "\nforce = " << ansf << endl;
      return 1;
    }
  }
#endif
}
