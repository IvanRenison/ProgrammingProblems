// https://codeforces.com/gym/104603/problem/G

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

ull minimumSpanningTreeCost(ull n, const vuuu& edges) {
  ull ans = 0;
  UF uf(n);
  for (auto [w, u, v] : edges) {
    // cerr << "edge: " << u << " " << v << " " << w << endl;
    if (uf.join(u, v)) ans += w;
  }
  return ans;
}

struct STree {
	typedef ii T;
  typedef optional<T> L; // T: data type, L: lazy type
	constexpr static T tneut = {0, 0}; constexpr static L lneut = {}; // neutrals
	T oper(T a, T b){return max(a, b);}
	T apply(T v, L l, int s, int e) {return l.has_value() ? *l : v;} // new st according to lazy
	L prop(L a, L b) {return b;} // cumulative effect of lazy

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

vuuu down_right_edges(const viii& HLRs) {
  ull N = HLRs.size();

  viii HLRs_aligned(N);
  vector<ll> x_cords;

  fore(i, 0, N) {
    auto [H, L, R] = HLRs[i];
    HLRs_aligned[i] = {H, L + H, R + H};
    x_cords.push_back(L + H);
    x_cords.push_back(R + H);
  }
  sort(x_cords.begin(), x_cords.end());

  map<ll, ull> x_cords_map;
  ull x_cords_id = 0;
  ll last_x_cord = -(1ll << 48);
  for (auto x : x_cords) {
    if (x != last_x_cord) {
      x_cords_map[x] = x_cords_id;
      x_cords_id++;
    }
  }

  STree stree(x_cords_id);

  vuuu edges;

  fore(i, 1, N + 1) {
    auto [H, L, R] = HLRs_aligned[i - 1];

    ull iL = x_cords_map[L], iR = x_cords_map[R];

    auto [H_l, l_id] = stree.query(iL, iL + 1);
    auto [H_r, r_id] = stree.query(iR, iR + 1);

    edges.push_back({H - H_l, l_id, i});
    edges.push_back({H - H_r, r_id, i});

    stree.upd(iL, iR + 1, {{(ull)H, i}});
  }

  return edges;
}

ull solve(viii& HLRs) {
  sort(HLRs.begin(), HLRs.end());
  ull N = HLRs.size();

  auto [H_max, _, __] = HLRs[N - 1];
  H_max++;

  vuuu edges = down_right_edges(HLRs);
  for (auto& [H, L, R] : HLRs) {
    swap(L, R);
    L = -L, R = -R;
  }

  auto edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    edges.push_back({w, u, v});
  }

  reverse(HLRs.begin(), HLRs.end());
  for(auto& [H, L, R] : HLRs) {
    H = H_max - H;
  }

  edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    if (u != 0) {
      edges.push_back({w, N + 1 - v, N + 1 - u});
    }
  }

  for (auto& [H, L, R] : HLRs) {
    swap(L, R);
    L = -L, R = -R;
  }

  edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    if (u != 0) {
      edges.push_back({w, N + 1 - v, N + 1 - u});
    }
  }

  sort(edges.begin(), edges.end());

  ull ans = minimumSpanningTreeCost(N + 1, edges);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);


  ull N;
  cin >> N;
  viii HLRs(N);
  for (auto& [H, L, R] : HLRs) {
    cin >> H >> L >> R;
  }

  auto ans = solve(HLRs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
