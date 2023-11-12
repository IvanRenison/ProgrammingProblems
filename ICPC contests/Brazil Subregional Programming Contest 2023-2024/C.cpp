// https://codeforces.com/gym/104555/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll NMAX=1e5+10;


#define NEUT 0LL

struct STree{
    vector<ll> t;ll n;
    STree(ll n):n(n),t(2*n+5,NEUT){}
    void upd(int p, ll v){
        p+=n;
        for(t[p]=v;p>1;p>>=1) t[p>>1]=max(t[p],t[p^1]);
    }
    ll query(int l, int r){
        ll res=NEUT;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1) res=max(res,t[l++]);
            if(r&1) res=max(res,t[--r]);
        }
        return res;
    }
};

vector<ll> g[NMAX];
ll res[NMAX];
vector<ll> a;
vector<pair<ll,ll>> a_sor;
ll n;

void dfs(ll x, STree &st){
    fore(i,0,SZ(g[x])){
        ll posi = lower_bound(ALL(a_sor),make_pair(a[g[x][i]],0LL))-a_sor.begin();
        ll que = st.query(0,posi);
        ll que_2 = st.query(0,n);
        // cout << que << " " << que_2 << "\n";
        res[g[x][i]] = max(que+1,que_2);
        posi = lower_bound(ALL(a_sor),make_pair(a[g[x][i]],g[x][i]))-a_sor.begin();
        st.upd(posi,que+1);
        dfs(g[x][i],st);
    }
    ll pos = lower_bound(ALL(a_sor),make_pair(a[x],x))-a_sor.begin();
    st.upd(pos,0);
}

int main(){FIN;
    cin>>n;
    fore(i,0,n-1){
        ll p;cin>>p;--p;
        g[p].pb(i+1);
    }
    a.resize(n);a_sor.resize(n);
    fore(i,0,n){
        cin>>a_sor[i].fst;
        a_sor[i].snd=i;
        a[i]=a_sor[i].fst;
    }
    sort(ALL(a_sor));
    ll pos = lower_bound(ALL(a_sor),make_pair(a[0],0LL))-a_sor.begin();
    STree st(n);
    st.upd(pos,1);
    dfs(0,st);
    fore(i,1,n){
        cout << res[i] << " ";
    }
    cout << "\n";
    return 0;
}