// https://codeforces.com/contest/1904/problem/D2

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
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

struct Tree {
  typedef ull T;
  static constexpr T unit = inf;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

struct STree {
  typedef ull T; typedef ull L; // T: data type, L: lazy type
  constexpr static T tneut = 0; constexpr static L lneut = inf; // neutrals
  T oper(T a, T b){return max(a, b);}
  T apply(T v, L l, int s, int e) {return l == inf ? v : l;} // new st according to lazy
  L prop(L a, L b) {return b == inf ? a : b;} // cumulative effect of lazy

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

bool solve1(vu& as, const vu& bs) {
  ull n = as.size();

  vuu bs_i(n);
  fore(i, 0, n) {
    bs_i[i] = {bs[i], i};
  }
  sort(all(bs_i));

  Tree tbs(n);
  fore(i, 0, n) {
    tbs.update(i, bs[i]);
  }

  STree tas(n);
  tas.init(as);

  for (auto [b, i] : bs_i) {
    if (as[i] > b) {
      return false;
    }
    if (as[i] == b) {
      continue;
    }

    if (i + 1 < n) {
      ull l = i + 1, r = n;
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (tas.query(i + 1, m) >= b) {
          r = m;
        } else {
          l = m;
        }
      }
      if (tas.query(l, l + 1) == b && tbs.query(i, l) >= b) {
        tas.upd(i, l, b);
        goto next;
      }
    }
    if (i > 0) {
      ull l = 0, r = i;
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (tas.query(m, i) >= b) {
          l = m;
        } else {
          r = m;
        }
      }
      if (tas.query(l, l + 1) == b && tbs.query(l, i) >= b) {
        tas.upd(l, i + 1, b);
        goto next;
      }
    }
    return false;
    next:;
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n), bs(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    fore(j, 0, n) {
      cin >> bs[j];
    }

    if (solve1(as, bs)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
