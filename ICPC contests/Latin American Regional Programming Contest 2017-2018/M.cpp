// https://codeforces.com/gym/101889

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(a) a.begin(), a.end()

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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(basic_string<int>& s, int lim=304) { // or basic_string<int>
		int n = s.size() + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			fore(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			fore(i,0,n) ws[x[i]]++;
			fore(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			fore(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		fore(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

Mod solve(const vector<vu>& vss) {

  basic_string<int> Vs;
  vu starts;
  for(const vu& vs : vss) {
    starts.push_back(Vs.size());
    for(ull v : vs) {
      Vs.push_back(v);
    }
    Vs.push_back(301);
  }
  Vs.push_back(302);

  SuffixArray sa(Vs);

  vu inv_sa(sa.sa.size() - 1);
  fore(i, 0, inv_sa.size()) {
    inv_sa[sa.sa[i + 1]] = i;
  }

  rpriority_queue<uu> q;
  for (ull i : starts) {
    q.push({inv_sa[i], i});
  }

  Mod ans = 0;

  while (!q.empty()) {
    auto [p, i] = q.top();
    q.pop();

    ans = ans * Mod(365) + Mod(Vs[i]);
    if (Vs[i+1] < 301) {
      q.push({inv_sa[i+1], i+1});
    }
  }

  ans *= Mod(365);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<vu> vss(N);
  for(vu& vs : vss) {
    ull K;
    cin >> K;
    vs = vu(K);
    for(ull& v : vs) {
      cin >> v;
    }
  }

  auto ans = solve(vss);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
