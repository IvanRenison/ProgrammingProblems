// https://codeforces.com/gym/104768/problem/K
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,aei=b;i<aei;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define imp(v) {for(auto dfjg:v)cout<<dfjg<<" ";cout<<endl;}
using namespace std;
typedef int ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

const ll C=21;

vector<ll> operator*(vector<ll> &a, vector<ll> &b){
    vector<ll>c(SZ(a));
    fore(i,0,SZ(a)){
        c[i]=a[b[i]];
    }
    return c;
}
ll fc[12];
ll rec(vi &a){
    if(SZ(a)==1)return 0;
    // cout<<"rec "; imp(a);
    ll x=0;
    ll sz=SZ(a);
    fore(i,0,sz-1)x+=a[i]<a.back();
    a.pop_back();
    ll ans = fc[sz-1]*x+rec(a);
    return ans;
}
ll num(vi a){
    return rec(a);}
ll bitmask(vector<vi>&a){
    ll n = a[0].size(), m = a.size();
    vector<vi>h;
    fore(mk,1,1ll<<m){
        vi x;
        fore(i,0,n)x.pb(i);
        fore(i,0,m)if(mk>>i&1)x=x*a[i];
        h.pb(x);
    }
    ll res=1;
    sort(ALL(h));
    fore(i,1,SZ(h))res+=(h[i]!=h[i-1]);
    // fore(j,0,SZ(h)){
    //     imp(h[j]);
    // }
    return res;
}

ll brute(vector<vi>&a){
    ll n = a[0].size(), m = a.size();
    assert(n<12);
    vector<vi>h(fc[n]);
    h[num(a[0])]=a[0];
    ll res=1;
    fore(i,1,m){
        if(res==fc[n])break;
        vector<vi>add={a[i]};
        fore(j,0,SZ(h))if(SZ(h[j]))add.pb(h[j]*a[i]);
        for(auto &i:add){
            ll id=num(i);
            if(!SZ(h[id]))h[id]=i,res++;
        }
    }
    // fore(j,0,SZ(h)){
    //     imp(h[j]);
    // }
    return res;
}


int main(){
    ios::sync_with_stdio(0),cin.tie(0);
     fc[0]=1;
    fore(i,1,12)fc[i]=fc[i-1]*i;
    // cout<<num({4,3,2,1,0})<<"\n"<<num({3,4,2,1,0})<<"\n";
    ll n,m;
    cin>>n>>m;
    vector<vi>a(m,vi(n));
    fore(i,0,m)fore(j,0,n){
        cin>>a[i][j];
        a[i][j]--;
    }

   if(m<=C){

        cout<<bitmask(a)<<"\n";
    }
   else {

        cout<<brute(a)<<"\n";
    }
    return 0;
    fore(_, 0, 10000) {
        ll n = rand() % 10 + 1, m = rand() % 10 + 1;
        vector<vi> a(m, vi(n));
        fore(i, 0, m) {
            fore(j, 0, n) {
                a[i][j] = j;
            }
            random_shuffle(ALL(a[i]));
        }

        ll ans0 = brute(a);
        ll ans1 = bitmask(a);

        if (ans0 != ans1) {
            cerr << n << ' ' << m << '\n';
            fore(i, 0, m) {
                fore(j, 0, n) {
                    cerr << a[i][j] << ' ';
                }
                cerr << '\n';
            }
            return 1;
        }
    }
}