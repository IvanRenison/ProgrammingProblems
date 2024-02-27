// https://codeforces.com/contest/1882/problem/B

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


ull solve1(const vector<set<ull>>& Sss) {
  ull n = Sss.size();

  vu cnt(51);

  fore(i, 0, n) {
    for (ull s : Sss[i]) {
      cnt[s]++;
    }
  }

  ull ans = 0;

  fore(i, 1, 51) {
    if (cnt[i] > 0) {
      vu this_cnt(51);
      fore(j, 0, n) {
        if (Sss[j].count(i) == 0) {
          for (ull s : Sss[j]) {
            this_cnt[s]++;
          }
        }
      }

      ull this_ans = 0;
      fore(j, 0, 51) {
        if (this_cnt[j] > 0) {
          this_ans++;
        }
      }

      ans = max(ans, this_ans);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<set<ull>> Sss(n);
    fore(i, 0, n) {
      ull k;
      cin >> k;
      fore(j, 0, k) {
        ull s;
        cin >> s;
        Sss[i].insert(s);
      }
    }

    auto ans = solve1(Sss);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
