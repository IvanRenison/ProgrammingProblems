// https://codeforces.com/contest/1919/problem/F1

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

const ull inf = 1ull << 60;

struct STree { // example: range sum with range addition
  typedef ll T; typedef ll L; // T: data type, L: lazy type
  constexpr static T tneut = -inf; constexpr static L lneut = 0; // neutrals
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

vu solve(vu& as, vu& bs, const vuuu& querys) {
  ull n = as.size(), q = querys.size();

  ull a_sum = 0;
  for (ull a : as) {
    a_sum += a;
  }

  vi diffs(n);
  fore(i, 0, n) {
    diffs[i] = (ll)as[i] - (ll)bs[i];
  }

  vi sub_sums(n + 1);
  for (ull i = n - 1; i < n; i--) {
    sub_sums[i] = sub_sums[i + 1] + diffs[i];
  }

  STree st(n + 1);
  st.init(sub_sums);

  vu ans(q);
  fore(i, 0, q) {
    auto [p, x, y] = querys[i];
    a_sum += x - as[p];

    ll d = (ll)x - (ll)y;

    ll delta = d - diffs[p];

    st.upd(0, p + 1, delta);
    as[p] = x;
    bs[p] = y;
    diffs[p] = d;

    ull qu = st.query(0, n + 1);
    ans[i] = a_sum - qu;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vu as(n), bs(n), cs(n - 1);
  fore(i, 0, n) {
    cin >> as[i];
  }
  fore(i, 0, n) {
    cin >> bs[i];
  }
  fore(i, 0, n - 1) {
    cin >> cs[i];
  }
  vuuu querys(q);
  fore(i, 0, q) {
    ull p, x, y, z;
    cin >> p >> x >> y >> z;
    p--;
    querys[i] = {p, x, y};
  }

  auto ans = solve(as, bs, querys);
  for (ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
