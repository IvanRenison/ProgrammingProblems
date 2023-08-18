// https://codeforces.com/gym/100801
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

struct Statement;

struct ForRange {
  char var;
  char limit;
  vector<Statement> loop;

  bool limitIsDigit() {
    return '0' <= limit && limit <= '9';
  }
};

struct Statement {
  bool lag;
  optional<ForRange> forRange;
};

Statement Lag() {
  Statement ans;
  ans.lag = true;
  return ans;
}

typedef vector<Statement> Program;

vector<pair<ull, ull>>
parts(vector<string>& ss, ull from, ull to, ull base_indent) {
  if (to < from || ss.empty()) {
    return {};
  }
  vector<pair<ull, ull>> ans = {{from, from + 1}};
  fore(i, from + 1, to) {
    string s = ss[i];
    if (s[4 * base_indent] == ' ') {
      ans.back().second++;
    } else {
      ans.push_back({ans.back().second, ans.back().second + 1});
    }
  }
  return ans;
}

Program read(vector<string>& ss, ull from, ull to, ull base_indent) {

  Program ans;

  vector<pair<ull, ull>> ps = parts(ss, from, to, base_indent);

  for (auto [i, j] : ps) {
    if (i + 1 == j) {
      ans.push_back(Lag());
    } else {
      char var = ss[i][4 * base_indent + 4];
      char limit = ss[i][4 * base_indent + 15];
      Program loop = read(ss, i + 1, j, base_indent + 1);
      ForRange forRange = {var, limit, loop};
      ans.push_back({false, forRange});
    }
  }

  return ans;
}

struct Ratio {
  ll num;
  ull den;
  Ratio(ll num = 0, ull den = 1) {
    ull g = gcd((ull)abs(num), den);
    this->num = num / ((ll)g);
    this->den = den / g;
  }

  Ratio operator+(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den + o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator-(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den - o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator*(Ratio o) const {
    return Ratio(num * o.num, den * o.den);
  }

  void operator+=(Ratio o) {
    *this = *this + o;
  }
  void operator-=(Ratio o) {
    *this = *this - o;
  }
  void operator*=(Ratio o) {
    *this = *this * o;
  }

  bool operator==(Ratio o) const {
    return num == o.num && den == o.den;
  }
  bool operator!=(Ratio o) const {
    return !(*this == o);
  }

  friend ostream& operator<<(ostream& os, Ratio r) {
    os << r.num;
    if (r.den != 1) {
      os << "/" << r.den;
    }
    return os;
  }
};

struct Var {
  char c;
  Var(char c) : c(c) {}

  bool operator==(Var o) const& {
    return c == o.c;
  }
  bool operator!=(Var o) const& {
    return c != o.c;
  }
  bool operator<(Var o) const& {
    return c < o.c;
  }

  friend ostream& operator<<(ostream& os, Var v) {
    os << v.c;
    return os;
  }
};
typedef pair<map<Var, ull>, Ratio> Term;
// Multivariate polynomial
struct Pol {
  map<map<Var, ull>, Ratio> m;
  Pol() {}
  Pol(Ratio x) {
    m[{}] = x;
  }
  Pol(Var c) {
    m[{{c, 1}}] = Ratio(1);
  }
  Pol(Term t) {
    m[t.first] = t.second;
    {
      for (auto it : m) {
        ;
      }
    }
  }
};

Pol operator+(Var n, Var k) {
  Pol res;
  res.m[{{n, 1}}] = Ratio(1);
  res.m[{{k, 1}}] = Ratio(1);
  return res;
}
Pol operator+(Var n, Ratio x) {
  Pol res;
  res.m[{}] = x;
  res.m[{{n, 1}}] = Ratio(1);
  return res;
}
Pol operator+(Var n, ll x) {
  Pol res;
  res.m[{}] = Ratio(x);
  res.m[{{n, 1}}] = Ratio(1);
  return res;
}

Term operator*(Var n, Var k) {
  if (n == k) {
    return {{{n, 2}}, Ratio(1)};
  } else {
    return {{{n, 1}, {k, 1}}, Ratio(1)};
  }
}
Term operator*(Var n, Ratio x) {
  return {{{n, 1}}, x};
}
Term operator*(Var n, ll x) {
  return {{{n, 1}}, Ratio(x)};
}

Term operator*(Term t, Var k) {
  Term res = t;
  res.first[k] += 1;
  return res;
}
Term operator*(Term t, Ratio x) {
  Term res = t;
  res.second *= x;
  return res;
}

ostream& operator<<(ostream& os, Term t) {
  os << t.second;
  for (auto& p : t.first) {
    os << " * " << p.first;
    if (p.second != 1) {
      os << "^" << p.second;
    }
  }
  return os;
}

Pol operator+(const Pol& pol, const Pol& o) {
  Pol res;
  for (auto& p : pol.m) {
    res.m[p.first] += p.second;
  }
  for (auto& p : o.m) {
    res.m[p.first] += p.second;
  }
  return res;
}
Pol operator+(const Pol& pol, int x) {
  Pol res;
  if (x != 0) {
    res.m[{}] = Ratio(x);
  }
  for (auto& p : pol.m) {
    res.m[p.first] += p.second;
  }
  return res;
}

Pol operator*(const Pol& pol, Ratio x) {
  Pol res;
  for (auto& p : pol.m) {
    res.m[p.first] += p.second * x;
  }
  return res;
}
Pol operator*(const Pol& pol, Var c) {
  Pol res;
  for (Term t : pol.m) {
    Term sub_t = t * c;
    Pol sub_res = Pol(sub_t);
    res = res + sub_res;
  }
  return res;
}
Pol operator*(const Pol& pol, Term t) {
  Pol res;
  for (auto& p : pol.m) {
    map<Var, ull> q = p.first;
    for (auto& pp : t.first) {
      q[pp.first] += pp.second;
    }
    res.m[q] += p.second * t.second;
  }
  return res;
}
Pol operator*(const Pol& pol, const Pol& o) {
  Pol res;
  for (auto& p : o.m) {
    res = res + pol * p;
  }
  return res;
}

ostream& operator<<(ostream& os, const Pol& p) {
  if (p.m.empty()) {
    os << 0;
    return os;
  }
  bool first = true;
  for (auto& pp : p.m) {
    if (pp.second == 0) {
      continue;
    }
    if (!first && pp.second.num > 0) {
      os << " + ";
    } else if (!first) {
      cout << " ";
    }
    first = false;
    bool x_first = true;
    if (pp.second != Ratio(1) || pp.first.empty()) {
      os << pp.second;
      x_first = false;
    }
    for (auto [x, i] : pp.first) {
      fore(j, 0, i) {
        if (!x_first) {
          os << " * ";
        }
        x_first = false;
        os << x;
      }
    }
  }
  return os;
}

Pol operator+(const Term x, const Term y) {
  return Pol(x) + y;
}
Pol operator+(const Term x, Var y) {
  return Pol(x) + y;
}

Pol sumOverUntil(Term t, Var c, Var k) {
  const auto& [vars, val] = t;

  if (vars.count(c) == 0) {
    Pol ans = Pol(t) * k;
    return ans;
  } else {
    Pol _k = k + (-1ll);
    // Sum over c
    ull i = vars.at(c);
    assert(1 <= i && i <= 5);
    Pol ans;
    if (i == 1) { // _k(_k+1)/2
      ans = (_k + 1) * _k * Ratio(1, 2);
    } else if (i == 2) { // _k(_k+1)(2_k+1)/6
      ans = (_k + 1) * (_k * _k * Ratio(2) + _k) * Ratio(1, 6);
    } else if (i == 3) { // _k²(_k + 1)² / 4
      ans = (_k + 1) * _k * (_k + 1) * _k * Ratio(1, 4);
    } else if (i == 4) { // _k(_k+1)(2_k+1)(3_k²+3_k-1)/30
      ans = (_k + 1) * (_k * _k * Ratio(2) + _k) *
            (_k * _k * Ratio(3) + _k * Ratio(3) + Ratio(-1)) * Ratio(1, 30);
    } else { // i == 5 // _k²(_k+1)²(2_k²+2_k-1)/12
      ans = (_k + 1) * (_k + 1) * _k * _k *
            (_k * _k * Ratio(2) + _k * Ratio(2) + Ratio(-1)) * Ratio(1, 12);
    }

    // Other variables
    map<Var, ull> new_vars;
    for (auto& p : vars) {
      if (p.first != c) {
        new_vars[p.first] = p.second;
      }
    }
    Term new_t = {new_vars, val};

    return ans * new_t;
  }
}

Pol sumOverUntil(const Pol& t, Var c, Var k) {
  Pol res;
  for (auto& p : t.m) {
    res = res + sumOverUntil(p, c, k);
  }
  return res;
}

Pol solve(Program& p);

Pol StatementSolve(Statement s) {
  if (s.lag) {
    return Pol(Ratio(1));
  } else if (s.forRange->limitIsDigit()) {
    Pol ans = solve(s.forRange->loop);
    ans = sumOverUntil(ans, s.forRange->var, s.forRange->limit);
    return ans;
  } else {
    Var k = s.forRange->limit;
    Var c = s.forRange->var;
    Pol ans = solve(s.forRange->loop);
    ans = sumOverUntil(ans, c, k);
    return ans;
  }
}

Pol solve(Program& p) {
  Pol ans;
  for (auto& s : p) {
    Pol sub_ans = StatementSolve(s);
    ans = ans + sub_ans;
  }
  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("fygon.in", "r", stdin);
  freopen("fygon.out", "w", stdout);
#endif

  vector<string> ss;
  // Read each line until end of file
  string s;
  while (getline(cin, s)) {
    ss.push_back(s);
  }

  Program p = read(ss, 0, ss.size(), 0);

  Pol ans = solve(p);

  cout << ans << "\n";

  return 0;
}
