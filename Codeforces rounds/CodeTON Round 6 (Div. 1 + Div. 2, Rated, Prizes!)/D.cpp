// https://codeforces.com/contest/1870/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct STree { // example: range sum with range addition
	typedef int T; typedef int L; // T: data type, L: lazy type
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

vector<ull> solve1(vector<ull> cs, ull k) {
  ull n = cs.size();

  vector<pair<ull,ull>> cs_i = {{cs[n-1], n-1}};
  for(ull i = n-2; i < n; i--) {
    ull c = cs[i];
    auto [cb, _] = cs_i.back();

    if (c < cb) {
      cs_i.push_back({c, i});
    }
  }

  reverse(cs_i.begin(), cs_i.end());

  STree st(n);
  vector<ull> cs_uses(n);

  for(auto it = cs_i.begin(); k > 0 && it != cs_i.end(); it++) {
    auto [c, i] = *it;
    if (c > k) {
      if (it == cs_i.begin()) {
        break;
      }
      auto [ca, j] = *(it-1);
      if (c - ca <= k) {
        ull diff = c - ca;
        ull d = min(cs_uses[j], k / diff);
        k -= d*diff;

        st.upd(j+1, i+1, d);
        cs_uses[i] += d;
        cs_uses[j] -= d;
      }
    } else if (c == k) {
      st.upd(0, i+1, 1);
      cs_uses[i] = 1;
      k = 0;
    } else {
      ull d = k / c;
      k = k%c;

      st.upd(0, i+1, d);
      cs_uses[i] = d;
    }


  }

  /* for(ull j = n-1; j < n && k > 0; j--) {
    auto [c, i] = cs_i[j];
    if (c > k) {
      continue;
    }

    ull d = k / c;
    k = k%c;

    st.upd(0, i+1, d);
  } */

  vector<ull> ans(n);
  fore(i, 0, n) {
    ans[i] = st.query(i, i+1);
  }

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
    vector<ull> cs(n);
    fore(i, 0, n) {
      cin >> cs[i];
    }
    ull k;
    cin >> k;

    auto ans = solve1(cs, k);
    fore(i, 0, ans.size()) {
      cout << ans[i] << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
