// https://atcoder.jp/contests/arc177/tasks/arc177_a

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


bool solve(ull A, ull B, ull C, ull D, ull E, ull F, vu &Xs) {

  for (ull X : Xs) {
    if (X > F * 500) {
      X -= F*500;
      F = 0;
    } else {
      ull d = X / 500;
      X -= d * 500;
      F -= d;
    }

    if (X > E * 100) {
      X -= E*100;
      E = 0;
    } else {
      ull d = X / 100;
      X -= d * 100;
      E -= d;
    }

    if (X > D * 50) {
      X -= D*50;
      D = 0;
    } else {
      ull d = X / 50;
      X -= d * 50;
      D -= d;
    }

    if (X > C * 10) {
      X -= C*10;
      C = 0;
    } else {
      ull d = X / 10;
      X -= d * 10;
      C -= d;
    }

    if (X > B * 5) {
      X -= B*5;
      B = 0;
    } else {
      ull d = X / 5;
      X -= d * 5;
      B -= d;
    }

    if (X > A) {
      return false;
    } else {
      A -= X;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull A, B, C, D, E, F;
  cin >> A >> B >> C >> D >> E >> F;
  ull N;
  cin >> N;
  vu Xs(N);
  for (auto &x : Xs) cin >> x;

  bool ans = solve(A, B, C, D, E, F, Xs);

  cout << (ans ? "Yes" : "No") << '\n';

  return EXIT_SUCCESS;
}
