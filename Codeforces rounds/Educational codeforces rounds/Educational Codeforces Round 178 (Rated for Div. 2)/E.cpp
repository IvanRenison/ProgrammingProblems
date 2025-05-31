// https://codeforces.com/contest/2104/problem/E

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


vu solve(ull k, string& s, vector<string>& ts) {
  ull n = s.size(), q = ts.size();

  vector<vu> map_ford(n);
  map_ford.back() = vu(k, n);
  map_ford.back()[s.back() - 'a'] = n - 1;
  for (ull i = n - 1; i--; ) {
    map_ford[i] = map_ford[i + 1];
    map_ford[i][s[i] - 'a'] = i;
  }

  vu ans_end(n + 1);
  ans_end[n] = 1;
  vb found(k, false);
  ull found_count = 0;
  for (ull i = n; i--; ) {
    if (!found[s[i] - 'a']) {
      found[s[i] - 'a'] = true;
      found_count++;
    }

    ans_end[i] = ans_end[i + 1];
    if (found_count == k) {
      found = vb(k, false);
      found_count = 0;
      ans_end[i]++;
    }
  }

  vu ans(q);
  fore(j, 0, q) {
    ull i = 0, pos = 0;
    for (; i < ts[j].size(); i++) {
      if (pos >= n) {
        ans[j] = 0;
        pos = n + 1;
        break;
      }

      ull c = ts[j][i] - 'a';
      pos = map_ford[pos][c] + 1;

      if (pos > n) {
        ans[j] = 0;
        break;
      }
    }

    if (pos < n) {
      ans[j] = ans_end[pos];
    } else if (pos == n) {
      ans[j] = 1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  ull q;
  cin >> q;
  vector<string> ts(q);
  for (ull i = 0; i < q; ++i) {
    cin >> ts[i];
  }


  auto ans = solve(k, s, ts);
  for (ull i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }

}
