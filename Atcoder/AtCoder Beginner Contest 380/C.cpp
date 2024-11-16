// https://atcoder.jp/contests/abc380/tasks/abc380_c

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


string solve(ull K, string& s) {
  ull n = SZ(s);
  vu blocks(1, 1);

  fore(i, 1, n) {
    if (s[i] == s[i - 1]) {
      blocks.back()++;
    } else {
      blocks.push_back(1);
    }
  }

  if (s[0] == '0') {
    assert(blocks.size() > 2 * K - 1);
    blocks[2*K-3] += blocks[2*K-1];
    blocks[2*K-1] = 0;

    string ans = string(blocks[0], '0');
    fore(i, 1, SZ(blocks)) {
      ans += string(blocks[i], i % 2 == 0 ? '0' : '1');
    }

    return ans;
  } else {
    assert(blocks.size() > 2 * K - 2);
    blocks[2*K - 4] += blocks[2*K - 2];
    blocks[2*K - 2] = 0;

    string ans = string(blocks[0], '1');
    fore(i, 1, SZ(blocks)) {
      ans += string(blocks[i], i % 2 == 0 ? '1' : '0');
    }

    return ans;
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, K;
  cin >> N >> K;
  string s;
  cin >> s;
  auto ans = solve(K, s);
  cout << ans << '\n';

}
