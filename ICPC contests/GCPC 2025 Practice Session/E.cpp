//

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

const map<char, char> id_map = {
  {'b', 'b'},
  {'d', 'd'},
  {'p', 'p'},
  {'q', 'q'}
};

const map<char, char> h_map = {
  {'b', 'd'},
  {'d', 'b'},
  {'p', 'q'},
  {'q', 'p'}
};

const map<char, char> v_map = {
  {'b', 'p'},
  {'d', 'q'},
  {'p', 'b'},
  {'q', 'd'}
};

const map<char, char> r_map = {
  {'b', 'q'},
  {'d', 'p'},
  {'p', 'd'},
  {'q', 'b'}
};

void comb(map<char, char>& m, const map<char, char>& m2) {
  for (auto& [k, v] : m) {
    v = m2.at(v);
  }
}

string solve(string& s, string& t) {
  map<char, char> ans_map = id_map;

  bool hor_flip = false;
  for (char c : t) {
    if (c == 'h') {
      comb(ans_map, h_map);
      hor_flip = !hor_flip;
    } else if (c == 'v') {
      comb(ans_map, v_map);
    } else { // c == 'r'
      comb(ans_map, r_map);
      hor_flip = !hor_flip;
    }
  }

  for (char& c : s) {
    c = ans_map[c];
  }

  if (hor_flip) {
    reverse(ALL(s));
  }

  return s;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  auto ans = solve(s, t);
  cout << ans << '\n';

}
