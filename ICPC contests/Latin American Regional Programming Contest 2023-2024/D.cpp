// https://codeforces.com/gym/104736/problem/D
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool match(const string& s, const string& w, const string& p) {
  set<char> ss;
  fore(i, 0, s.size()) {
    ss.insert(s[i]);
  }

  fore(i, 0, 5) {
    if (p[i] == 'X') {
      if (ss.find(w[i]) != ss.end()) {
        return false;
      }
    } else if (p[i] == '!') {
      if (w[i] == s[i] || ss.find(w[i]) == ss.end()) {
        return false;
      }
    } else {
      if (w[i] != s[i]) {
        return false;
      }
    }
  }

  return true;
}

vu solve(const vector<string>& ss, const vector<string>& gs) {
  ull N = ss.size(), G = gs.size();

  vu ans(G);

  fore(i, 0, G) {
    const string& p = gs[i];
    fore(j, 0, N) {
      if (match(ss[0], ss[j], p)) {
        ans[i]++;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<string> ss(N);
  for(string& s : ss) {
    cin >> s;
  }
  ull G;
  cin >> G;
  vector<string> gs(G);
  for(string& g : gs) {
    cin >> g;
  }

  auto ans = solve(ss, gs);
  for (ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
