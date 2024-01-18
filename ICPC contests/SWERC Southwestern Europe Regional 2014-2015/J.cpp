// https://codeforces.com/gym/100783
#include <bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

struct H {
  ull x;
  H(ull x = 0) : x(x) {}
  H operator+(H o) {
    return x + o.x + (x + o.x < x);
  }
  H operator-(H o) {
    return *this + ~o.x;
  }
  H operator*(H o) {
    auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64);
  }
  ull get() const {
    return x + !~x;
  }
  bool operator==(H o) const {
    return get() == o.get();
  }
  bool operator<(H o) const {
    return get() < o.get();
  }
};
static const H C = (ull)1e11+3;
static const H P = (ull)1e9+7;

struct HashInterval2D {
  vector<vector<H>> ha;
  vector<H> pw_C, pw_P;
  HashInterval2D(vector<string> ss) : ha(SZ(ss) + 1, vector<H>(SZ(ss[0]) + 1)), pw_C(SZ(ss) + 1), pw_P(SZ(ss[0]) + 1) {
    ull x = SZ(ss), y = SZ(ss[0]);
    pw_C[0] = pw_P[0] = 1;
    fore(i, 1, x + 1) {
      pw_C[i] = pw_C[i-1] * C;
    }
    fore(i, 1, y + 1) {
      pw_P[i] = pw_P[i-1] * P;
    }
    fore(i, 0, SZ(ss)) {
      fore(j, 0, SZ(ss[0])) {
        ha[i+1][j+1] = ha[i+1][j] * C + ha[i][j+1] * P - ha[i][j] * C * P + ss[i][j];
      }
    }
  }
  H hashInterval(ull i0, ull j0, ull i1, ull j1) {
    return ha[i1][j1] - ha[i0][j1] * pw_P[i1 - i0] - ha[i1][j0] * pw_C[j1 - j0] + ha[i0][j0] * pw_P[i1 - i0] * pw_C[j1 - j0];
  }
};

ull solve(vector<string> p, vector<string> m) {
  ull hp = p.size(), wp = p[0].size(), hm = m.size(), wm = m[0].size();

  HashInterval2D ph = HashInterval2D(p), mh = HashInterval2D(m);
  H pH = ph.hashInterval(0, 0, hp, wp);

  ull ans = 0;
  fore(i, 0, hm + 1 - hp) {
    fore(j, 0, wm + 1 - wp) {
      if (mh.hashInterval(i, j, i + hp, j + wp) == pH) {
        ans++;
      }
    }
  }

  return ans;
}

/* ull slowSolve(vector<string> p, vector<string> m) {
  ull hp = p.size(), wp = p[0].size(), hm = m.size(), wm = m[0].size();
  ull ans = 0;

  fore(i, 0, hm + 1 - hp) {
    fore(j, 0, wm + 1 - wp) {
      bool is = true;
      fore(i1, 0, hp) {
        fore(j1, 0, wp) {
          if (p[i1][j1] != m[i + i1][j + j1]) {
            is = false;
          }
        }
      }
      if (is) {
        ans++;
      }
    }
  }

  return ans;
} */

int main(){FIN;
  ull hp, wp, hm, wm;
  cin >> hp >> wp >> hm >> wm;
  vector<string> p(hp), m(hm);
  for(string& s : p) {
    cin >> s;
    /* for(char& c : s) {
      c = c == 'x' ? 1 : 0;
    } */
  }
  for(string& s : m) {
    cin >> s;
    /* for(char& c : s) {
      c = c == 'x' ? 1 : 0;
    } */
  }

  cout << solve(p, m) << '\n';

/*   fore(_,0,1000) {
    ull hp = 100, wp = 100, hm = 150, wm = 150;
    vector<string> p(hp), m(hm);
    for(string& s : p) {
      s = "";
      fore(j, 0, wp) {
        s.push_back(rand() % 2 ? '0' : 'x');
      }
    }
    for(string& s : m) {
      s = "";
      fore(j, 0, wm) {
        s.push_back(rand() % 2 ? '0' : 'x');
      }
    }

    ull ans = solve(p, m);
    ull ans2 = slowSolve(p, m);
    if (ans != ans2) {
      cout << hp << ' ' << wp << ' ' << hm << ' ' << wm << '\n';
      for(string& s : p) {
        cout << s << '\n';
      }
      for(string& s : m) {
        cout << s << '\n';
      }
      cout << "ans: " << ans << ", ans2: " << ans2 << '\n';
      return EXIT_FAILURE;
    }
  } */

	return 0;
}
