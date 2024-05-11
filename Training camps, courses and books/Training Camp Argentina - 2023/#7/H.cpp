// https://codeforces.com/group/hzSLIARNBN/contest/467095/problem/H

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

typedef ll T;
T oper(T a, T b) {
  return min(a, b);
}
const T NEUT = inf;
struct STree { // persistent segment tree for min over integers
  vector<T> st; vector<ll> L, R; ll n,sz,rt;
  STree(ll n): st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),sz(1){}
  ll new_node(T v, ll l=0, ll r=0){
    ll ks=SZ(st);
    st.push_back(v);L.push_back(l);R.push_back(r);
    return ks;
  }
  /* ll init(ll s, ll e, T *a){ // not necessary in most cases
    if(s+1==e)return new_node(a[s]);
    ll m=(s+e)/2,l=init(s,m,a),r=init(m,e,a);
    return new_node(oper(st[l],st[r]),l,r);
  } */
  ll upd(ll k, ll s, ll e, ll p, T v){
    ll ks=new_node(st[k],L[k],R[k]);
    if(s+1==e){st[ks]=v;return ks;}
    ll m=(s+e)/2,ps;
    if(p<m)ps=upd(L[ks],s,m,p,v),L[ks]=ps;
    else ps=upd(R[ks],m,e,p,v),R[ks]=ps;
    st[ks]=oper(st[L[ks]],st[R[ks]]);
    return ks;
  }
  T query(ll k, ll s, ll e, ll a, ll b){
    if(e<=a||b<=s)return NEUT;
    if(a<=s&&e<=b)return st[k];
    ll m=(s+e)/2;
    return oper(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
  //ll init(T *a){return init(0,n,a);}
  ll upd(ll k, ll p, T v){return rt=upd(k,0,n,p,v);}
  ll upd(ll p, T v){return upd(rt,p,v);} // update on last root
  T query(ll k,ll a, ll b){return query(k,0,n,a,b);};
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);

vuu dfsOrder(ull r, const vector<vu>& adj) {
  ull n = adj.size();

  vuu ord(n);

  ull i = 0;
  function<void(ull, ull)> dfs = [&](ull u, ull p) {
    ord[u].first = i;
    i++;

    for (ull v : adj[u]) {
      if (v != p) {
        dfs(v, u);
      }
    }

    ord[u].second = i;
  };

  dfs(r, inf);

  return ord;
}

vu solve(ull r, const vuu& edges, const vu& as, const vuu& queries) {
  ull n = as.size(), q = queries.size();

  vector<vu> adj(n);
  for (const auto& [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<vu> levels = {{r}};

  vu dep(n, inf);

  dep[r] = 0;

  while (!levels.back().empty()) {
    ull d = levels.size();
    levels.push_back({});

    for (ull u : levels[d - 1]) {
      for (ull v : adj[u]) {
        if (dep[v] == inf) {
          dep[v] = d;
          levels.back().push_back(v);
        }
      }
    }
  }

  levels.pop_back();

  vuu ord = dfsOrder(r, adj);

  STree st(n);

  vu versions(levels.size());

  fore(l, 0, levels.size()) {
    ull v = inf;
    for (ull u : levels[l]) {
      v = st.upd(ord[u].first, as[u]);
    }

    versions[l] = v;
  }

  ull last = 0;
  vu ans(q);
  fore(i, 0, q) {
    auto [p, q] = queries[i];
    ull x = (p + last) % n;
    ull k = (q + last) % n;

    ull v = versions[min(levels.size() - 1ull, dep[x] + k)];

    last = st.query(v, ord[x].first, ord[x].second);

    ans[i] = last;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, r;
  cin >> n >> r;
  r--;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }
  vuu edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    --u, --v;
  }

  ull m;
  cin >> m;
  vuu queries(m);
  for (auto& [p, q] : queries) {
    cin >> p >> q;
  }

  vu ans = solve(r, edges, as, queries);
  for (ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
