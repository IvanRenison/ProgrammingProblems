// https://codeforces.com/gym/106682/problem/D
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct Tree {
	typedef bool T;
	static constexpr T neut = true;
	T f(T a, T b) { return a && b; } // (any associative fn)
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

struct BigInt {
  vu d;
  Tree t;

  BigInt(vu& d) : d(d), t(d.size()) {
    assert(d.back() != 0);
    ull sum = 0;
    fore(i, 0, d.size()) {
      sum += d[i];
      t.upd(i, d[i] == 9);
    }
    assert(sum % 9 == 0);
  }

  bool all_nines() {
    return t.query(0, d.size());
  }

  void resta(ull c) {
    // Restar 10^c - 1
    assert(c + 1 == d.size());
    assert(!all_nines());


    // Primero resto 10^c
    d.back() -= 1;
    t.upd(d.size() - 1, d.back() == 9);
    while (d.back() == 0) {
      d.pop_back();
      assert(!d.empty()); // Si el número original era múltiplo de 9, esto no debería pasar
    }

    // Ahora sumo 1
    fore(i, 0, d.size()) {
      if (d[i] != 9) {
        d[i] += 1;
        t.upd(i, d[i] == 9);
        break;
      } else {
        assert(i+1 < d.size()); // Si el número original era múltiplo de 9, esto no debería pasar
        d[i] = 0;
        t.upd(i, false);
      }
    }
  }

  void print() {
    for (ull i = d.size(); i--;) {
      cerr << d[i];
    }
    cerr << endl;
  }
};

ull solve(vu& s) {
  reverse(s.begin(), s.end());

  // s *= 9
  ull carry = 0;
  fore(i, 0, s.size()) {
    (s[i] *= 9) += carry, carry = s[i] / 10, s[i] %= 10;
  }
  if (carry) {
    s.push_back(carry);
  }

  BigInt n(s);
  // n.print();

  ull ans = 0;
  while (!n.all_nines()) {
    ans++;
    assert(!n.d.empty());
    n.resta(n.d.size() - 1);
    // n.print();
  }

  return ans + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s_;
  cin >> s_;
  vu s(s_.size());
  fore(i, 0, s.size()) {
    s[i] = s_[i] - '0';
  }

  ull ans = solve(s);
  cout << ans << '\n';
}

