// https://atcoder.jp/contests/abc332/tasks/abc332_f

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 998244353ull;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) const {
    return Mod((x + mod - b.x + mod) % mod);
  }
  Mod operator*(Mod b) const {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) const {
    return x == b.x;
  }
  bool operator!=(Mod b) const {
    return x != b.x;
  }
  bool operator<(Mod b) const {
    return x < b.x;
  }
  bool operator>(Mod b) const {
    return x > b.x;
  }
  bool operator<=(Mod b) const {
    return x <= b.x;
  }
  bool operator>=(Mod b) const {
    return x >= b.x;
  }

  Mod invert(Mod a) const {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) const {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) const {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    ull x;
    is >> x;
    m = Mod(x);
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

typedef Mod T; typedef pair<Mod, Mod> L; // T: data type, L: lazy type
const T tneut = Mod(0); const L lneut = {Mod(1), Mod(0)}; // neutrals
T oper(T a, T b){return a+b;}
T apply(T v, L l, int s, int e) {
  return v * l.first + l.second;
} // new st according to lazy
L prop(L a, L b) {
  auto [a1, a2] = a;
  auto [b1, b2] = b;
  return {a1 * b1, a2 * b1 + b2};
} // cumulative effect of lazy

struct STree { // example: range sum with range addition
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

vector<Mod> solve(const vector<Mod>& As, const vuuu& LRXs) {
  ull N = sz(As);
  STree st(N);
  st.init(As);

  for(auto& [L, R, X] : LRXs) {
    st.upd(L, R + 1, {Mod(R - L) / Mod(R + 1 - L), Mod(X)/Mod(R + 1 - L)});
  }

  vector<Mod> ans(N);
  fore(i, 0, N) {
    ans[i] = st.query(i, i + 1);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vector<Mod> As(N);
  fore(i, 0, N) {
    cin >> As[i];
  }
  vuuu LRXs(M);
  for(auto& [L, R, X] : LRXs) {
    cin >> L >> R >> X;
    L--, R--;
  }

  auto ans = solve(As, LRXs);
  for(Mod a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
