// https://codeforces.com/group/5GNF7zti59/contest/536252
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef long double ld;

const ld eps = 1e-10;

enum FType {
  Atomic,
  Not, And, Or, Xor
};

struct Formula {
  FType ty;
  Formula* f0 = NULL, * f1 = NULL;
  ll a, b, c;

  Formula(ll a, ll b, ll c) : ty(Atomic), a(a), b(b), c(c) {}
  Formula(Formula* f) : ty(Not), f0(f) {}
  Formula(FType ty, Formula* f0, Formula* f1) : ty(ty), f0(f0), f1(f1) {}
};

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

ll parseNum(const string& s, ll& i) {
  ll n = s.size();

  bool neg = s[i] == '-';
  if (neg) {
    i++;
  }

  ll ans = 0;
  while (i < n && isDigit(s[i])) {
    ans = ans * 10 + (s[i] - '0');
    i++;
  }

  if (neg) {
    ans = -ans;
  }

  return ans;
}

Formula* parse(const string& s, ll& i) {

  if (s[i] == '[') {
    i++;
    ll a, b, c;
    a = parseNum(s, i);
    assert(s[i] == ',');
    i++;
    b = parseNum(s, i);
    assert(s[i] == ',');
    i++;
    c = parseNum(s, i);
    assert(s[i] == ']');
    i++;
    return new Formula(a, b, c);
  } else {
    assert(s[i] == '(');
    i++;
    if (s[i] == '!') {
      i++;
      Formula* f = parse(s, i);
      assert(s[i] == ')');
      i++;
      return new Formula(f);
    } else {
      Formula* f0 = parse(s, i);
      assert(s[i] == '&' || s[i] == '|' || s[i] == '^');
      FType ty = s[i] == '&' ? And : (s[i] == '|' ? Or : Xor);
      i++;
      Formula* f1 = parse(s, i);
      assert(s[i] == ')');
      i++;
      return new Formula(ty, f0, f1);
    }
  }
}


typedef ld T;
ll sgn(T x) {
  if (abs(x) < eps) return 0;
  return (x > 0) - (x < 0);
}

struct P {
  T x, y;
  P(T x = 0, T y = 0) : x(x), y(y) {}

  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }

  T cross(P p) const { return x*p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }

  P perp() const { return P(-y, x); }
};

pair<ll, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (abs(d) < eps)
    return {-(abs(s1.cross(e1,s2)) < eps), P(0,0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  fore(i, 0, SZ(poly)) {
    P cur = poly[i], prev = i ? poly[i-1] : poly.back();
    bool side = s.cross(e, cur)  + eps < 0;
    if (side != (s.cross(e, prev) + eps < 0))
      res.push_back(lineInter(s, e, cur, prev).second);
    if (side)
      res.push_back(cur);
  }
  return res;
}

T polygonArea2(vector<P>& v) {
  T a = v.back().cross(v[0]);
  fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
  return a;
}

P polygonCenter(const vector<P>& v) {
  P res(0, 0); ld A = 0;
  for (ll i = 0, j = SZ(v) - 1; i < SZ(v); j = i++) {
    res = res + (v[i] + v[j]) * v[j].cross(v[i]);
    A += v[j].cross(v[i]);
  }
  return res / A / 3;
}

void atomics(Formula* f, viii& ans) {
  if (f->ty == Atomic) {
    ans.push_back({f->a, f->b, f->c});
  } else {
    atomics(f->f0, ans);
    if (f->ty != Not) {
      atomics(f->f1, ans);
    }
  }
}

bool sat(Formula* f, P p) {
  if (f->ty == Atomic) {
    return f->a * p.x + f->b * p.y + f->c >= 0;
  } else if (f->ty == Not) {
    return !sat(f->f0, p);
  } else if (f->ty == And) {
    return sat(f->f0, p) && sat(f->f1, p);
  } else if (f->ty == Or) {
    return sat(f->f0, p) || sat(f->f1, p);
  } else {
    return sat(f->f0, p) != sat(f->f1, p);
  }
}


ld solve(ld x, ld X, ld y, ld Y, Formula* f) {
  viii atoms;
  atomics(f, atoms);

  vector<vector<P>> polys = {{P(x, y), P(X, y), P(X, Y), P(x, Y)}};
  for (auto [a, b, c] : atoms) {
    // ax + by + c = 0
    // y = (-ax - c) / b
    P s, t;
    if (abs(b) < eps) {
      s = P((ld)(-c) / (ld)(a), 0), t = P((ld)(-c) / (ld)(a), 1);
    } else {
     s = P(0, (ld)(-c) / (ld)b), t = P(1, ((ld)(-a - c)) / (ld)b);
    }

    vector<vector<P>> polys_new;
    for (auto& poly : polys) {
      vector<P> poly_new = polygonCut(poly, s, t);
      if (poly_new.size() >= 3) {
        polys_new.push_back(move(poly_new));
      }
      poly_new = polygonCut(poly, t, s);
      if (poly_new.size() >= 3) {
        polys_new.push_back(move(poly_new));
      }
    }
    polys = move(polys_new);
  }

  ld ans = 0;
  for (auto& poly : polys) {
    P center = polygonCenter(poly);
    if (sat(f, center)) {
      ans += polygonArea2(poly) / 2;
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll x, X, y, Y;
  cin >> x >> X >> y >> Y;
  string s;
  cin >> s;

  ll i = 0;
  Formula* f = parse(s, i);
  assert(i == s.size());
  ld ans = solve(x, X, y, Y, f);
  cout << fixed << setprecision(8);
  cout << ans << '\n';

}
