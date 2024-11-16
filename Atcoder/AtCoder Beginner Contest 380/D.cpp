// https://atcoder.jp/contests/abc380/tasks/abc380_d

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

char changeCase(char c) {
  if (islower(c)) {
    return toupper(c);
  } else {
    return tolower(c);
  }
}

vector<char> solve(string& S, vu& Ks) {
  ull Q = SZ(Ks);
  vector<char> ans(Q);

  fore(i, 0, Q) {
    char c = S[Ks[i] % S.size()];

    ll pos = Ks[i] / S.size();

    if (__builtin_popcountll(pos) % 2 == 1) {
      c = changeCase(c);
    }

    ans[i] = c;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
/*
  fore(i, 0, 32) {
    cout << __builtin_popcountll(i) % 2;
  }
  return 0; */

  string S;
  ull Q;
  cin >> S >> Q;
  vu Ks(Q);
  for (ull i = 0; i < Q; i++) {
    cin >> Ks[i];
    Ks[i]--;
  }

  auto ans = solve(S, Ks);
  for (char c : ans) {
    cout << c << ' ';
  }
  cout << '\n';

}
