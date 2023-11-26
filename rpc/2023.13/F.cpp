// https://redprogramacioncompetitiva.com/contests/2023/13
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
const ll NMAX = 2e5+10;
const ll MOD = 1e9+7;

ll pa[NMAX];
vector<ll> g[NMAX];
set<ll> np[NMAX];
ll n,m;


void dsu_init(){
    fore(i,0,n){
        pa[i]=i;
        fore(j,0,SZ(g[i])){
            np[i].insert(g[i][j]);
        }
    }
}

ll find(ll pos){
    if(pa[pos]!=pos)pa[pos]=find(pa[pos]);
    return pa[pos];
}

ll join(ll x, ll y){
    ll pax = find(x); ll pay = find(y);
    if(pax==pay)return false;
    if(SZ(np[pay])>SZ(np[pax]))swap(pay,pax);
    for(auto i:np[pay]){
        np[pax].insert(find(i));
        np[find(i)].insert(pax);
        np[find(i)].erase(pay);
    }
    pa[pay]=pax;
    return true;
}


int main(){FIN;
    cin>>n>>m;
    fore(i,0,m){
        ll x,y;cin>>x>>y;--x;--y;
        g[x].pb(y);g[y].pb(x);
    }
    dsu_init();
    ll q;cin>>q;
    while(q--){
        ll x,y;cin>>x>>y;--x;--y;
        if(find(x)==find(y)){
            cout << "NEXT\n";
            continue;
        }
        ll pax = find(x), pay=find(y);
        if(np[pax].count(pay) || np[pay].count(pax)){
            cout << "AVOID WAR\n";
            continue;
        }
        cout << "FOR THE PEACE\n";
        join(x,y);
    }
    return 0;
}
