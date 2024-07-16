// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/C
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef int ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
const ll MOD = 1e9+7;
const ll NMAX = 2010;


struct Tree {
  typedef ll T;
  static constexpr T neut = 0;
  T f(T a, T b){return (a+b)%MOD;}
  vector<T> s;ll n;
  Tree(ll n = 0, T def = neut) : s(2*n,def), n(n) {}
  void upd(ll pos, T val){
    for(s[pos += n]=val;pos/=2; )
      s[pos] =f(s[pos*2],s[pos*2+1]);
  }
  T query(ll b, ll e){
    if(b>=e)return neut;
    T ra = neut, rb = neut;
    for(b += n, e+=n;b<e;b/=2,e/=2){
      if(b&1) ra = f(ra,s[b++]);
      if(e&1) rb = f(s[--e],rb);
    }
    return f(ra,rb);
  }
};




string grid[NMAX];


int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m;cin>>n>>m;
  fore(i,0,n)cin>>grid[i];
  vector<vector<ll>> pre_s_rows(n,vector<ll>(m+1));
  vector<vector<ll>> pre_s_cols(m,vector<ll>(n+1));
  vector<Tree> sts_cols_der,sts_rows_arr;
  fore(i,0,n){
    sts_rows_arr.pb(Tree(m));
    fore(j,0,m){
      pre_s_rows[i][j+1]=pre_s_rows[i][j]+(grid[i][j]=='R');
    }
  }
  fore(i,0,m){
    sts_cols_der.pb(Tree(n));
    fore(j,0,n){
      pre_s_cols[i][j+1]=pre_s_cols[i][j]+(grid[j][i]=='R');
    }
  }
  fore(i,0,m-1){
    if(pre_s_rows[n-1][m]-pre_s_rows[n-1][i]==0){
      // vengo_arr.upd(n-1,i,1);
      sts_rows_arr[n-1].upd(i,1);
      // vengo_der.upd(n-1,i,1);
      sts_cols_der[i].upd(n-1,1);
    }
  }
  fore(i,0,n-1){
    if(pre_s_cols[m-1][n]-pre_s_cols[m-1][i]==0){
      // vengo_arr.upd(i,m-1,1);
      // vengo_der.upd(i,m-1,1);
      sts_cols_der[m-1].upd(i,1);
      sts_rows_arr[i].upd(m-1,1);
      // cout << i << " " << m-1 << " acaaa\n";
    }
  }
  if(grid[n-1][m-1]=='R'){
    cout << "0\n";
    return 0;
  }
  // vengo_arr.upd(n-1,m-1,1);
  sts_rows_arr[n-1].upd(m-1,1);
  // vengo_der.upd(n-1,m-1,1);
  sts_cols_der[m-1].upd(n-1,1);
  for(int i = n-2;i>=0;--i){
    for(int j = m-2;j>=0;--j){
      // resuelvo viniendo de arriba.
      ll hay_a_derecha = pre_s_rows[i][m]-pre_s_rows[i][j+1];
      ll hay_abajo = pre_s_cols[j][n]-pre_s_cols[j][i];
      ll que_der = sts_rows_arr[i+1].query(j+1,m-hay_a_derecha);
      ll que_abajo = sts_cols_der[j+1].query(i+1,n-hay_abajo);
      // cout << i << " " << j << " " << hay_a_derecha << " " << hay_abajo << "\n";
      // cout << que_der << " " << que_abajo << "\n";
      if(hay_abajo+i<n){
        sts_rows_arr[i].upd(j,(que_abajo+que_der)%MOD);
        // cout << que_der << " " << que_abajo << "\n";
      } else {
        // cout << 0 << " " << 0 << "\n";
      }
      // resuelvo viniendo de derecha;
      hay_a_derecha = pre_s_rows[i][m]-pre_s_rows[i][j];
      hay_abajo = pre_s_cols[j][n]-pre_s_cols[j][i+1];
      que_der = sts_rows_arr[i+1].query(j+1,m-hay_a_derecha);
      que_abajo = sts_cols_der[j+1].query(i+1,n-hay_abajo);
      if(hay_a_derecha+j<m)sts_cols_der[j].upd(i,(que_abajo+que_der)%MOD);
    }
  }
  ll res = sts_cols_der[0].query(0,1);
  // fore(i,0,n){
  //   fore(j,0,m){
  //     cout << sts_rows_arr[i].query(j,j+1) << " ";
  //   }
  //   cout << "\n";
  // }
  // cout << vengo_arr.query(0,0,1,1) << "\n";
  cout << res << "\n";
}




// 4 4
// ...R
// .RR.
// .RR.
// R...
// 2 2 0 1
// 1 0
// 2 1 1 1
// 1 0
// 2 0 2 1
// 1 0
// 1 2 0 2
// 0 0
// 1 1 1 2
// 1 0
// 1 0 2 1
// 1 0
// 0 2 1 2
// 0 1
// 0 1 1 2
// 0 1
// 0 0 1 1
// 1 1
// 2
