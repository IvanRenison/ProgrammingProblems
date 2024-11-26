// https://codeforces.com/gym/103934/problem/E
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, efunca = b; i < efunca; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll, ll>> vii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef long double ld;

// PHI FUN
const ll LIM = 1e6 + 1;
array<ll,LIM> phi;

void calculatePhi() {
    fore(i,0,LIM) phi[i] = i&1 ? i : i/2;
    for(ll i = 3; i < LIM; i += 2) if (phi[i] == i)
        for(ll j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}

typedef array<ll, 22> T;
typedef pair<ll,ll> L;
const T tneut = {0};
const L lneut = {-1,0};//<lo seteo a, aplico phi veces>

T f(const T& a, const T& b) {
    T res = tneut;
    fore(i,0,22){
        res[i] = a[i] + b[i];
    }
    return res;
}

void apply(T& v, const L& l, ll s, ll e) {
    if(l.first != -1){
        //assert(l.second == 0);
        //lo tengo que setear
        ll acc = l.first;
        v[0] = l.first*(e-s);
        fore(i,1,22){
            acc = phi[acc];
            v[i] = acc * (e-s);
        }
        return;
    }
    //tengo que aplicar phi nomas
    v[0] = v[l.second];
    fore(i,1,22)v[i] = v[min(l.second+i,21ll)];
}

void comb(L& a, const L& b) {
    L res;
    if(b.first!=-1){
        //assert(b.second == 0);
        //seteo todo a b
        a = {b.first,0};
    }
    a = {a.first, b.second + a.second};
    if (a.first != -1) {
        while (a.second > 0) {
            a.first = phi[a.first];
            a.second--;
        }
    }
}

struct Tree {
    ll n;
    vector<T> st;
    vector<L> lazy;
    Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
    Tree(vector<T> &a) : n(SZ(a)), st(4*n), lazy(4*n, lneut){
        init(1,0,n,a);
    }
    void init(ll k, ll s, ll e, vector<T> &a) {
        lazy[k] = lneut;
        if (s + 1 == e) { st[k] = a[s]; return;}
        ll m = (s + e) / 2;
        init(2*k, s, m, a), init(2*k+1, m, e, a);
        st[k] = f(st[2*k], st[2*k+1]);
    }

    void push(ll k, ll s, ll e) {
        if(lazy[k] == lneut) return;
        apply(st[k], lazy[k], s, e);
        if (s + 1 < e) {
            comb(lazy[2*k], lazy[k]);
            comb(lazy[2*k+1], lazy[k]);
        }
        lazy[k] = lneut;
    }

    void upd(ll k, ll s, ll e, ll a, ll b, const L& v) {
        push(k, s, e);
        if (s >= b || e <= a) return;
        if (s >= a && e <= b) {
            comb(lazy[k], v);
            push(k, s, e);
            return;
        }
        ll m = (s + e) / 2;
        upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
        st[k] = f(st[2*k], st[2*k+1]);
    }

    ll query2(ll k, ll s, ll e, ll a, ll b) {
        if (s >= b || e <= a) return 0;
        push(k, s, e);
        if (s >= a && e <= b) return st[k][0];
        ll m = (s + e) / 2;
        return query2(2*k, s, m, a, b) + query2(2*k+1, m, e, a, b);
    }

    T query(ll k, ll s, ll e, ll a, ll b) {
        if (s >= b || e <= a) return tneut;
        push(k, s, e);
        if (s >= a && e <= b) return st[k];
        ll m = (s + e) / 2;
        return f(query(2*k, s, m, a, b),query(2*k+1, m, e, a, b));
    }

    void upd(ll a, ll b, const L& v) {upd(1,0,n,a,b,v); }
    T query(ll a, ll b) { return query(1,0,n,a,b); }
    ll query2(ll a, ll b) { return query2(1,0,n,a,b); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    calculatePhi();

    int n,q;
    cin>>n>>q;
    vector<T> nums(n);
    fore(_,0,n){
        T cur = tneut;
        cin>>cur[0];
        fore(i,1,22)cur[i] = phi[cur[i-1]];
        nums[_] = cur;
    };
    Tree tree(nums);
    while(q--){
        int tipo;
        cin>>tipo;
        ll s,e;
        cin>>s>>e;
        --s;
        if(tipo==1){
            tree.upd(s,e,{-1,1});
        }
        else if (tipo == 2){
            ll x;
            cin>>x;
            tree.upd(s,e,{x,0});
        }
        else{
            cout<<tree.query2(s,e)<<'\n';
        }
    }
    return 0;
}
