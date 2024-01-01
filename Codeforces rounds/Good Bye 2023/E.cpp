// https://codeforces.com/contest/1916/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

struct STree { // example: range sum with range addition
  typedef ll T; typedef ll L; // T: data type, L: lazy type
  constexpr static T tneut = 0; constexpr static L lneut = 0; // neutrals
  T oper(T a, T b){return max(a, b);}
  T apply(T v, L l, int s, int e) {return v+l;} // new st according to lazy
  L prop(L a, L b) {return a+b;} // cumulative effect of lazy

  vector<T> st;vector<L> lazy;int n;
  STree(int n): st(4*n+5,tneut), lazy(4*n+5,lneut), n(n) {}
  void init(int k, int s, int e, const vector<T>& a){
    lazy[k]=lneut;
    if(s+1==e){st[k]=a[s];return;}
    int m=(s+e)/2;
    init(2*k,s,m,a);init(2*k+1,m,e,a);
    st[k]=oper(st[2*k],st[2*k+1]);
  }
  void push(int k, int s, int e){
    if(lazy[k] == lneut)return; // if neutral, nothing to do
    st[k]=apply(st[k], lazy[k], s, e);
    if(s+1<e){ // propagate to children
      lazy[2*k]=prop(lazy[2*k],lazy[k]);
      lazy[2*k+1]=prop(lazy[2*k+1],lazy[k]);
    }
    lazy[k]=lneut; // clear node lazy
  }
  void upd(int k, int s, int e, int a, int b, L v){
    push(k,s,e);
    if(s>=b||e<=a)return;
    if(s>=a&&e<=b){
      lazy[k]=prop(lazy[k], v); // accumulate lazy
      push(k,s,e);return;
    }
    int m=(s+e)/2;
    upd(2*k,s,m,a,b,v);upd(2*k+1,m,e,a,b,v);
    st[k]=oper(st[2*k],st[2*k+1]);
  }
  T query(int k, int s, int e, int a, int b){
    if(s>=b||e<=a)return tneut;
    push(k,s,e);
    if(s>=a&&e<=b)return st[k];
    int m=(s+e)/2;
    return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
  }
  void init(const vector<T>& a){init(1,0,n,a);}
  void upd(int a, int b, L v){upd(1,0,n,a,b,v);}
  T query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);


ull solve1(const vu& ps, const vu& as) {
  ull n = as.size();

  vector<vu> adj(n);
  fore(i, 0, n - 1) {
    adj[ps[i]].push_back(i + 1);
  }

  vuu eulerOrd;
  vector<vu> eulerOrd_pos(n);
  {
    function<void(ull)> dfs = [&](ull u) {

      if (adj[u].size() > 0) {
        ull i = eulerOrd.size();
        for (ull v : adj[u]) {
          dfs(v);
          eulerOrd.push_back({u, i});
          i = eulerOrd.size();
          eulerOrd_pos[u].push_back(i - 1);
        }
      } else {
        eulerOrd.push_back({u, eulerOrd.size()});
        eulerOrd_pos[u].push_back(eulerOrd.size() - 1);
      }
    };

    dfs(0);
  }

  vu lastWithSame(n, inf);

  {
    vu lastColors(n, inf);

    function<void(ull)> dfs = [&](ull u) {
      ull last = lastColors[as[u]];
      lastWithSame[u] = last;

      lastColors[as[u]] = u;

      for (ull v : adj[u]) {
        dfs(v);
      }

      lastColors[as[u]] = last;
    };

    dfs(0);
  }

  vector<vu> lastWithSame_par(n);
  fore(u, 0, n) {
    if (lastWithSame[u] != inf) {
      lastWithSame_par[lastWithSame[u]].push_back(u);
    }
  }

  STree st(eulerOrd.size());

  ull ans = 0;

  function<void(ull)> dfs = [&](ull u) {

    for (ull v : adj[u]) {
      dfs(v);
    }

    for (ull j : eulerOrd_pos[u]) {
      auto [v, i] = eulerOrd[j];
      st.upd(i, j + 1, 1);
    }

    for (ull v : lastWithSame_par[u]) {
      for (ull j : eulerOrd_pos[v]) {
        auto [w, i] = eulerOrd[j];
        st.upd(i, j + 1, -1);
      }
    }

    ull son0 = 1, son1 = 0;
    for (ull j : eulerOrd_pos[u]) {
      auto [v, i] = eulerOrd[j];
      ull val = st.query(i, j + 1);
      if (val > son0) {
        son1 = son0;
        son0 = val;
      } else if (val > son1) {
        son1 = val;
      }
    }

    ans = max(ans, son0 * son1);

  };

  dfs(0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu ps(n - 1), as(n);
    for (ull& p : ps) {
      cin >> p;
      p--;
    }
    for (ull& a : as) {
      cin >> a;
      a--;
    }

    auto ans = solve1(ps, as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
