// https://redprogramacioncompetitiva.com/contests/2023/11
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vii;
typedef vector<ull> vuii;
typedef pair<ll,ll> ii;
const ll MOD = 1e9+7;

ll add(ll x, ll y){
    return (x+y)%MOD;
}


ll dp[11][1034][2][1010];
ll cant_r,cant_c;
ll pot2[15];


ll f(ll r, ll mask, ll izq, ll c){
    if(c==cant_c)return 1;
    if(r==cant_r)return f(0,mask,0,c+1);
    ll &res = dp[r][mask][izq][c];
    if(res!=-1)return res;
    ll mask_aux = mask;
    ll r_viejo = 0, r_1_viejo=0;
    fore(i,0,r){
        if(i==r-1) r_1_viejo = mask_aux&1;
        mask_aux/=2;
    }
    r_viejo = mask_aux&1;
    mask_aux = mask - r_viejo*pot2[r];
    res = f(r+1,mask_aux,r_viejo,c);
    if(r==0){
        mask_aux = mask/2;
        ll abajo = mask_aux&1;
        mask_aux = mask - r_viejo*pot2[r];
        if(r_viejo==0 && abajo==0){
            mask_aux += pot2[r];
            res = add(res,f(r+1,mask_aux,r_viejo,c));
        }
    } else {
        mask_aux = mask;
        fore(i,0,r+1){
            mask_aux/=2;
        }
        ll abajo = mask_aux&1;
        mask_aux = mask - r_viejo*pot2[r];
        if(r_viejo == 0 && r_1_viejo == 0 && izq==0 && abajo==0){
            mask_aux += pot2[r];
            res = add(res, f(r+1,mask_aux,r_viejo,c));
        }
    }
   // cout << r << " " << mask << " " << izq << " " << c << " " << res << "\n";
    return res;
}


int main(){FIN;
    cin>>cant_r>>cant_c;
    pot2[0]=1;
    fore(i,1,15)pot2[i]=2*pot2[i-1];
    mset(dp,-1);
    ll res = f(0,0,0,0);
    cout << res << "\n";
    return 0;
}