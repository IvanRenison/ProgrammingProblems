// https://codeforces.com/contest/1895/problem/C

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

ull sum(const string& s) {
  ull ans = 0;
  for (char c : s) {
    ans += c - '0';
  }
  return ans;
}

ull solve(vector<string>& ps) {
  ull n = ps.size();

  map<uuuu, ull> cnt;

  for (string& p : ps) {
    ull l = p.size();
    fore(i, 1, l + 1) {
      string a = p.substr(0, i);
      string b = p.substr(i, l - i);
      cnt[uuuu{a.size(), b.size(), sum(a), sum(b)}]++;
    }
  }

  ull ans = 0;

  for (auto [key, c] : cnt) {
    auto [la, lb, sa, sb] = key;
    if (lb == 0) {
      ans += c * c;
    } else if (sa > sb && la > lb) {
      ans += c * cnt[{la - lb, 0, sa - sb, 0}];
    } else if (sa < sb && la < lb) {
      ans += c * cnt[{lb - la, 0, sb - sa, 0}];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vector<string> ps(n);
  fore(i, 0, n) {
    cin >> ps[i];
  }

  auto ans = solve(ps);
  cout << ans << '\n';

}
