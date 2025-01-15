// https://codeforces.com/contest/2043/problem/D

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

optional<uu> solve(ull l, ull r) {
  if (r <= l) {
    return {};
  }
  if (l == 1) {
    return {{l, r - 1}};
  }
  if (l + 1 == r) {
    return {};
  }

  uu ans = {-1, -1};

  fore(i, 0, 4) {
    ull A = l + i, B = r - 1;
    while (A <= B) {
      if (gcd(A, B) == 1) {
        if (ans.first == -1 || B - A > ans.second - ans.first) {
          ans = {A, B};
        }
        break;
      }
      B--;
    }
  }

  if (ans.first == -1) {
    return {};
  } else {
    return ans;
  }

  return {};
}

optional<uu> solve(ull l, ull r, ull G) {

  l = (l + G - 1) / G;
  r = (r - 1) / G + 1;

  auto ans = solve(l, r);
  if (ans.has_value()) {
    ans->first *= G;
    ans->second *= G;
  }

  return ans;
}

optional<uu> force(ull l, ull r, ull G) {
  ll ans_val = -1;
  uu ans = {0, 0};
  fore(A, l, r) fore(B, A, r) {
    if (gcd(A, B) == G) {
      ll val = B - A;
      if (val > ans_val || (val == ans_val && A < ans.first)) {
        ans_val = val;
        ans = {A, B};
      }
    }
  }

  if (ans_val == -1) {
    return {};
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull l, r, G;
    cin >> l >> r >> G;
    r++;

    auto ans = solve(l, r, G);

    if (ans.has_value()) {
      cout << ans->first << ' ' << ans->second << '\n';
    } else {
      cout << "-1 -1\n";
    }
  }
#else
  fore(l, 1, 100) fore(r, l + 1, 100) fore(G, 1, 100) {
  //fore(_, 0, 100000) {
  //  ull l = rand() % 200 + 1;
  //  ull r = rand() % 200 + l + 1;
  //  ull G = rand() % 205 + 1;

    auto ans = solve(l, r, G);
    auto ans2 = force(l, r, G);
    if (ans.has_value() != ans2.has_value()) {
      cout << "ERROR" << endl;
      cout << l << ' ' << r << ' ' << G << endl;
      cout << "ans: ";
      if (ans.has_value()) {
        cout << ans->first << ' ' << ans->second << '\n';
      } else {
        cout << "-1 -1\n";
      }
      cout << "ans2: ";
      if (ans2.has_value()) {
        cout << ans2->first << ' ' << ans2->second << '\n';
      } else {
        cout << "-1 -1\n";
      }
      return 1;
    }

 /*    if (ans.has_value()) {
      cout << ans->first << ' ' << ans->second << '\n';
    } else {
      cout << "-1 -1\n";
    } */
    cout << "OK " << l << ' ' << r << ' ' << G << endl;
    //cout << "OK " << _ << endl;
  }
#endif
}
