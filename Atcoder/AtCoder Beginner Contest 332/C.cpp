// https://atcoder.jp/contests/abc332/tasks/abc332_c

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


void solve(void) {

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  string S;
  cin >> N >> M >> S;

  ull ans = 0;

  ull plain_clean = M;
  ull plain_dirty = 0;
  ull atcoder_clean = 0;
  ull atcoder_dirty = 0;


  for (char c : S) {
    if (c == '0') {
      plain_clean += plain_dirty;
      plain_dirty = 0;
      atcoder_clean += atcoder_dirty;
      atcoder_dirty = 0;
    } else if (c == '1') {
      if (plain_clean > 0) {
        plain_clean--;
        plain_dirty++;
      } else if (atcoder_clean > 0) {
        atcoder_clean--;
        atcoder_dirty++;
      } else {
        ans++;
        atcoder_dirty++;
      }
    } else {
      if (atcoder_clean > 0) {
        atcoder_clean--;
        atcoder_dirty++;
      } else {
        ans++;
        atcoder_dirty++;
      }
    }
  }



  cout << ans << '\n';

  return EXIT_SUCCESS;
}
