// https://codeforces.com/contest/381/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct T {
  ull ans;
  ull open_extra, close_extra;
};
const T neut = {false, 0, 0};
struct Tree {
  T f(T a, T b) {
    ull d = min(a.open_extra, b.close_extra);
    T ans;
    ans.ans = a.ans + b.ans + 2 * d;
    ans.open_extra = a.open_extra + b.open_extra - d;
    ans.close_extra = a.close_extra + b.close_extra - d;
    return ans;
  } // (any associative fn)
  vector<T> s; ull n;
  Tree(ull n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string S;
  cin >> S;

  ull n = S.size();
  Tree t(n);
  fore(i, 0, n) {
    T val = {0, 0, 0};
    if (S[i] == '(') val.open_extra = 1;
    else val.close_extra = 1;
    t.upd(i, val);
  }

  ull m;
  cin >> m;
  while (m--) {
    ull l, r;
    cin >> l >> r;
    l--;
    T ans = t.query(l, r);
    cout << ans.ans << '\n';
  }

  return EXIT_SUCCESS;
}
