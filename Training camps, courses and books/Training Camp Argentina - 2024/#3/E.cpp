// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
const int NMAX = 4e5+10;
const int MASK = (1<<20)+5;
const int MAXS = 20;


int n;
string ss[MAXS];
vector<vector<int>> pre_s(MAXS,vector<int>(NMAX));
vector<int> pre_s_posis[MAXS][NMAX];
int calculo[MAXS][NMAX];
int suma[MASK];
int dp[MASK];

struct RMQ {
  vector<vector<int>> jmp;
  RMQ(const vector<int> &V) : jmp(1,V){
    for(int pw = 1, k=1;pw*2 <= SZ(V); pw*=2,++k){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] =min(jmp[k-1][j],jmp[k-1][j+pw]);
    }
  }
  int query(int a, int b){
    assert(a < b);
    int dep = 31 - __builtin_clz(b-a);
    return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};


int f(int x){
  if(x==(1<<n)-1)return 0;
  int &res = dp[x];
  if(res!=-1)return res;
  int c = suma[x];
  if(c<0)return res=0;
  int aux = (~x)&((1<<n)-1);
  res = 0;
  while(aux!=0){
    int v = bit_width(unsigned(aux&(-aux)))-1;
    int m = SZ(ss[v]);
    // int cuantos = f(x+(1<<v));
    // cout << x << " " << calculo[v][c] << " " << m << " " << cuantos << endl;
    if(calculo[v][c]>m){
      int cuantos = f(x+(1<<v));
      if(c<=m){
        cuantos += SZ(pre_s_posis[v][c]);
      }
      res = max(res, cuantos);
    } else {
      if(c<=m){
        int posi = lower_bound(ALL(pre_s_posis[v][c]),calculo[v][c])-pre_s_posis[v][c].begin();
        res = max(res,posi);
      }
    }
    aux -= (1<<v);
  }
  return res;
}



int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  mset(dp,-1);
  cin>>n;
  fore(i,0,n)cin>>ss[i];
  fore(i,0,n){
    int m = SZ(ss[i]);
    fore(j,0,m){
      pre_s[i][j+1]=pre_s[i][j];
      if(ss[i][j]==')')pre_s[i][j+1]--;
      else pre_s[i][j+1]++;
      if(pre_s[i][j+1]<=0)pre_s_posis[i][-pre_s[i][j+1]].pb(j+1);
    }
    RMQ rmq(pre_s[i]);
    fore(j,0,NMAX){
      ll l = 0, r = m;
      while(l<=r){
        ll mid = (l+r)/2;
        if(rmq.query(0,mid+1)<-j)r=mid-1;
        else l=mid+1;
      }
      // if(j==1)cout << calculo[0][0] << '\n';
      calculo[i][j]=l;
    }
  }
  fore(i,0,(1<<n)){
    int aux = i;
    while(aux!=0){
      int v = bit_width(unsigned(aux&(-aux)))-1;
      suma[i] += pre_s[v][SZ(ss[v])];
      aux -= (1<<v);
    }
  }
  int res = f(0);
  cout << res << '\n';
}