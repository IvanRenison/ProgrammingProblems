// https://codeforces.com/contest/1890/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

bool is_good(const vector<bool>& s) {
  ull n = s.size();
  fore(i, 1, n) {
    if (s[i] == s[i-1]) {
      return false;
    }
  }
  return true;
}


bool solve1(const vector<bool>& s, const vector<bool>& t) {
  if (is_good(s)) {
    return true;
  }
  if (!is_good(t)) {
    return false;
  }

  bool t0 = t[0], tb = t.back();
  if (t0 != tb) {
    return false;
  }

  fore(i, 1, s.size()) {
    if (s[i] == s[i-1]) {
      if (s[i] == t0) {
        return false;
      }
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vector<bool> s(n), t(m);
    fore(j, 0, n) {
      char c;
      cin >> c;
      s[j] = c == '1';
    }
    fore(j, 0, m) {
      char c;
      cin >> c;
      t[j] = c == '1';
    }

    if (solve1(s, t)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
