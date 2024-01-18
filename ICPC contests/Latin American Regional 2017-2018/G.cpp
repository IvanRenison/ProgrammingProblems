// https://codeforces.com/gym/101889

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ull, ull, ll> uui;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<uui> vuui;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = (1e9 + 7);
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
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


struct Node {
  Mod counts[4];
  // 0bij = are i and should be j

  Mod& operator[](ull i) {
    return counts[i];
  }
  Mod are0() {
    return counts[0b00] + counts[0b01];
  }
  Mod are1() {
    return counts[0b10] + counts[0b11];
  }
  Mod should0() {
    return counts[0b00] + counts[0b10];
  }
  Mod should1() {
    return counts[0b01] + counts[0b11];
  }
  Mod total() {
    return are0() + are1();
  }
};

Node f(const vuui& gates, ull i) {
  if (i == 0) {
    Node ans;
    ans.counts[0b00] = ans.counts[0b11] = 1;
    return ans;
  }

  auto [X, Y, F] = gates[i - 1];

  Node X_node = f(gates, X), Y_node = f(gates, Y);

  Node ans;

  if (F == -1) {
    ans[0b00] = X_node[0b11] * Y_node[0b11];
    ans[0b10] = X_node[0b01] * Y_node[0b01] + X_node[0b01] * Y_node[0b11] + X_node[0b11] * Y_node[0b01];
    ans[0b01] = X_node[0b10] * Y_node[0b11] + X_node[0b11] * Y_node[0b10] + X_node[0b10] * Y_node[0b10];
    ans[0b11] = X_node.total() * Y_node.total() - ans[0b00] - ans[0b10] - ans[0b01];
  } else if (F == 0) {
    ans[0b00] = X_node.should1() * Y_node.should1();
    ans[0b01] = X_node.total() * Y_node.total() - ans[0b00];
  } else {
    ans[0b10] = X_node.should1() * Y_node.should1();
    ans[0b11] = X_node.total() * Y_node.total() - ans[0b10];
  }

  return ans;
}

Mod solve(const vuui& gates) {
  auto ans = f(gates, 1);
  return ans[0b01] + ans[0b10];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vuui gates(N);
  for(auto& [X, Y, F] : gates) {
    cin >> X >> Y >> F;
  }


  auto ans = solve(gates);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
