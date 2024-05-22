// https://judge.beecrowd.com/en/problems/view/3455

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

/*
A = graph
B = dp
C = geo
*/

#include <iostream>

using namespace std;

ull graphToDp(ull A) {
  return (A * 2) / 3;
}

ull dpToGraph(ull B) {
  return (B * 3) / 2;
}

ull geoToGraph(ull C) {
  return (C * 5) / 2;
}

ull graphToGeo(ull A) {
  return (A * 2) / 5;
}

ull solve(ull A, ull B, ull C, char x) {
  A *= 30, B *= 30, C *= 30;
  ull ans;
  if (x == 'A') {
    ans = A + dpToGraph(B) + geoToGraph(C);
  } else if (x == 'B') {
    ans = graphToDp(A) + B + graphToDp(geoToGraph(C));
  } else {
    ans = graphToGeo(A) + graphToGeo(dpToGraph(B)) + C;
  }

  ans /= 30;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull A, B, C;
  char x;
  cin >> A >> B >> C >> x;

  ull ans = solve(A, B, C, x);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
