// https://codeforces.com/contest/1866/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((int) x.size())
#define ALL(x) (x.begin(),x.end())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull mod = 998244353;

ull solve(vector<ull> As, vector<ull> Bs, vector<ull> Cs, vector<ull> Ds) {
  ull N = As.size(), M = Cs.size();
  map<ull, ull> X;
  fore(i, 0, N) {
    X[As[i]] = Bs[i];
  }

  map<ull, ull> Y;
  fore(i, 0, M) {
    if (X[Cs[i]] < Ds[i]) {
      return 0;
    }
    Y[Cs[i]] = Ds[i];
  }

  ull ans = 1;

  fore(i, 0, N) {
    if (Bs[i] != Y[As[i]])
      ans = (ans * 2) % mod;
  }

  return ans;
}

int main(){
  FIN;
  ull N;
  cin >> N;
  vector<ull> As(N), Bs(N);
  for(ull& A : As) {
    cin >> A;
  }
  for(ull& B : Bs) {
    cin >> B;
  }
  ull M;
  cin >> M;
  vector<ull> Cs(M), Ds(M);
  for(ull& C : Cs) {
    cin >> C;
  }
  for(ull& D : Ds) {
    cin >> D;
  }

  cout << solve(As, Bs, Cs, Ds) << '\n';

  return 0;
}
