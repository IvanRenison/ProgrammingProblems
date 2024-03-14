// https://redprogramacioncompetitiva.com/contests/2024/02/

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


string solve(vector<string> names) {
  ull n = names.size(), m = names[0].size();

  vector<vu> votes(m, vu(26, 0));

  for (string& s : names) {
    fore(i, 0, m) {
      votes[i][s[i] - 'a']++;
    }
  }

  string ans;

  fore(i, 0, m) {
    ull max_votes = 0;
    char max_char = 'a';
    fore(j, 0, 26) {
      if (votes[i][j] > max_votes) {
        max_votes = votes[i][j];
        max_char = 'a' + j;
      }
    }
    ans.push_back(max_char);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;
  cin >> n >> m;
  vector<string> names(n);
  fore(i, 0, n) cin >> names[i];

  auto ans = solve(names);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
