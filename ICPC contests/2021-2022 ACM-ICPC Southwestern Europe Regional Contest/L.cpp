// https://codeforces.com/contest/1662/problem/L
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mste(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

#define NEUT 0


struct STree{
    vector<int> t;int n;
    STree(int n): n(n),t(2*n+5,NEUT){}
    void upd(int p, int v){
        p+=n;for(t[p]=v;p>1;p>>=1) t[p>>1]=max(t[p],t[p^1]);
    }
    int query(int l, int r){
        int res = NEUT;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1) res=max(res,t[l++]);
            if(r&1) res=max(res,t[--r]);
        }
        return res;
    }
};



int main(){FIN;
    ll N,v;cin>>N>>v;
    vector<ll> t_temp(N);
    vector<ll> a_temp(N);
    fore(i,0,N){
        cin>>t_temp[i];
    }
    fore(i,0,N)cin>>a_temp[i];

    vi a, t;
    fore(i,0,N) {
      if (abs(a_temp[i]) <= v*t_temp[i]) {
        a.push_back(a_temp[i]), t.push_back(t_temp[i]);
      }
    }
    ll n = a.size();
    vector<pair<ll,ll>> arr(n);
    vector<ll> custom(n);
    fore(i,0,n){
        arr[i]={a[i]+v*t[i],v*t[i]-a[i]};
        custom[i]=v*t[i]-a[i];
    }
    sort(ALL(arr));sort(ALL(custom));
    STree st(n);
    for(int i = n-1;i>=0;--i){
        ll seg = arr[i].snd;
        ll posi = lower_bound(ALL(custom),seg)-custom.begin();
        ll maxi = st.query(posi,n);
        st.upd(posi,maxi+1);
    }
    cout << st.query(0,n) << "\n";
    return 0;
}
