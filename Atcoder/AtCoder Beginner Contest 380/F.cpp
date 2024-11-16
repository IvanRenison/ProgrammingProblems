//https://atcoder.jp/contests/abc380/tasks/abc380_f

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


bool solve(const vu& As, vu& Bs, vu& Cs) {
  ull N = As.size(), M = Bs.size(), L = Cs.size();

  vu cards = As;
  for (ull B : Bs) {
    cards.push_back(B);
  }
  for (ull C : Cs) {
    cards.push_back(C);
  }

  ull K = N + M + L;

  map<uu, bool> dp;

  function<bool(ull, ull)> rec = [&](ull A_mask, ull B_mask) -> bool {
    {
      auto it = dp.find({A_mask, B_mask});
      if (it != dp.end()) {
        return it->second;
      }
    }
    if (A_mask == 0) {
      return dp[{A_mask, B_mask}] = false;
    }

    fore(i, 0, K) if (A_mask & (1ll << i)) {
      ull C = cards[i];
      ull new_A_mask = A_mask ^ (1ll << i);
      if (!rec(B_mask, new_A_mask)) {
        return dp[{A_mask, B_mask}] = true;
      }
      fore(j, 0, K) if (cards[j] < C && !(A_mask & (1ll << j)) && !(B_mask & (1ll << j))) {
        if (!rec(B_mask, new_A_mask | (1ll << j))) {
          return dp[{A_mask, B_mask}] = true;
        }
      }
    }

    return dp[{A_mask, B_mask}] = false;
  };

  ull first_mask = 0;
  fore(i, 0, N) {
    first_mask |= 1ull << i;
  }
  ull second_mask = 0;
  fore(i, N, N + M) {
    second_mask |= 1ull << i;
  }

  bool ans = rec(first_mask, second_mask);
  return ans;


}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);


  ull N, M, L;
  cin >> N >> M >> L;
  vu As(N), Bs(M), Cs(L);
  for (ull& A : As) {
    cin >> A;
    A--;
  }
  for (ull& B : Bs) {
    cin >> B;
    B--;
  }
  for (ull& C : Cs) {
    cin >> C;
    C--;
  }
  auto ans = solve(As, Bs, Cs);
  if (ans) {
    cout << "Takahashi\n";
  } else {
    cout << "Aoki\n";
  }

}
