// https://redprogramacioncompetitiva.com/contests/2023/13

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;
typedef long double ld;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define forp(xs, a, b) for (auto &[a, b] : xs)
#define prnt(x) cout << (x) << "\n"
#define vvii vector<vii>
#define vvi vector<vi>
#define vd vector<ld>
#define vvd vector<vd>
#define vc vector<char>
#define vvc vector<vector<char>>

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl
#define SZ(x) (x.size())

#define NEUT 0
ull oper(ull x, ull y) {
  return x + y;
}
struct STree{
  vi t; int n;
  STree(int n):n(n),t(2*n+5,NEUT){}
  void upd(int p, ull v){
    p+=n;
    for(t[p]=v;p>1;p>>=1) t[p>>1]=oper(t[p],t[p^1]);
  }
  ull query(int l, int r){ // [l, r)
    ull res=NEUT;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1) res=oper(res,t[l++]);
      if(r&1) res=oper(res,t[--r]);
    }
    return res;
  }
};

// Tree with values updates and path querys
struct HLD {
  vector<vi> g;
  vi wg,dad,dep, // weight,father,depth
              pos,head;
  int curpos;STree rmq;
  HLD(const vector<vi>& g) : g(g), wg(SZ(g)), dad(SZ(g)),
      dep(SZ(g)), pos(SZ(g)), head(SZ(g)), rmq(SZ(g)) {
    dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);
  }
  void dfs1(int x){
    wg[x]=1;
    for(int y:g[x])if(y!=dad[x]){
      dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
      wg[x]+=wg[y];
    }
  }
  void hld(int x, int c){
    if(c<0)c=x;
    pos[x]=curpos++;head[x]=c;
    int mx=-1;
    for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
    if(mx>=0)hld(mx,c);
    for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
  }
  ull query(ull x, ull y){
    ull r=NEUT;
    while(head[x]!=head[y]){
      if(dep[head[x]]>dep[head[y]])swap(x,y);
      r=oper(r,rmq.query(pos[head[y]],pos[y]+1));
      y=dad[head[y]];
    }
    if(dep[x]>dep[y])swap(x,y); // now x is lca
    r=oper(r,rmq.query(pos[x],pos[y]+1));
    return r;
  }
  void upd(int x, ull v){rmq.upd(pos[x],v);}
};
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 34)

vu solve(vu hs, vuu edges, vuuu querys) {
  ull n = SZ(hs), q = SZ(querys);

  vector<vi> adj(n);
  for(auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  HLD hld(adj);

  vuu his(n);
  fore(i, 0, n) {
    his[i] = {hs[i], i};
  }

  sort(all(his));

  vuuuu x_ab_i(q);
  fore(i, 0, q) {
    auto [a, b, x] = querys[i];
    x_ab_i[i] = {x, a, b, i};
  }

  sort(all(x_ab_i));

  vu ans(q);

  ull i = 0; // hs
  fore(j, 0, q) {
    auto [x, a, b, k] = x_ab_i[j];

    while(i < n && his[i].first <= x) {
      auto [h, u] = his[i];
      hld.upd(u, 1);
      i++;
    }

    //assert(a < n && b < n);
    ans[k] = hld.query(a, b);
  }

  return ans;
}

ll randin(ll a, ll b) {
    static random_device rd;
    static mt19937_64 gen(rd());
    uniform_int_distribution<ll> dis(a, b - 1);
    return dis(gen);
}

#define fori(xs, x) for (auto &x : xs)


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;

  vu hs(n);
  fore(i, 0, n) {
    cin >> hs[i];
  }

  vuu edges(n - 1);
  fore(i, 0, n - 1) {
    ull u, v;
    cin >> u >> v;
    u--, v--;
    edges[i] = {u, v};
  }

  vuuu querys(q);
  fore(i, 0, q) {
    ull a, b, x;
    cin >> a >> b >> x;
    a--, b--;
    querys[i] = {a, b, x};
  }

  auto ans = solve(hs, edges, querys);
  for(ull a : ans) {
    cout << a << '\n';
  }

/*   fore(_, 0, 10000) {
    ll n = 100;
    vvi tree(n);
    fore(i, 1, n) {
        ll p = randin(0, i);
        tree[p].pb(i);
    }

    vi perm(n);
    iota(all(perm), 0);
    static random_device rd;
    static mt19937_64 gen(rd());
    shuffle(all(perm), gen);

    fori(tree, xs) {
        fori(xs, x) x = perm[x];
    }

    vuu edges;
    fore(i, 0, n) {
        fori(tree[i], x) edges.pb(mp(i, x));
    }

    vu hs(n);
    fore(i, 0, n) {
      hs[i] = rand() % 100 + 1;
    }
    ull q = 100;
    vuuu querys(q);
    fore(i, 0, q) {
      ull a = rand() % n, b = rand() % n, x = rand() % 100 + 1;
      querys[i] = {a, b, x};
    }

    auto ans = solve(hs, edges, querys);
    cout << "PASSES TEST " << _ << "\n";
  }
 */
  return EXIT_SUCCESS;
}
