// https://codeforces.com/gym/104172/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<bool> vb;

const ll inf = 1ll << 60;

struct T {
  ll m, count;
};
typedef ll L;
constexpr static T tneut = {inf, 0};
constexpr static L lneut = 0;
T f(T a, T b){
  if (a.m == b.m) {
    return {a.m, a.count + b.count};
  } else if (a.m < b.m) {
    return a;
  } else {
    return b;
  }
}
T apply(T v, L l, ll s, ll e){
  v.m += l;
  return v;
}
L comb(L a, L b){return a + b;}

struct Tree{
    ll n;
    vector<T> st;
    vector<L> lazy;
    Tree(ll n) : n(n), st(4*n,tneut), lazy(4*n,lneut){}
    Tree(vector<T> a) : n(SZ(a)), st(4*n), lazy(4*n, lneut) {
      init(1, 0, n, a);
    }
    void init(ll k, ll s, ll e, vector<T>& a) {
      lazy[k] = lneut;
      if (s + 1 == e) {
        st[k] = a[s];
        return;
      }
      ll m = (s + e) / 2;
      init(2*k, s, m, a), init(2*k+1, m, e, a);
      st[k] = f(st[2*k], st[2*k+1]);
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
        if(s>=a && e<=b) return st[k];
        ll m = (s + e) / 2;
        return f(query(2*k, s, m, a, b), query(2*k+1, m, e, a, b));
    }

    void upd(ll a, ll b, L v) {
      upd(1, 0, n, a, b, v);
    }
    T query(ll a, ll b) {
      return query(1, 0, n, a, b);
    }
};






const ll a_max = 1e6;

ll solve(ll k, vi& as) {
  ll n = as.size();

  vector<vi> aps(a_max);
  fore(i, 0, n) {
    aps[as[i]].push_back(i);
  }

  ll ans = 0;
  Tree t(vector<T>(n, {0, 1}));


  fore(r, 0, n) {
    ll a = as[r];
    ll x = lower_bound(ALL(aps[a]), r) - aps[a].begin();
    if (x + 1 >= k) {
      ll i0 = x + 1 == k ? 0 : aps[a][x - k] + 1;
      ll i1 = aps[a][x + 1 - k] + 1;
      t.upd(i0, i1, 1);
      if (x + 1 > k) {
        ll i = x == k ? 0 : aps[a][x - k - 1] + 1;
        t.upd(i, i0, -1);
      }
    }

    T val = t.query(0, r + 1);
    assert(val.m >= 0);
    if (val.m == 0) {
      ans += val.count;
    }
  }

  //ans = n * (n - 1) / 2 - ans;

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, k;
  cin >> n >> k;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
    a--;
  }

  cout << solve(k, as) << '\n';
}
