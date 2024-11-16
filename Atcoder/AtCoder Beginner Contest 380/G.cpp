// https://atcoder.jp/contests/abc380/tasks/abc380_g

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

// Based on ModularArithmetic of kactl
constexpr ull mod = 998244353; // Prime number for division to work
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
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
    Mod r = a ^ (mod - 2);
    return r;
  }
  Mod operator^(ull e) const {
    Mod r = Mod(1);
    Mod b = *this;
    while (e > 0) {
      if (e & 1) {
        r *= b;
      }
      b *= b;
      e /= 2;
    }
    return r;
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
    is >> m.x;
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

//#define Mod ld

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

// C++ program to Count Inversions in an array using merge sort

#include <iostream>
#include <vector>
using namespace std;

// This function merges two sorted subarrays arr[l..m] and arr[m+1..r]
// and also counts inversions in the whole subarray arr[l..r]
ull countAndMerge(vector<ull>& arr, ull l, ull m, ull r) {

    // Counts in two subarrays
    ull n1 = m - l + 1, n2 = r - m;

    // Set up two vectors for left and right halves
    vector<ull> left(n1), right(n2);
    for (ull i = 0; i < n1; i++)
        left[i] = arr[i + l];
    for (ull j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    // Initialize inversion count (or result) and merge two halves
    ull res = 0;
    ull i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {

        // No increment in inversion count if left[] has a
        // smaller or equal element
        if (left[i] <= right[j])
            arr[k++] = left[i++];

        // If right is smaller, then it is smaller than n1-i
          // elements because left[] is sorted
        else {
            arr[k++] = right[j++];
            res += (n1 - i);
        }
    }

    // Merge remaining elements
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];

    return res;
}

// Function to count inversions in the array
ull countInv(vector<ull>& arr, ull l, ull r){
    ull res = 0;
    if (l < r) {
        ull m = (r + l) / 2;

        // Recursively count inversions in the left and
        // right halves
        res += countInv(arr, l, m);
        res += countInv(arr, m + 1, r);

        // Count inversions such that greater element is in
          // the left half and smaller in the right half
        res += countAndMerge(arr, l, m, r);
    }
    return res;
}

ull inversionCount(vector<ull> arr) {
      ull n = arr.size();
      return countInv(arr, 0, n-1);
}

/** Author: Iván Renison
 * Date: 2024-03-05
 * License: CC0
 * Source: notebook el vasito
 * Description: Segment tree with ability to add values of large intervals, and compute the sum of intervals.
 * Ranges are [s, e).
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Tree st(n);
 *  st.init(x);
 *  st.upd(s, e, v);
 *  st.query(s, e);
 * Status: Tested on SPOJ HORRIBLE, stress-tested a bit
 */
typedef ll T; typedef ll L; // T: data type, L: lazy type
const T tneut = 0; const L lneut = 0; // neutrals
T f(T a, T b) { return a + b; } // associative
T apply(T v, L l, ll s, ll e) { // new st according to lazy
  return v + l * (e - s); }
L comb(L a, L b) { return a + b; } // cumulative effect of lazy

struct Tree { // example: range sum with range addition
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(vector<T> &a) : n(SZ(a)), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ll k, ll s, ll e, vector<T> &a) {
    lazy[k] = lneut;
    if (s + 1 == e) { st[k] = a[s]; return; }
    ll m = (s + e) / 2;
    init(2*k, s, m, a), init(2*k+1, m, e, a);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return; // if neutral, nothing to do
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) { // propagate to children
      lazy[2*k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut; // clear node lazy
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v); // accumulate lazy
      push(k, s, e);
      return;
    }
    ll m = (s + e) / 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) / 2;
    return f(query(2*k, s, m, a, b),query(2*k+1, m, e, a, b));
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  T query(ll a, ll b) { return query(1, 0, n, a, b); }
};


Mod solve(vu& Ps, ull K) {
  ull N = Ps.size();

  Mod extra_invs = inversionCount(Ps);
  Mod shuffle_invs = Mod(K * (K - 1)) / Mod(4);

  Tree block_less_count(N), block_more_count(N);

  fore(i, 0, K) {
    ull P = Ps[i];
    extra_invs -= block_more_count.query(P, P + 1);
    block_less_count.upd(P + 1, N, 1);
    block_more_count.upd(0, P, 1);
  }

  Mod ans = extra_invs + shuffle_invs;
  fore(i, 0, N - K) {
    ull j = i + K;
    ull Pi = Ps[i];
    ull Pj = Ps[j];

    block_less_count.upd(Pi + 1, N, -1);
    block_more_count.upd(0, Pi, -1);

    extra_invs += block_less_count.query(Pi, Pi + 1);


    block_less_count.upd(Pj + 1, N, 1);
    block_more_count.upd(0, Pj, 1);

    extra_invs -= block_more_count.query(Pj, Pj + 1);

    ans += extra_invs + shuffle_invs;
  }

  ans /= Mod(N - K + 1);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, K;
  cin >> N >> K;
  vu Ps(N);
  fore(i, 0, N) {
    cin >> Ps[i];
    Ps[i]--;
  }
  auto ans = solve(Ps, K);
  cout << ans << '\n';

}
