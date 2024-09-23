// https://www.facebook.com/codingcompetitions/hacker-cup/2023/round-1/problems/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef vector<double> vd;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 48;
const ull mod = 1e9 + 7;

struct STree { // example: range sum with range addition
	struct T {
    ull min, min_i, max, max_i;
  };
  typedef bool L; // T: data type, L: lazy type
	const T tneut = {inf, inf, 0, inf};
  const L lneut = 0; // neutrals
	T oper(T a, T b){
    T ans;
    if (a.min < b.min || (a.min == b.min && a.min_i < b.min_i)) {
      ans.min = a.min;
      ans.min_i = a.min_i;
    } else {
      ans.min = b.min;
      ans.min_i = b.min_i;
    }
    if (a.max > b.max || (a.max == b.max && a.max_i < b.max_i)) {
      ans.max = a.max;
      ans.max_i = a.max_i;
    } else {
      ans.max = b.max;
      ans.max_i = b.max_i;
    }
    return ans;
  }
	T apply(T v, L l, int s, int e) {
    if (l) {
      return {mod - v.max, v.max_i, mod - v.min, v.min_i};
    }
    else {
      return v;
    }
  } // new st according to lazy
	L prop(L a, L b) {return a ^ b;} // cumulative effect of lazy

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

ull solve1(vu As, vuu querys) {
  ull N = As.size();

  vector<STree::T> Ts(N);
  fore(i, 0, N) {
    Ts[i] = {As[i], i, As[i], i};
  }

  STree st(N);
  st.init(Ts);

  ull ans = 0;

  for (auto [L, R] : querys) {
    st.upd(L, R, true);
    STree::T t = st.query(0, N);
    ans += t.max_i + 1;
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
    vu As(N);
    fore(j, 0, N) cin >> As[j];
    ull Q;
    cin >> Q;
    vuu querys(Q);
    for (auto& [a, b] : querys) {
      cin >> a >> b;
      a--;
    }

    auto ans = solve1(As, querys);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
