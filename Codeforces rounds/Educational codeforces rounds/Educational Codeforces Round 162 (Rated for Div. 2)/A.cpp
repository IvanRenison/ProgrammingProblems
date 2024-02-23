// https://codeforces.com/contest/1923/problem/A

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


ull solve1(vu as) {
  ull n = as.size();

  ull first1 = 0;
  while (first1 < n && as[first1] == 0) first1++;

  ull count1 = 0;
  for(ull a : as) {
    if (a == 1) count1++;
  }

  ull ans = 0;

  for (ull i = n - 1; i >= first1 + count1; i--) {
    if (as[i] == 1) {
      ull j = i - 1;
      while (as[j] == 1) j--;
      as[i] = 0;
      as[j] = 1;
      ans++;
    }
  }

/*   ull i = 0;
  while (i < n && as[i] == 0) i++;

  if (i == n) return 0;

  while (i < n && as[i] == 1) i++;

  ull ans = 0;

  while (i < n) {
    while (as[i] == 0) {
      ull first1 = i;
      while (first1 < n && as[first1] == 0) first1++;
      if (first1 == n) return ans;

      ull firstlast1 = first1;
      while (firstlast1 + 1 < n && as[firstlast1 + 1] == 1) firstlast1++;
      as[first1 - 1] = 1;
      as[firstlast1] = 0;
      ans++;
    }
    i++;
  } */

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) cin >> as[j];

    auto ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
