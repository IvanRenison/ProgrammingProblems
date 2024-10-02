// https://codeforces.com/gym/101309

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const ull inf = 1ull << 60;

typedef array<ull, 10> Vec;
typedef array<Vec, 10> Mat;

const Vec id = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

Vec mul(const Vec& v, const Vec& w) {
  Vec ans;
  fore(i, 0, 10) {
    ans[i] = w[v[i]];
  }
  return ans;
}

Vec pow(Vec v, ull e) {
  Vec ans = id;
  while (e > 0) {
    if (e % 2 == 1) {
      ans = mul(ans, v);
    }
    v = mul(v, v);
    e /= 2;
  }
  return ans;
}

Vec getMul(const Mat& m, ull a) {
  Vec v;
  fore(i, 0, 10) {
    v[i] = m[i][a];
  }
  return v;
}

/*
a b

Dígito i:
  extra_start + dist * 10^(i+1) + extra * 10^i + extra_end = b - a

  (a + extra_start + 1) % 10^i = 0
  extra_start = 10^i - (a + 1) % 10^i

  dist = (b - (a + extra_start + 1)) / 10^(i+1)
  extra = (b - (a + extra_start + 1)) % 10^(i+1)

  extra_end = b - (a + extra_start + dist * 10^(i+1) + extra * 10^i)


*/

ull solve(const Mat& m, ull a, ull b) {
  ull ans = 0;

  Mat mat = m;

  ull a_ = a, b_ = b;

  a++;
  for (ull t = 1; b > 0; t *= 10, a = (a + 9) / 10, b /= 10) {
    ull da = a % 10, db = b % 10;
    ull extra_start = t - a_ % t - 1;
    ull dist = (b_ - a_ - extra_start - 1) / (t * 10);
    ull extra = ((b_ - a_ - extra_start - 1) % (t * 10)) / t;
    assert(extra < 10);
    ull extra_end = b_ - (a_ + extra_start + dist * t * 10 + extra * t);

    assert(extra_end <= b_);
    assert(extra_start + dist * t * 10 + extra * t + extra_end == b_ - a_);

    Vec v = id;

    // extra start
    {
      Vec v2 = getMul(m, (a + 9) % 10);
      v2 = pow(v2, extra_start);
      v = mul(v, v2);
    }

    // dist
    {
      Vec v2 = id;
      fore(i, 0, 10) {
        Vec v3 = getMul(mat, (da + i) % 10);
        v2 = mul(v2, v3);
      }
      v2 = pow(v2, dist);
      v = mul(v, v2);
    }

    // extra
    fore(i, 0, extra) {
      Vec v2 = getMul(mat, (db + 10 - (extra - i)) % 10);
      v = mul(v, v2);
    }

    // extra end
    {
      Vec v2 = getMul(m, db);
      v2 = pow(v2, extra_end);
      v = mul(v, v2);
    }


    ull this_ans = v[(a + 9) % 10];
    ans += this_ans * t;

    // Update mat
    Mat mat2;
    fore(i, 0, 10) {
      Vec v = getMul(mat, i);
      v = pow(v, 10);
      fore(j, 0, 10) {
        mat2[j][i] = v[j];
      }
    }
    mat = mat2;
  }

  return ans;
}

ull force(const Mat& m, ull a, ull b) {
  ull k = 0, k10 = 1;
  while (k10 <= b) {
    k10 *= 10;
    k++;
  }

  auto f = [&](ull x, ull y) -> ull {
    ull ans = 0;
    for (ull t = 1; t < k10; t *= 10, y /= 10, x /= 10) {
      ans += t * m[x % 10][y % 10];
    }
    return ans;
  };

  ull ans = a;
  fore(i, a + 1, b + 1) {
    ans = f(ans, i);
  }

  return ans;
}

int main(void) {
  ios::sync_with_stdio(0), cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("binary.in","r",stdin);
  freopen("binary.out","w",stdout);
#endif

  Mat m;
  fore(i, 0, 10) {
    fore(j, 0, 10) {
      cin >> m[i][j];
    }
  }
#ifndef TEST
  ull a, b;
  cin >> a >> b;

  ull ans = solve(m, a, b);
  cout << ans << '\n';
#else
  fore(_, 0, 100000) {
    ull a = rand() % 10;
    ull b = rand() % 200 + a + 1;
    ull ans = solve(m, a, b);
    ull ansf = force(m, a, b);
    if (ans != ansf) {
      cerr << "FAIL " << a << ' ' << b << '\n' << ans << ' ' << ansf << endl;
      return 1;
    }
  }
#endif


}
