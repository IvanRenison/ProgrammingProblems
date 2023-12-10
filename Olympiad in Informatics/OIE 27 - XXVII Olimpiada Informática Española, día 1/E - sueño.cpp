// https://codeforces.com/gym/104604
// Resultado parcial

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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull maxn = 1000;

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 202220233ull;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x + mod - b.x + mod) % mod);
  }
  Mod operator*(Mod b) {
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
  bool operator==(Mod b) {
    return x == b.x;
  }
  bool operator!=(Mod b) {
    return x != b.x;
  }
  bool operator<(Mod b) {
    return x < b.x;
  }
  bool operator>(Mod b) {
    return x > b.x;
  }
  bool operator<=(Mod b) {
    return x <= b.x;
  }
  bool operator>=(Mod b) {
    return x >= b.x;
  }

  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) {
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


Mod facts[maxn + 2];

Mod comb(ull a, ull b) {
  return facts[a] / (facts[b] * facts[a - b]);
}

void init() {
  // facts
  facts[0] = Mod(1);
  fore(i, 1, maxn + 2) {
    facts[i] = facts[i - 1] * Mod(i);
  }
}


vector<Mod> interpolate(vector<Mod> x, vector<Mod> y, int n) {
  vector<Mod> res(n), temp(n);
  fore(k,0,n-1) fore(i,k+1,n)
    y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  Mod last = 0; temp[0] = 1;
  fore(k,0,n) fore(i,0,n) {
    res[i] += y[k] * temp[i];
    swap(last, temp[i]);
    temp[i] -= last * x[k];
  }
  return res;
}

Mod interpolate(vector<Mod> x, vector<Mod> y, int n, Mod v) {
  Mod ans = 0;
  fore(i, 0, n) {
    Mod this_ans = 1;
    fore(j, 0, n) if (i != j) {
      this_ans *= (v - x[j]) / (x[i] - x[j]);
    }
    this_ans *= y[i];
    ans += this_ans;
  }
  return ans;
}


// Calc sum{i = 1 to n} i^e
Mod sumToPow(ull n, ull e) {
  if (e == 0) {
    return n;
  }

  vector<Mod> xs(e + 2), ys(e + 2);
  fore(i, 0, e + 2) {
    xs[i] = i + 1;
  }

  ys[0] = 1;

  fore(i, 1, e + 2) {
    ys[i] = ys[i-1] + (Mod(i + 1) ^ e);
  }

  if (n <= e + 1) {
    return ys[n - 1];
  }

  Mod ans = interpolate(xs, ys, e + 2, Mod(n));

  return ans;
}


Mod sumToPow_force(ull n, ull e) {
  Mod ans = 0;
  fore(i, 1, n + 1) {
    ans += Mod(i) ^ e;
  }
  return ans;
}



vector<Mod> solve1(ull n, ull x) {

  vector<Mod> ans(n);

  fore(i, 1, n + 1) {
    Mod this_ans = 0;

    if (i == n) {
      this_ans += 1;
    }

    /* fore(y, 2, x + 1) {
      this_ans += Mod(y - 1) ^ (n - i);
    } */
    this_ans += sumToPow(x - 1, n - i);

    this_ans *= comb(n, i);

    ans[i - 1] = this_ans;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  init();

  ull T;
  cin >> T;

  fore(i, 0, T) {
    ull n, x;
    cin >> n >> x;

    auto ans = solve1(n, x);
    for (Mod a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

/*   ull T = 100;
  while (T--) {
    ull n = rand() % 500000 + 1;
    ull e = rand() % 1001;

    auto ans1 = sumToPow(n, e);
    auto ans2 = sumToPow_force(n, e);
    if (ans1 != ans2) {
      cout << "ERROR: " << n << ' ' << e << '\n';
      cout << ans1 << ' ' << ans2 << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
