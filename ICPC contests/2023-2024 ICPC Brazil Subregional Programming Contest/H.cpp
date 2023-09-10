// https://codeforces.com/gym/104555/problem/H
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

#define NEUT 0LL

struct STree{
    vector<ll> t;int n;
    STree(int n):n(n),t(2*n+5,NEUT){}
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



int main(){FIN;
    ll n,s;cin>>n>>s;
    vector<pair<pair<ll,ll>,ll>> a(n);
    fore(i,0,n)cin>>a[i].fst.fst>>a[i].fst.snd>>a[i].snd;
    sort(ALL(a));
    STree st_q(n),st_f(n);
    for(int i = n-1; i>=0;--i){
        ll pos_l = lower_bound(ALL(a),make_pair(make_pair(a[i].fst.fst+1,0LL),0LL))-a.begin();
        ll pos_r = lower_bound(ALL(a),make_pair(make_pair(a[i].fst.snd+1,0LL),0LL))-a.begin();
        ll que = st_q.query(pos_l, pos_r);
        // cout << que << " ";
        que -= a[i].snd;
        que -= s*a[i].fst.fst;
        ll que_2 = st_f.query(pos_r,n);
        que_2 -= a[i].snd;
        que_2+= s*(a[i].fst.snd-a[i].fst.fst+1);
        st_f.upd(i,max(que,que_2));
        st_q.upd(i,max(que,que_2)+s*(a[i].fst.fst));
    }
    cout << st_f.query(0,n) << "\n";
    return 0;
}