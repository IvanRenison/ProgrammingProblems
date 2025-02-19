// https://codeforces.com/contest/2069/problem/E

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


bool solve(string& s, ull a, ull b, ull ab, ull ba) {
  ull n = s.size();

  vector<string> ss;

  ull j = 0;
  fore(i, 1, n) {
    if (s[i - 1] == s[i]) {
      ss.push_back(s.substr(j, i - j));
      j = i;
    }
  }
  ss.push_back(s.substr(j, n - j));

  ull sa = 0, sb = 0;
  vu sab, sba, saba, sbab;
  for (string& t : ss) {
    if (t == "A") {
      sa++;
    } else if (t == "B") {
      sb++;
    } else if (t[0] == 'A' && t.back() == 'B') {
      sab.push_back(t.size());
    } else if (t[0] == 'B' && t.back() == 'A') {
      sba.push_back(t.size());
    } else if (t[0] == 'A' && t.back() == 'A') {
      saba.push_back(t.size());
    } else {
      assert(t[0] == 'B' && t.back() == 'B');
      sbab.push_back(t.size());
    }
  }

  if (sa > a || sb > b) {
    return false;
  }

  a -= sa;
  b -= sb;

  sort(ALL(sab));
  reverse(ALL(sab));
  sort(ALL(sba));
  reverse(ALL(sba));

  while (!sab.empty()) {
    ull x = sab.back();
    sab.pop_back();
    if (x / 2 <= ab) {
      ab -= x / 2;
    } else {
      sab.push_back(x - 2 * ab);
      ab = 0;
      break;
    }
  }
  while (!sba.empty()) {
    ull x = sba.back();
    sba.pop_back();
    if (x / 2 <= ba) {
      ba -= x / 2;
    } else {
      sba.push_back(x - 2 * ba);
      ba = 0;
      break;
    }
  }

  while (!saba.empty()) {
    ull x = saba.back();
    saba.pop_back();
    if (a == 0) {
      return false;
    }
    if (x / 2 <= ab) {
      ab -= x / 2;
      a--;
    } else {
      saba.push_back(x - 2 * ab);
      ab = 0;
      break;
    }
  }
  while (!saba.empty()) {
    ull x = saba.back();
    saba.pop_back();
    if (a == 0) {
      return false;
    }
    if (x / 2 <= ba) {
      ba -= x / 2;
      a--;
    } else {
      saba.push_back(x - 2 * ba);
      ba = 0;
      break;
    }
  }
  while (!sbab.empty()) {
    ull x = sbab.back();
    sbab.pop_back();
    if (b == 0) {
      return false;
    }
    if (x / 2 <= ab) {
      ab -= x / 2;
      b--;
    } else {
      sbab.push_back(x - 2 * ab);
      ab = 0;
      break;
    }
  }
  while (!sbab.empty()) {
    ull x = sbab.back();
    sbab.pop_back();
    if (b == 0) {
      return false;
    }
    if (x / 2 <= ba) {
      ba -= x / 2;
      b--;
    } else {
      sbab.push_back(x - 2 * ba);
      ba = 0;
      break;
    }
  }


  while (!sab.empty()) {
    ull x = sab.back();
    sab.pop_back();
    if (a == 0 || b == 0) {
      return false;
    }
    a--, b--;
    x -= 2;
    if (x / 2 <= ba) {
      ba -= x / 2;
    } else {
      sba.push_back(x - 2 * ba);
      ba = 0;
      break;
    }
  }

  while (!sba.empty()) {
    ull x = sba.back();
    sba.pop_back();
    if (a == 0 || b == 0) {
      return false;
    }
    a--, b--;
    x -= 2;
    if (x / 2 <= ab) {
      ab -= x / 2;
    } else {
      sab.push_back(x - 2 * ab);
      ab = 0;
      break;
    }
  }

  while (!sab.empty()) {
    ull x = sab.back();
    sab.pop_back();
    if (a < x/2 || b < x/2) {
      return false;
    }
    a -= x / 2, b -= x / 2;
  }
  while (!sba.empty()) {
    ull x = sba.back();
    sba.pop_back();
    if (a < x/2 || b < x/2) {
      return false;
    }
    a -= x / 2, b -= x / 2;
  }
  while (!saba.empty()) {
    ull x = saba.back();
    saba.pop_back();
    if (a < x/2 + 1 || b < x/2) {
      return false;
    }
    a -= x / 2 + 1, b -= x / 2;
  }
  while (!sbab.empty()) {
    ull x = sbab.back();
    sbab.pop_back();
    if (a < x/2 || b < x/2 + 1) {
      return false;
    }
    a -= x / 2, b -= x / 2 + 1;
  }

  return true;
}

bool force(string& s, ull a, ull b, ull ab, ull ba) {
  ull n = s.size();

  fore(x, 0, 1 << (n - 1)) {
    ull j = 0;
    vector<string> ss;
    fore(i, 1, n) {
      if (x & (1 << (i - 1))) {
        ss.push_back(s.substr(j, i - j));
        j = i;
      }
    }
    ss.push_back(s.substr(j, n - j));

    ull ca = 0, cb = 0, cab = 0, cba = 0;
    for (string t : ss) {
      if (t == "A") {
        ca++;
      } else if (t == "B") {
        cb++;
      } else if (t == "AB") {
        cab++;
      } else if (t == "BA") {
        cba++;
      } else {
        goto end;
      }
    }

    if (ca <= a && cb <= b && cab <= ab && cba <= ba) {
      return true;
    }

    end:;
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

/*   cout << "1\n";
  fore(i, 0, 500000) {
    ull x = rand() % 2;
    if (x) {
      cout << "A";
    } else {
      cout << "B";
    }
  }
  cout << "\n";
  cout << "200000 200000 200000 200000\n";
  return 0; */
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s;
    cin >> s;
    ull a, b, ab, ba;
    cin >> a >> b >> ab >> ba;

    bool ans = solve(s, a, b, ab, ba);
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
#else
  fore(_, 0, 100000) {
    ull n = rand() % 8 + 1;
    string s;
    fore(i, 0, n) {
      ull x = rand() % 2;
      if (x) {
        s += "A";
      } else {
        s += "B";
      }
    }
    ull a = rand() % (n + 1);
    ull b = rand() % (n + 1);
    ull ab = rand() % (n + 1);
    ull ba = rand() % (n + 1);

    ull ans = solve(s, a, b, ab, ba);
    ull ansf = force(s, a, b, ab, ba);
    if (ans != ansf) {
      cout << "ERROR\n";
      cout << s << '\n';
      cout << a << ' ' << b << ' ' << ab << ' ' << ba << '\n';
      cout << ans << ' ' << ansf << '\n';
      return 1;
    }
  }
#endif
}
