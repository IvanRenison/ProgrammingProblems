// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/C
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
typedef vector<ld> vd;

/** Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
vi Z(const string& S) {
  vi z(SZ(S));
  ll l = -1, r = -1;
  fore(i,1,SZ(S)) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (i + z[i] < SZ(S) && S[i + z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r)
      l = i, r = i + z[i];
  }
  return z;
}

bool contains(const string& S, const string& T) {
  ll n = S.size(), m = T.size();
  string A = T + "#" + S;
  vi z = Z(A);
  fore(i, m + 1, n + m + 1) {
    if (z[i] == m) {
      return true;
    }
  }
  return false;
}

bool solve(string& A, string& S, string& T) {
  if (S == T) {
    return true;
  }
  if (S.size() > T.size()) {
    swap(S, T);
  }

  if (contains(T, S)) {
    return true;
  }

  ll n = S.size(), m = T.size();

  bool T_found = false;
  {
    vi zT = Z(T);
    fore(i, 1, m) {
      ll z = zT[i];
      if (z == m - i) {
        string T_ = T + T.substr(m - i);
        if (!contains(T_, S)) {
          T_found = true;
          break;
        }
      }
    }
    if (!T_found && !contains(T + T, S)) {
      T_found = true;
    }
    for (char a : A) {
      if (!T_found && !contains(T + a + T, S)) {
        T_found = true;
      }
      for (char b : A) {
        if (!T_found && !contains(T + a + b + T, S)) {
          T_found = true;
        }
      }
    }
  }
  bool S_found = false;
  {
    vi zS = Z(S);
    fore(i, 1, n) {
      ll z = zS[i];
      if (z == n - i) {
        string S_ = S + S.substr(n - i);
        if (!contains(S_, T)) {
          S_found = true;
          break;
        }
      }
    }
    if (!S_found && !contains(S + S, T)) {
      S_found = true;
    }
    for (char a : A) {
      if (!S_found && !contains(S + a + S, T)) {
        S_found = true;
      }
      for (char b : A) {
        if (!S_found && !contains(S + a + b + S, T)) {
          S_found = true;
        }
      }
    }
  }

  if (T_found && S_found) {
    return false;
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    string A, S, T;
    cin >> A >> S >> T;

    bool ans = solve(A, S, T);
    cout << (ll)ans << '\n';
  }

/*   cout << 50 << '\n';
  fore(_, 0, 50) {
    fore(c, 0, 26) {
      cout << (char)('a' + c);
    }
    cout << ' ';
    fore(_, 0, 500) {
      cout << (char)('a' + (rand() % 26));
    }
    cout << ' ';
    fore(_, 0, 500) {
      cout << (char)('a' + (rand() % 26));
    }
    cout << '\n';
  } */
}
