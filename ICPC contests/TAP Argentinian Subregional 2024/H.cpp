#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) (ll)x.size()
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef long double ld;


struct Data {
    ll count;
    ld val;
};
typedef vector<Data> vd;

struct Reroot{
    ll n;
    vector<vi> &g;
    vd &neuts;
    vi &probs;

    Data finalize(const Data &a, ll p, ll ei) {
        ll sum = a.count + probs[p];
        ld val = sum == 0 ? 0 : (ld)a.count / (ld) sum * (1.0 + a.val);
        return {sum, val};
    }
    void acc(Data &p_ans, const Data &c_ans, ll p, ll ei){
        ll sum = p_ans.count + c_ans.count;
        ld val = sum == 0 ? 0 : (ld)p_ans.count / (ld)sum * p_ans.val + (ld)c_ans.count / (ld)sum * c_ans.val;
        p_ans.count = sum;
        p_ans.val = val;
    }

    vd root_dp;
    vector<vd> fdp, bdp;
    Reroot(vector<vi>&g, vd&neuts, vi& probs) : n(SZ(g)), g(g), neuts(neuts), probs(probs), root_dp(n), fdp(n), bdp(n){}
    void reroot(){
        if(n==1){root_dp[0]=finalize(neuts[0],0,-1);return;}
        vd dp = neuts, e(n);vi o, p(n);o.reserve(n), o.pb(0);
        fore(i,0,n)for(ll v : g[o[i]]) if(v!=p[o[i]])
            p[v]=o[i],o.pb(v);
        reverse(ALL(o));
        for(ll u : o){
            ll pei = -1;
            fore(ei,0,SZ(g[u])) if(g[u][ei]==p[u]) pei=ei;
            else acc(dp[u],dp[g[u][ei]],u,ei);
            dp[u]=finalize(dp[u],u,pei);
        }
        reverse(ALL(o));
        for(ll u : o){
            dp[p[u]] = dp[u];
            fdp[u].reserve(SZ(g[u])), bdp[u].reserve(SZ(g[u]));
            for(ll v : g[u]) fdp[u].pb(dp[v]);
            ex(e,fdp[u],neuts[u],u);
            fore(i,0,SZ(fdp[u]))bdp[u].pb(finalize(e[i],u,i));
            acc(e[0],fdp[u][0],u,0);
            root_dp[u]=finalize(n>1?e[0]:neuts[u],u,-1);
            fore(i,0,SZ(g[u]))dp[g[u][i]]=bdp[u][i];
        }
    }
    void ex( vd&e, vd&a, Data &ne, ll v){
        ll d = SZ(a);fill(begin(e),begin(e)+d,ne);
        for(ll b = __bit_width((unsigned)d)-1;b>=0;b--){
            for(ll i = d-1;i>=0;--i)
                e[i]= e[i>>1];
            fore(i,0,d-(d&!b))
                acc(e[(i>>b)^1],a[i],v,i);
        }
    }
};

typedef ll T; typedef ll L;
constexpr static T tneut = -1; constexpr static L lneut = -1;
T f(T a, T b){
    if (a == -1) return b;
    else return a;
}
T apply(T v, L l, ll s, ll e){
    if (l == -1) return v;
    else return l;
}
L comb(L a, L b){
    if (b == -1) return a;
    else return b;
}

struct Tree {
    ll n;
    vector<T> st;
    vector<L> lazy;
    Tree(ll n): n(n),st(4*n,tneut),lazy(4*n,lneut){}
    Tree(vector<T>&a):n(SZ(a)),st(4*n),lazy(4*n){
        init(1,0,n,a);
    }
    void init(ll k, ll s, ll e, vector<T> &a){
        lazy[k]=lneut;
        if(s+1==e){st[k]=a[s];return;}
        ll m = (s+e)/2;
        init(2*k,s,m,a);init(2*k+1,m,e,a);
        st[k]=f(st[2*k],st[2*k+1]);
    }
    void push(ll k, ll s, ll e){
        if(lazy[k]==lneut)return;
        st[k]=apply(st[k],lazy[k],s,e);
        if(s+1<e){
            lazy[2*k]=comb(lazy[2*k],lazy[k]);
            lazy[2*k+1]=comb(lazy[2*k+1],lazy[k]);
        }
        lazy[k]=lneut;
    }
    void upd(ll k, ll s, ll e, ll a, ll b, L v){
        push(k,s,e);
        if(s>=b||e<=a)return;
        if(s>=a && e<=b){
            lazy[k]=comb(lazy[k],v);
            push(k,s,e);
            return;
        }
        ll m = (s+e)/2;
        upd(2*k,s,m,a,b,v);upd(2*k+1,m,e,a,b,v);
        st[k]=f(st[2*k],st[2*k+1]);
    }
    T query(ll k, ll s, ll e, ll a, ll b){
        if(s>=b || e<=a)return tneut;
        push(k,s,e);
        if(s>=a && e<=b)return st[k];
        ll m = (s+e)/2;
        return f(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
    }
    void upd(ll a, ll b, L v){upd(1,0,n,a,b,v);}
    T query(ll a, ll b){return query(1,0,n,a,b);}
};


ll compress(viiii& quads , vii& points) {
    vi a;
    a.reserve(SZ(quads) * 2 + SZ(points));
    for(auto &[x0, y0, x1, y1] : quads) {
        a.pb(x0);
        a.pb(x1);
    }
    for(auto &[x, y] : points) {
        a.pb(x);
    }
    sort(ALL(a));
    a.erase(unique(ALL(a)), a.end());
    for(auto &[x0, y0, x1, y1] : quads) {
        x0 = lower_bound(ALL(a), x0) - a.begin();
        x1 = lower_bound(ALL(a), x1) - a.begin();
    }
    for(auto &[x, y] : points) {
        x = lower_bound(ALL(a), x) - a.begin();
    }
    return SZ(a);
}


ld solve(viiii& cuads, vii& points, ll X_max) {
    ll N = cuads.size(), M = points.size();

    vector<tuple<ll, ll, ll, ll, bool, bool>> events;
    events.reserve(2*N+M);
    fore(i, 0, N) {
        auto [X0, Y0, X1, Y1] = cuads[i];
        events.pb({Y0, X0, X1, i + 1, false, false});
        events.pb({Y1, X0, X1, i + 1, true, false});
    }
    for (auto [X, Y] : points) {
        events.pb({Y, X, -1, -1, false, true});
    }
    sort(ALL(events));

    vi neu(X_max, 0);
    Tree t(neu);

    vi pars(N + 1), probs(N + 1);

    for (auto [Y, X0, X1, i, time, ty] : events) {
        if (ty) {
            ll j = t.query(X0, X0 + 1);
            probs[j]++;
        } else if (!time) {
            ll p = t.query(X0, X0 + 1);
            pars[i] =  p;
            t.upd(X0, X1 + 1, i);
        } else {
            ll p = pars[i];
            t.upd(X0, X1 + 1, p);
        }
    }

    vector<vi> adj(N + 1);
    fore(i, 1, N + 1) {
        ll p = pars[i];
        adj[p].pb(i);
        adj[i].pb(p);
    }

    vector<Data> neuts(N + 1, {0, 0});

    Reroot re(adj, neuts, probs);
    re.reroot();

    ld ans = 0.0;
    fore(i, 0, N + 1) {
        ld pr = (ld)probs[i] / (ld)M;
        ld this_ans = re.root_dp[i].val;
        ans += this_ans * pr;
    }


    return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    ll N, M;
    cin >> N >> M;

    viiii cuads(N);
    for (auto& [X0, Y0, X1, Y1] : cuads) {
        cin >> X0 >> Y0 >> X1 >> Y1;
    }
    vii points(M);
    for (auto& [X, Y] : points) {
        cin >> X >> Y;
    }
    ll X_max = compress(cuads, points);

    ld ans = solve(cuads, points, X_max + 1);
    cout << setprecision(15) << fixed << ans << '\n';


}
