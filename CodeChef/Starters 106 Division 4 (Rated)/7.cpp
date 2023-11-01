// https://www.codechef.com/problems/FIZZBUZZ2307

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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

struct STree { // example: range sum with range addition
	typedef ull T; typedef ull L; // T: data type, L: lazy type
	constexpr static T tneut = 0; constexpr static L lneut = 0; // neutrals
	T oper(T a, T b){return a+b;}
	T apply(T v, L l, int s, int e) {return v+l*(e-s);} // new st according to lazy
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

vi topoSort(const vector<vi>& gr) {
	vi indeg(gr.size()), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	fore(i,0,gr.size()) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

vu solve1(vuu edges) {
  ull N = edges.size() + 1;
  vector<vi> adj_fordward(N), adj_backward(N);

  for(auto [u, v] : edges) {
    adj_fordward[u].push_back(v);
    adj_backward[v].push_back(u);
  }

  auto topo = topoSort(adj_fordward);

  vu dp_depth(N);
  for(auto u : topo) {
    for(auto v : adj_backward[u]) {
      dp_depth[u] = dp_depth[v] + 1;
    }
  }

  reverse(all(topo));

  vu dp_n_suns(N);

  for(auto u : topo) {
    dp_n_suns[u] = 0;
    for(auto v : adj_fordward[u]) {
      dp_n_suns[u] += dp_n_suns[v] + 1;
    }
  }


  STree anst(N);
  fore(u, 0, N) {
    ull m = dp_depth[u];
    ull M = N - dp_n_suns[u] - 1;
    anst.upd(m, M + 1, 1);
  }

  vu ans(N);
  fore(u, 0, N) {
    ans[u] = anst.query(u, u + 1);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vuu edges(N-1);
    for(auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    auto ans = solve1(edges);
    for(ull a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
