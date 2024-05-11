// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Problem {
  ull n;
  ull val;
  Problem *l, *r;

  Problem(ull n) : n(n) {
    if (n == 0) {
      l = NULL, r = NULL;
    } else {
      l = new Problem(n - 1);
      r = new Problem(n - 1);
    }
  }

  void update(ull p, ull b) {
    if (n == 0) {
      val = b;
    } else {
      if (p < (1ull << (n - 1))) {
        l->update(p, b);
      } else {
        ull new_p = p & ~(1ull << (n - 1));
        r->update(new_p, b);
      }
      if (n % 2 == 0) {
        val = l->val ^ r->val;
      } else {
        val = l->val | r->val;
      }
    }
  }
};

void solve(void) {}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  Problem t(n);
  fore(i, 0, 1ull << n) {
    ull a;
    cin >> a;
    t.update(i, a);
  }

  fore(i, 0, m) {
    int p, b;
    cin >> p >> b;
    t.update(p-1, b);
    cout << t.val << '\n';
  }

  return EXIT_SUCCESS;
}
