// https://codeforces.com/contest/2048/problem/I1

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


struct presums {
  typedef ull T;
  T op(T a, T b) { return a + b; }
  T rev(T a, T b) { return a - b; }
  constexpr static T neut = 0;
  // rev(op(a, b), b) = a

  ull n;
  vector<T> as;

  presums(ull n) : n(n), as(n + 1) {}

  void update(ull i, ull j, T v) { // [i, j)
    as[i] = op(as[i], v);
    as[j] = rev(as[j], v);
  }
  void pointUpdate(ull i, T v) {
    update(i, i + 1, v);
  }

  vector<T> build() {
    vector<T> ans(n);
    ans[0] = as[0];
    fore(i, 1, n) {
      ans[i] = op(ans[i - 1], as[i]);
    }
    return ans;
  }
};

optional<tuple<presums, ull, ull>> solve(string& s, ull i, ull j) {
  ull n = s.size();

  assert(i < j);

  if (i + 1 == j) { // length 1
    presums ans(n);
    return {{move(ans), 0, 1}};
  } else if (i + 2 == j) { // length 2
    presums ans(n);
    ull ans_mx = 0;
    ull ans_cnt = 0;

    if (s[i] == 'L' && s[j - 1] == 'L') {
      ans.pointUpdate(i + 1, 1);
      ans_mx = 1;
      ans_cnt = 2;
    } else if (s[i] == 'L' && s[j - 1] == 'R') {
      ans_cnt = 1;
    } else if (s[i] == 'R' && s[j - 1] == 'L') {
      ans.update(i, j, 1);
      ans_mx = 1;
      ans_cnt = 1;
    } else { // s[i] == 'R' && s[j - 1] == 'R'
      ans.pointUpdate(i, 1);
      ans_mx = 1;
      ans_cnt = 2;
    }
    return {{move(ans), ans_mx, ans_cnt}};
  } else {
    if (s[i] == 'L' && s[j - 1] == 'L') {
      optional<tuple<presums, ull, ull>> ans_ = solve(s, i + 1, j - 1);
      if (!ans_.has_value()) {
        return {};
      }
      auto& [ans, ans_mx, ans_cnt] = *ans_;
      assert(ans_mx <= ans_cnt);
      if (ans_mx == ans_cnt) {
        return {};
      }
      ans.update(i + 1, j - 1, 1);
      ans_mx++;
      ans_cnt++;
      ans.pointUpdate(j - 1, ans_cnt);
      ans_mx = max(ans_mx, ans_cnt);
      ans_cnt++;
      return {{move(ans), ans_mx, ans_cnt}};
    } else if (s[i] == 'L' && s[j - 1] == 'R') {
      optional<tuple<presums, ull, ull>> ans_ = solve(s, i + 1, j - 1);
      if (!ans_.has_value()) {
        return {};
      }
      auto& [ans, ans_mx, ans_cnt] = *ans_;
      assert(ans_mx <= ans_cnt);
      ans.update(i + 1, j - 1, 1);
      ans_mx++;
      ans_cnt++;
      return {{move(ans), ans_mx, ans_cnt}};
    } else if (s[i] == 'R' && s[j - 1] == 'L') {
      presums ans(n);
      ans.update(i, j, 1);
      ull ans_mx = 1;
      ull ans_cnt = 1;
      return {{move(ans), ans_mx, ans_cnt}};
    } else { // s[i] == 'R' && s[j - 1] == 'R'
      optional<tuple<presums, ull, ull>> ans_ = solve(s, i + 1, j - 1);
      if (!ans_.has_value()) {
        return {};
      }
      auto& [ans, ans_mx, ans_cnt] = *ans_;
      assert(ans_mx <= ans_cnt);
      if (ans_mx == ans_cnt) {
        return {};
      }
      ans.update(i + 1, j - 1, 1);
      ans_mx++;
      ans_cnt++;
      ans.pointUpdate(i, ans_cnt);
      ans_mx = max(ans_mx, ans_cnt);
      ans_cnt++;
      return {{move(ans), ans_mx, ans_cnt}};
    }

  }
}

optional<vu> solve(string& s) {
  ull n = s.size();

  optional<tuple<presums, ull, ull>> ans_ = solve(s, 0, n);

  if (!ans_.has_value()) {
    return {};
  }

  auto& [ans, ans_mx, ans_cnt] = *ans_;

  vu vans = ans.build();

  return vans;
}

bool check(string& s, vu ans) {
  ull n = s.size();

  fore(i, 0, n) {
    set<ull> cur;
    if (s[i] == 'L') {
      fore(j, 0, i) {
        cur.insert(ans[j]);
      }
    } else {
      fore(j, i + 1, n) {
        cur.insert(ans[j]);
      }
    }
    if (cur.size() != ans[i]) {
      return false;
    }
  }

  return true;
}

optional<vu> force(string s) {
  ull n = s.size();

  ull pow = 1;
  fore(_, 0, n) {
    pow *= n + 1;
  }

  fore(x, 0, pow) {
    vu ans(n);
    ull cur = x;
    fore(i, 0, n) {
      ans[i] = cur % (n + 1);
      cur /= n + 1;
    }

    if (check(s, ans)) {
      return ans;
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    string s;
    cin >> s;

    optional<vu> ans = solve(s);
    if (ans.has_value()) {
      for (ull& x : *ans) {
        cout << x << ' ';
      }
    } else {
      cout << -1;
    }
    cout << '\n';
  }
#else

  fore(n, 1, 8) fore(x, 0, 1 << n) {
    string s;
    fore(i, 0, n) {
      s.push_back((x & (1 << i)) ? 'L' : 'R');
    }

    auto ans = solve(s);
    auto ansf = force(s);
    if (ans.has_value() != ansf.has_value() || (ans.has_value() && !check(s, *ans))) {
      cout << "FAIL" << endl;
      cout << s.size() << endl;
      cout << s << endl;
      if (ans.has_value()) {
        for (ull& x : *ans) {
          cout << x << ' ';
        }
        cout << endl;
      } else {
        cout << -1 << endl;
      }
      if (ansf.has_value()) {
        for (ull& x : *ansf) {
          cout << x << ' ';
        }
        cout << endl;
      } else {
        cout << -1 << endl;
      }
      return 1;
    }
  }
#endif
}
