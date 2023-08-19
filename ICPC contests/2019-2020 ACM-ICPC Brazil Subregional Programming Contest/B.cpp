#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){FIN;
  ull N;
  cin >> N;
  vector<ull> vs(N);
  for(ull& v : vs) {
    cin >> v;
  }

  bool ans = true;

  for(ull v : vs) {
    if (v > vs[0]) {
      ans = false;
    }
  }

  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

  return 0;
}