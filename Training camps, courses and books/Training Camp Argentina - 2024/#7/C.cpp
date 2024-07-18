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

bool solve(string& A, string& S, string& T) {
  if (S == T) {
    return true;
  }
  if (S.size() > T.size()) {
    swap(S, T);
  }

  ll n = S.size(), m = T.size();
  fore(i, 0, m - n) {
    bool valid = true;
    fore(j, i, i + n) {
      if (S[j - i] != T[j]) {
        valid = false;
        break;
      }
    }

    if (valid) {
      return true;
    }
  }

  if (A.size() == 2 && S.size() == 2 && T.size() == 2) {
    char a = A[0], b = A[1];
    if (S[0] == a && S[1] == b && T[0] == b && T[1] == a) {
      return true;
    }
    if (S[0] == b && S[1] == a && T[0] == a && T[1] == b) {
      return true;
    }
  }

  return false;
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
}