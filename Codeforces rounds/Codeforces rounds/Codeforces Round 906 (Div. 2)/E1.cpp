// https://codeforces.com/contest/1890/problem/E1

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

template <typename T> ostream &operator<<(ostream &out, const vector<T>& vs) {
  ull N = vs.size();
  fore(i, 0, N) {
    out << vs[i];
    if (i + 1 != N) {
      out << ' ';
    }
  }
  return out;
}

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

ull solve1(ull n, vuu lrs) {
  ull m = lrs.size();

  STree nrains(n);
  for(auto [l, r] : lrs) {
    nrains.upd(l, r, 1);
  }

  STree rained1(n), rained2(n);
  vuu rained_i;
  ull drys = 0;
  fore(i, 0, n) {
    ull q = nrains.query(i, i+1);
    if (q == 0) {
      drys++;
    } else if (q == 1) {
      rained1.upd(i, i+1, 1);
    } else if (q == 2) {
      rained2.upd(i, i+1, 1);
    }
  }

  ull ans = drys;

  { // Try two intervals independently
    ull first_i = 0, first_i_diff = 0;
    fore(i, 0, m) {
      auto [l, r] = lrs[i];

      ull with1 = rained1.query(l, r);
      ull this_i_diff = with1;
      if (this_i_diff > first_i_diff) {
        first_i = i;
        first_i_diff = this_i_diff;
      }
    }

    ull second_i_diff = 0;
    fore(i, 0, m) if (i != first_i) {
      auto [l, r] = lrs[i];

      ull with1 = rained1.query(l, r);
      ull this_i_diff = with1;
      if (this_i_diff > second_i_diff) {
        second_i_diff = this_i_diff;
      }
    }

    ull this_ans = drys + first_i_diff + second_i_diff;
    ans = max(ans, this_ans);
  }

  { // Intersecting intervals
    vuuu events;
    fore(j, 0, m) {
      auto [l, r] = lrs[j];
      events.push_back({l, 0, j});
      events.push_back({r, 1, j});
    }

    sort(events.begin(), events.end());

    set<ull> opens;
    for(auto [i, t, j] : events) {
      if (t == 0) {
        opens.insert(j);
      } else {
        opens.erase(j);
      }

      if (opens.size() == 2) {
        auto it = opens.begin();
        ull j0 = *it;
        it++;
        ull j1 = *it;

        auto [l0, r0] = lrs[j0];
        auto [l1, r1] = lrs[j1];

        // Intersect segments
        auto l = max(l0, l1);
        auto r = min(r0, r1);

        ull with1in0 = rained1.query(l0, r0);
        ull with1in1 = rained1.query(l1, r1);
        ull with2 = rained2.query(l, r);

        ull this_drys = drys + with1in0 + with1in1 + with2;
        ans = max(ans, this_drys);
      }
    }
  }

  return ans;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vuu lrs(m);
    fore(j, 0, m) {
      ull l, r;
      cin >> l >> r;
      l--;
      lrs[j] = {l, r};
    }

    auto ans = solve1(n, lrs);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
