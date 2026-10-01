// https://codeforces.com/gym/106682/problem/B
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef vector<ull> vu;

bool isV(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

string solve(string& p) {
  ull n = p.size();

  ull count = 0;
  ull found;

  if (n < 5) {
    return "-";
  }

  auto isGAS = [&](ull i) -> bool {
    return p[i] == p[i + 4] && isV(p[i]) && p[i+1] == 'G' && p[i+2] == 'A' && p[i+3] == 'S';
  };

  fore(i, 0, n - 4) {
    if (isGAS(i)) {
      count++;
      found = i;
      i += 4;
      while (i < n - 4 && isGAS(i)) {
        i += 4;
      }
    }
  }

  if (count == 0) {
    return "-";
  }

  if (count > 1) {
    return "+";
  }

  string ans;
  fore(i, 0, found) {
    ans.push_back(p[i]);
  }
  fore(i, found + 4, n) {
    ans.push_back(p[i]);
  }

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  string p;
  cin >> p;

  auto ans = solve(p);
  cout << ans << '\n';

}
