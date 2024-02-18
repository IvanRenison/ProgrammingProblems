// https://redprogramacioncompetitiva.com/contests/2024/01/

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

bool isNum(char c) {
  return c >= '0' && c <= '9';
}

ull parseNum(const string& s, ull& pos) {
  ull n = s.size();
  ull res = 0;
  while (pos < n && isNum(s[pos])) {
    res = res * 10 + (s[pos] - '0');
    pos++;
  }
  return res;
}

void skipBlanck(const string& s, ull& pos) {
  ull n = s.size();
  while (pos < n && s[pos] == ' ') {
    pos++;
  }
}

ull parse(const string& s, ull& pos, set<uu>& res) {
  ull n = s.size();

  ull p;

  skipBlanck(s, pos);

  if (pos < n && s[pos] != ')') {
    p = parseNum(s, pos);

    skipBlanck(s, pos);

    while (pos < n && s[pos] != ')') {
      assert (s[pos] == '(');
      pos++;
      skipBlanck(s, pos);
      ull p1 = parse(s, pos, res);
      res.insert({p, p1});
      skipBlanck(s, pos);
      assert(s[pos] == ')');
      pos++;

      skipBlanck(s, pos);
    }
  }

  return p;
}

bool solve(string l0, string l1) {

  set<uu> t0, t1;

  ull pos0 = 0, pos1 = 0;

  ull p0 = parse(l0, pos0, t0);
  ull p1 = parse(l1, pos1, t1);

  return p0 == p1 && t0 == t1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string line0, line1;
  getline(cin, line0);
  getline(cin, line1);

  bool ans = solve(line0, line1);
  if (ans) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
