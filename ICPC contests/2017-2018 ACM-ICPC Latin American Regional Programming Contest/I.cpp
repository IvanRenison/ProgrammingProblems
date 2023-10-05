// https://codeforces.com/gym/101889
#include<bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef pair<ull,ull> uu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<ull> vu;
typedef vector<uuu> vuuu;
typedef vector<uu> vuu;

struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  bool sameSet(ll a, ll b) {return find(a) == find(b);}
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]);}
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};


struct RMQ {
  vector<vu> jmp;
  RMQ(const vu& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j, 0, SZ(jmp[k]))
        jmp[k][j] = max(jmp[k-1][j], jmp[k-1][j+pw]);
    }
  }
  ull query(int a, int b) {
    if (a >= b) {
      return 0;
    }
    int dep = 31 - __builtin_clz(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

/* struct LCA {
  ll T = 0;
  vi time, path, ret;
  RMQ rmq;

  LCA(const vector<vi>& C) : time(SZ(C)), rmq(dfs(C, 0, -1), ret) {}
  void dfs( const vector<vi>& C, ll v, ll par) {
    Time[v] = T++;
  }
} */

struct HLD {
  vector<vi> g;
  vi wg, dad, dep, pos, head;
  ll curpos;
  RMQ rmq;
  HLD(const vector<vi>& g, const vu& V) : g(g), wg(SZ(g)), dad(SZ(g)),
    dep(SZ(g)), pos(SZ(g)), head(SZ(g)), rmq({}) {
      dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);
      rmq = RMQ(get_RMQ(V));
  }
  vu get_RMQ(const vu& V) {
    vu vs(SZ(V));
    fore(i,0,SZ(V)) {
      vs[pos[i]] = V[i];
    }
    return vs;
  }
  void dfs1(ll x) {
    wg[x]=1;
    for(ll y:g[x])if(y!=dad[x]){
      dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
      wg[x]+=wg[y];
    }
  }
  void hld(ll x, ll c) {
    if (c<0)c=x;
    pos[x]=curpos++;head[x]=c;
    ll mx=-1;
    for(ll y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
    if(mx>=0)hld(mx,c);
    for(ll y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
  }
  ull query(ll x, ll y){
    ull r = 0;
    while(head[x]!=head[y]){
      if(dep[head[x]]>dep[head[y]])swap(x,y);
      r=max(r,rmq.query(pos[head[y]],pos[y]+1));
      y=dad[head[y]];
    }
    if(dep[x]>dep[y])swap(x,y);
    r=max(r,rmq.query(pos[x]+1,pos[y]+1));
    return r;
  }
};



struct Problem {
  HLD* hld;
  ull base_cost;
  map<uu, ull> medges;
  Problem(ull N, const vuuu& edges) {
    ull M = edges.size();
    vuuu c_edges(M);
    fore(i, 0, M) {
      auto [u, v, c] = edges[i];
      c_edges[i] = {c, u, v};
      medges[{u, v}] = c;
    }
    sort(ALL(c_edges));

    vuuu tree_edges;

    UF uf(N);
    base_cost = 0;

    fore(i, 0, M) {
      auto [c, u, v] = c_edges[i];
      if (uf.join(u, v)) {
        tree_edges.push_back({u, v, c});
        base_cost += c;
      }
    }

    ull m =  tree_edges.size();
    assert(m+1 == N);
    vector<vi> adj(N);
    vector<vuu> tree_adj(N);

    fore(i, 0, m) {
      auto [u, v, c] = tree_edges[i];
      tree_adj[u].push_back({v, i}), tree_adj[v].push_back({u, i});
      adj[u].push_back(v), adj[v].push_back(u);
    }

    vu vals(N, -1);
    vals[0]=0;

    vu stack = {0};

    while(!stack.empty()) {
      ull u = stack.back();
      stack.pop_back();

      for(auto [v, i] : tree_adj[u]) {
        if (vals[v] == -1) {
          vals[v] = get<2>(tree_edges[i]);

          stack.push_back(v);
        }
      }
    }

    hld = new HLD(adj, vals);


  }

  ull query(ull u, ull v) {
    ull d = hld->query(u, v);
    ull n = medges[{u, v}];
    return base_cost + n - d;
  }

};

int main(){FIN;

  ull N, R;
  cin >> N >> R;
  vuuu edges(R);
  for(auto& [u, v, c] : edges) {
    cin >> u >> v >> c;
    u--, v--;
  }

  Problem P(N, edges);

  ull Q;
  cin >> Q;
  while(Q--) {
    ull u, v;
    cin >> u >> v;
    u--, v--;
    cout << P.query(u, v) << '\n';
  }

  return 0;
}