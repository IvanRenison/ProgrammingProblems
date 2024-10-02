// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ll(x.size())
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
const ll NMAX = 2e5+10;

struct STree{
    vector<pair<int,int>> t;int n;
    STree(int n):n(n),t(2*n+5,{-10,-10}){}
    void upd(int p, pair<int,int> v){
        p+=n;
        for(t[p]=v;p>1;p>>=1)t[p>>1]=max(t[p],t[p^1]);
    }
    pair<int,int> query(int l, int r){
        pair<int,int> res = {-10,-10};
        for(l+=n,r+=n;l<r;l>>=1, r>>=1){
            if(l&1) res=max(res,t[l++]);
            if(r&1) res=max(res,t[--r]);
        }
        return res;
    }
};

vector<ll> g[NMAX];
ll vis[NMAX], pa[NMAX];
ll dep[NMAX];
ll ent[NMAX], sal[NMAX];
vector<ll> ord;
ll n;

void dfs(ll x){
    assert(SZ(ord)<=n);
    ent[x]=SZ(ord);
    ord.pb(x);
    for(auto i:g[x]){
        if(vis[i])continue;
        pa[i]=x;
        vis[i]=1;
        dep[i]=dep[x]+1;
        dfs(i);
    }
    sal[x]=SZ(ord);
}



int main(){FIN;
    cin>>n;
    fore(i,0,n-1){
        ll x,y;cin>>x>>y;--x;--y;
        g[x].pb(y);g[y].pb(x);
    }
    dep[0]=0;
    vis[0]=1;
    pa[0]=-1;
    dfs(0);
    assert(SZ(ord)==n);
    STree st(n);
    fore(i,0,n){
        assert(ord[ent[i]]==i);
        st.upd(ent[i],{dep[i],i});
    }
    reverse(ALL(ord));
    ll res = 0;
    fore(i,0,n){
        vector<ll> options;
        for(auto x:g[ord[i]]){
            if(x==pa[ord[i]])continue;
            options.pb(x);
        }
        if(SZ(options)==0)continue;
        if(SZ(options)==1){
            ll x = options[0];
            ii query_ans;
            while(query_ans = st.query(ent[x],sal[x]), query_ans.fst>dep[ord[i]]+1){
                auto borro = query_ans.snd;
                ++res;
                st.upd(ent[borro],{-10,-10});
            }
            continue;
        }
        ll x = options[0], y = options[1];
        if(st.query(ent[x],sal[x]).fst>st.query(ent[y],sal[y]).fst)swap(x,y);
        ll busco = st.query(ent[x],sal[x]).fst;
        ii query_ans;
        while(query_ans = st.query(ent[y],sal[y]), query_ans.fst>busco+1){
            auto borro = query_ans.snd;
            ++res;
            st.upd(ent[borro],{-10,-10});
        }
    }
    cout << res << "\n";
    return 0;
}
