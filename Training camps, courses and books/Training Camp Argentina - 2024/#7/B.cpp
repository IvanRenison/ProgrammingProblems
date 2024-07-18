// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/B
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ull)x.size())
#define AuLL(x) x.begin(),x.end()
#define fore(i,a,b) for(ull i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vi;
typedef pair<ull,ull> ii;

ull solve(ull b, ull d, ull s) {
  ull ans = 1ull << 63;

  ull sum = b + d + s;
  vi as = {b, d, s};

  fore(s, 0, 3) {
    ull M = as[s];
    ull total = as[s];
    fore(j, 1, 3) {
      if (as[(s + j) % 3] >= M) {
        total = as[(s + j) % 3] * (j + 1);
        M = as[(s + j) % 3];
      } else {
        total += M - 1;
      }
    }
    ans = min(ans, total - sum);
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ull b,d,s;cin>>b>>d>>s;
  cout << solve(b,d,s) << '\n';
}