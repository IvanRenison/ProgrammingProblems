// https://redprogramacioncompetitiva.com/contests/2023/11

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
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(a) (a).begin(), (a).end()

struct B {
  vi bridges;

  vi num, st;
  vector<vector<ii>> ed;
  ll Time;
  template<class F>
  ll dfs(ll at, ll par, F& f) {
    ll me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        ll si = st.size();
        ll up = dfs(y, e, f);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          f(vi(st.begin() + si, st.end()));
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else { /* e is a bridge */
          bridges.push_back(e);
        }
      }
    }
    return top;
  }

  template<class F>
  void bicomps(F f) {
    num.assign(ed.size(), 0);
    fore(i,0,ed.size()) if (!num[i]) dfs(i, -1, f);
  }


  tuple<ull, vuu, vector<bool>, map<ull, ull>> buildTree(ull N, vii edges) {
    ull eid = 0;
    ed.resize(N);
    vector<vu> adj(N);

    for(auto e : edges) {
      ull u = e.first;
      ull v = e.second;
      ed[u].push_back({v, eid});
      ed[v].push_back({u, eid});
      eid++;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    ull nbc = 0;

    vector<set<ull>> comps(N);

    bicomps([&](const vi& bc) {
      for(auto eid : bc) {
        //auto [u, v] = edges[eid];
        ull u = edges[eid].first;
        ull v = edges[eid].second;
        comps[u].insert(nbc);
        comps[v].insert(nbc);
      }
      nbc++;
    });

    map<ull, ull> m;
    vuu newEdges;
    vector<bool> arts;

    ull n = 0;
    fore(i, 0, nbc) {
      arts.push_back(false);
      n++;
    }
    fore(u, 0, N) {
      const set<ull>& comp = comps[u];
      if (comp.empty() || comp.size() > 1) {
        m[u] = n;
        n++;
        arts.push_back(true);
        for(auto v : comp) {
          newEdges.push_back({m[u], v});
        }
      } else {
        ull c = *comp.begin();
        bool found_diff = false;
        for (auto v : adj[u]) {
          if (comps[v].size() == 0) {
            found_diff = true;
            goto here;
          }
          for (auto c1 : comps[v]) {
            if (c1 != c) {
              found_diff = true;
              goto here;
            }
          }
        }
      here:
        if (found_diff) {
          m[u] = n;
          n++;
          arts.push_back(true);
          for(auto v : comp) {
            newEdges.push_back({m[u], v});
          }
        } else {
          m[u] = c;
        }
      }
    }

    for(ull i : bridges) {
      //auto [u, v] = edges[i];
      ull u = edges[i].first, v = edges[i].second;
      newEdges.push_back({m[u], m[v]});
    }

    return {n, newEdges, arts, m};
  }
};

#define oper(a, b) (a + b)
#define NEUT 0
struct STree { // segment tree for min over integers
	vector<int> st;int n;
	STree(int n): st(4*n+5,NEUT), n(n) {}
	void init(int k, int s, int e, int *a){
		if(s+1==e){st[k]=a[s];return;}
		int m=(s+e)/2;
		init(2*k,s,m,a);init(2*k+1,m,e,a);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	void upd(int k, int s, int e, int p, int v){
		if(s+1==e){st[k]=v;return;}
		int m=(s+e)/2;
		if(p<m)upd(2*k,s,m,p,v);
		else upd(2*k+1,m,e,p,v);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	int query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return NEUT;
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
	}
	void init(int *a){init(1,0,n,a);}
	void upd(int p, int v){upd(1,0,n,p,v);}
	int query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(i,v);rmq.query(s,e);


constexpr ull MAXN = 1e5+1;
struct HLD {
  // Tree with path querys
  vector<vi> g;
  int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth
  void dfs1(int x){
    wg[x]=1;
    for(int y:g[x])if(y!=dad[x]){
      dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
      wg[x]+=wg[y];
    }
  }
  int curpos,pos[MAXN],head[MAXN];
  void hld(int x, int c){
    if(c<0)c=x;
    pos[x]=curpos++;head[x]=c;
    int mx=-1;
    for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
    if(mx>=0)hld(mx,c);
    for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
  }
  void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
  int query(int x, int y, STree& rmq){
    // rmq has to have the values of the edges
    int r=NEUT;
    while(head[x]!=head[y]){
      if(dep[head[x]]>dep[head[y]])swap(x,y);
      r=oper(r,rmq.query(pos[head[y]],pos[y]+1));
      y=dad[head[y]];
    }
    if(dep[x]>dep[y])swap(x,y); // now x is lca
    r=oper(r,rmq.query(pos[x],pos[y]+1));
    return r;
  }
  // for updating: rmq.upd(pos[x],v);
  // queries on edges: - assign values of edges to "child" node
  //                   - change pos[x] to pos[x]+1 in query (line 28)
};

vu solve(ull N, vii edges, vii queries) {
  ull t = queries.size();

  B b;
  // auto [n, newEdges, arts, m] = b.buildTree(N, edges);
  auto n_newEdges_arts_m = b.buildTree(N, edges);
  auto n = get<0>(n_newEdges_arts_m);
  auto newEdges = get<1>(n_newEdges_arts_m);
  auto arts = get<2>(n_newEdges_arts_m);
  auto m = get<3>(n_newEdges_arts_m);

/*   cerr << "Tree: \n";
  cerr << n << '\n';
  for (auto [u, v] : newEdges) {
    cerr << u + 1 << ' ' << v + 1 << '\n';
  }
  cerr << '\n';

  cerr << "m: \n";
  for (auto [u, v] : m) {
    cerr << u + 1 << ' ' << v + 1 << '\n';
  }
  cerr << '\n'; */

  vector<vi> adj(n);
  for (auto e : newEdges) {
    ull u = e.first, v = e.second;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  HLD hld;
  hld.g = adj;
  hld.hld_init();

  STree st(n);

  fore(u, 0, n) {
    st.upd(hld.pos[u], arts[u] ? 1 : 0);
  }

  vu ans(t);
  fore(i, 0, t) {
    //auto [u, v] = queries[i];
    ull u = queries[i].first, v = queries[i].second;
    ans[i] = hld.query(m[u], m[v], st);
    if (!arts[m[u]]) {
      ans[i]++;
    }
    if (!arts[m[v]]) {
      ans[i]++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vii edges(M);
  fore(i, 0, M) {
    ull u, v;
    cin >> u >> v;
    u--, v--;
    edges[i] = {u, v};
  }
  ull t;
  cin >> t;
  vii queries(t);
  fore(i, 0, t) {
    ull u, v;
    cin >> u >> v;
    u--, v--;
    queries[i] = {u, v};
  }

  auto ans = solve(N, edges, queries);
  fore(i, 0, ans.size()) {
    cout << ans[i] << '\n';
  }

  return EXIT_SUCCESS;
}
