#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ull i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll NMAX = 110;
const ll INF = 1ll << 48;

using rpriority_queue = priority_queue<pair<ull, ull>, vector<pair<ull, ull>>, greater<pair<ull, ull>>>;

ll floyd(vector<vector<ull>>& g){
  ull n = g.size();
  vector<vector<bool>> alts(n, vector<bool>(n, false));
  fore(k,0,n)fore(i,0,n)if(g[i][k]<INF && i != k)fore(j,0,n)if(g[k][j]<INF && j!=k) {
    // g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    ull ng = g[i][k]+g[k][j];
    if (ng < g[i][j]) {
      return -1;
    }
    if (ng == g[i][j]) {
      alts[i][j] = true;
    }
  }

  ull count = 0;
  fore(i, 0, n) {
    fore(j, i+1, n) {
      if (alts[i][j]) {
        cerr << i << ' ' << j << '\n';
        count++;
      }
    }
  }

  return count;
}

int main(){FIN;
  ull N;
  cin>>N;
  vector<vector<ull>> adj(N, vector<ull>(N));
  fore(i,0,N){
    fore(j, 0, N) {
      cin >> adj[i][j];
    }
  }

  cout << floyd(adj) << '\n';

  return 0;
}

