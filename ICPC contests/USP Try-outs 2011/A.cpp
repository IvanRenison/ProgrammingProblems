// https://codeforces.com/gym/101081/problem/A
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef uint8_t u8;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, pluton = b; i < pluton; i++)

typedef array<uint, 52> T; typedef array<uint, 52> L; // T: data type, L: lazy type
constexpr static T tneut = {0};
L lneut() {
  L l;
  fore(i, 0, 52) {
    l[i] = i;
  }
  return l;
}
struct STree { // example: range sum with range addition
  T oper(T a, T b){
    T ans = {0};
    fore(i, 0, 52) {
      ans[i] = a[i] + b[i];
    }
    return ans;
  }
  T apply(T v, L l, int s, int e) { // Apply permutation
    T ans;
    fore(i, 0, 52) {
      ans[i] = v[l[i]];
    }
    return ans;
  } // new st according to lazy
  L prop(L a, L b) {
    L ans;
    fore(i, 0, 52) {
      ans[i] = a[b[i]];
    }
    return ans;
  } // cumulative effect of lazy

  vector<T> st;vector<L> lazy;int n;
  STree(int n): st(4*n,tneut), lazy(4*n,lneut()), n(n) {}
  void init(int k, int s, int e, const vector<T>& a){
    lazy[k]=lneut();
    if(s+1==e){st[k]=a[s];return;}
    int m=(s+e)/2;
    init(2*k,s,m,a);init(2*k+1,m,e,a);
    st[k]=oper(st[2*k],st[2*k+1]);
  }
  void push(int k, int s, int e){
    if(lazy[k] == lneut())return; // if neutral, nothing to do
    st[k]=apply(st[k], lazy[k], s, e);
    if(s+1<e){ // propagate to children
      lazy[2*k]=prop(lazy[2*k],lazy[k]);
      lazy[2*k+1]=prop(lazy[2*k+1],lazy[k]);
    }
    lazy[k]=lneut(); // clear node lazy
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


struct Problem {
  uint N;
  STree st;
  Problem(uint N) : N(N), st(N) {
    T t;
    fore(i, 0, 52) {
      t[i] = i % 13 + 1;
    }
    vector<T> v(N, t);
    st.init(v);
  }

  void shuffle(uint A, uint B, uint I, uint J) {
    L l = lneut();
    l[I] = J;
    l[J] = I;
    st.upd(A, B + 1, l);
  }

  uint sum(uint A, uint B) {
    T t = st.query(A, B + 1);
    return t[51];
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  uint T;
  cin >> T;
  while (T--) {
    uint N, Q;
    cin >> N >> Q;

    Problem p(N);
    while (Q--) {
      uint t;
      cin >> t;
      if (t == 0) {
        uint A, B, I, J;
        cin >> A >> B >> I >> J;
        p.shuffle(A, B, I, J);
      } else {
        uint A, B;
        cin >> A >> B;
        uint ans = p.sum(A, B);
        cout << ans << '\n';
      }
    }
  }

  return EXIT_SUCCESS;
}
