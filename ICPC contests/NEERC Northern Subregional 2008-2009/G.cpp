// https://codeforces.com/gym/100623

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
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl
#define M_PI 3.14159265358979323846

const ull inf = 1ull << 60;
const ld eps = 1e-9;


enum Dir { UP, DOWN, LEFT, RIGHT };

bool connected(ull n, uu p, Dir d) {
  auto [x, y] = p;

  if (n == 1) {
    return d == UP;
  }

  ull sz = (1ull << n) - 1;

  if (x > sz/2) {
    Dir d_ = d == LEFT ? RIGHT
           : d == RIGHT ? LEFT
           : d;
    return connected(n, {sz - x - 1, y}, d_);
  }

  if (y == sz/2) {
    if (d == LEFT) {
      return x != 0;
    } else if (d == RIGHT) {
      return x != sz;
    } else if (d == UP) {
      if (x == sz/2) {
        return true;
      } else { // x < sz/2
        return connected(n - 1, {0, sz/2 - x - 1}, LEFT);
      }
    } else { // d == DOWN
      if (x == sz/2) {
        return false;
      } else { // x < sz/2
        return connected(n - 1, {x, sz/2 - 1}, UP);
      }
    }
  } else if (y < sz/2) {
    if (x == sz/2) {
      if (d == LEFT || d == RIGHT) {
        return connected(n - 1, {x - 1, y}, RIGHT);
      } else if (d == UP) {
        return y != sz/2 - 1;
      } else { // d == DOWN
        return true;
      }
    } else { // x < sz/2
      return connected(n - 1, {x, y}, d);
    }
  } else { // y > sz/2
    if (x == sz/2) {
      if (d == LEFT || d == RIGHT) {
        return connected(n - 1, {y - sz/2 - 1, 0}, DOWN);
      } else { // d == UP || d == DOWN
        return true;
      }
    } else { // x < sz/2
      Dir d_ = d == LEFT ? UP
             : d == RIGHT ? DOWN
             : d == UP ? RIGHT
             : LEFT;
      return connected(n - 1, {y - sz/2 - 1, sz/2 - x - 1}, d_);
    }
  }
}

/* void print(ull n) {
  ull sz = (1ull << n) - 1;
  fore(j, 0, sz) {
    fore(i, 0, sz) {
      cout << (connected(n, {i, sz - j - 1}, UP) ? 'U' : ' ');
    }
    cout << '\n';
  }
  fore(j, 0, sz) {
    fore(i, 0, sz) {
      cout << (connected(n, {i, sz - j - 1}, DOWN) ? 'D' : ' ');
    }
    cout << '\n';
  }
  fore(j, 0, sz) {
    fore(i, 0, sz) {
      cout << (connected(n, {i, sz - j - 1}, LEFT) ? 'L' : ' ');
    }
    cout << '\n';
  }
  fore(j, 0, sz) {
    fore(i, 0, sz) {
      cout << (connected(n, {i, sz - j - 1}, RIGHT) ? 'R' : ' ');
    }
    cout << '\n';
  }
} */

ld calcSquareValue(ld α, Dir d, ld c) {
  if (d == LEFT) {
    return 1.0 - calcSquareValue(M_PI/2.0 - α, UP, 1.0 - c);
  } else if (d == RIGHT) {
    return calcSquareValue(M_PI/2.0 - α, UP, c);
  } else if (d == DOWN) {
    return 1.0 - calcSquareValue(α, UP, 1.0 - c);
  } else { // d == UP
    ld δ = atan(1.0/(1.0 - c));
    if (α <= δ) {
      ld o = (1.0 - c) * tan(α);
      //assert(o >= 0.0);
      //assert(o <= 1.0 + eps);
      return 1.0 - (1.0 - c) * o / 2.0;
    } else {
      ld β = M_PI/2.0 - α;
      ld o = tan(β);
      //assert(o >= 0.0);
      //assert(o <= 1.0 + eps);
      return c + o / 2.0;
    }
  }
}

ld solve(ull n, ld α) {

  vector<tuple<uu, Dir, ld>> s;

  ull sz = (1ull << n) - 1;

  fore(x, 0, sz) {
    if (connected(n, {x, sz - 1}, UP)) {
      s.push_back({{x, sz - 1}, UP, 0.0});
    }
  }
  //vector<vd> vis(sz, vd(sz, 0));

  ld ans = 0.0;
  while (!s.empty()) {
    auto [p, d, c] = s.back();
    s.pop_back();
    auto [x, y] = p;

    ld this_ans = calcSquareValue(α, d, c);
    //vis[y][x] = this_ans;
    //assert(this_ans <= 1.0);
    ans += this_ans;

    if (d == RIGHT) {
      ld δ = atan(1.0 - c);
      //assert(δ >= 0.0);
      //assert(δ <= M_PI/2.0 + eps);
      if (α > δ + eps) {
        if (connected(n, p, UP)) {
          ld o = 1.0 - (1.0 - c) / tan(α);
          //assert(o > 0.0 && o <= 1.0);
          s.push_back({{x, y + 1}, DOWN, o});
        }
        if (connected(n, p, LEFT)) {
          s.push_back({{x - 1, y}, RIGHT, 1.0});
        }
      } else {
        if (connected(n, p, LEFT)) {
          ld o = c + tan(α);
          //assert(o > 0.0);
          //assert(o <= 1.0 + eps);
          s.push_back({{x - 1, y}, RIGHT, min((ld)1.0, o)});
        }
      }
      if (connected(n, p, DOWN)) {
        s.push_back({{x, y - 1}, UP, 1.0});
      }
    } else if (d == LEFT) {
      ld δ = atan(c);
      //assert(δ >= 0.0);
      //assert(δ <= M_PI/2.0 + eps);
      if (α + eps < δ) {
        if (connected(n, p, RIGHT)) {
          ld o = c - tan(α);
          //assert(o > 0.0 && o <= 1.0);
          s.push_back({{x + 1, y}, LEFT, o});
        }
        if (connected(n, p, DOWN)) {
          s.push_back({{x, y - 1}, UP, 1.0});
        }
      } else {
        if (connected(n, p, DOWN)) {
          ld o = tan(M_PI/2 - α) * c;
          //assert(o > 0.0);
          //assert(o <= 1.0 + eps);
          s.push_back({{x, y - 1}, UP, min((ld)1.0, o)});
        }
      }
    } else if (d == UP) {
      ld δ = atan(1.0/(1.0 - c));
      //assert(δ >= 0.0);
      //assert(δ <= M_PI/2.0 + eps);
      if (α + eps < δ) {
        if (connected(n, p, RIGHT)) {
          ld o = 1.0 - (1.0 - c) * tan(α);
          //assert(o > 0.0 && o <= 1.0);
          s.push_back({{x + 1, y}, LEFT, o});
        }
        if (connected(n, p, DOWN)) {
          s.push_back({{x, y - 1}, UP, 1.0});
        }
      } else {
        if (connected(n, p, DOWN)) {
          ld o = c + tan(M_PI/2.0 - α);
          //assert(o > 0.0);
          //assert(o <= 1.0 + eps);
          s.push_back({{x, y - 1}, UP, min((ld)1.0, o)});
        }
      }
      if (connected(n, p, LEFT)) {
        s.push_back({{x - 1, y}, RIGHT, 1.0});
      }
    } else { // d == DOWN
      ld δ = M_PI/2.0 - atan(c);
      if (α > δ + eps) {
        if (connected(n, p, UP)) {
          ld o = c - tan(M_PI/2.0 - α);
          //assert(o > 0.0 && o <= 1.0);
          s.push_back({{x, y + 1}, DOWN, o});
        }
        if (connected(n, p, LEFT)) {
          s.push_back({{x - 1, y}, RIGHT, 1.0});
        }
      } else {
        if (connected(n, p, LEFT)) {
          //assert(α > 0.0);
          ld o = c / tan(M_PI/2.0 - α);
          //assert(o > 0.0);
          //assert(o <= 1.0 + eps);
          //DBG(o);
          s.push_back({{x - 1, y}, RIGHT, min((ld)1.0, o)});
        }
      }
    }

  }

/*   cerr << setprecision(2);
  for (ull y = sz - 1; y < sz; y--) {
    fore(x, 0, sz) {
      if (vis[y][x] == 0.0) {
        cerr << " \t";
      } else {
        cerr << vis[y][x] << '\t';
      }
    }
    cerr << '\n';
  } */

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
#ifdef ONLINE_JUDGE
  freopen("ground.in", "r", stdin);
  freopen("ground.out", "w", stdout);
#endif

  ull n;
  ull a;
  cin >> n >> a;
  ld α = (ld)a * M_PI / 180.0;

  auto ans = solve(n, α);
  cout << setprecision(10);
  cout << ans << '\n';

/*   cout << setprecision(10);
  fore(a, 0, 90) {
    ld last = 0;
    fore(n, 1, 13) {
      ld α = (ld)a * M_PI / 180.0;
      auto ans = solve(n, α);
      //assert(ans > last);
      last = ans;
      cout << n << ' ' << a << ' ' << ans << endl;
    }
  } */


  return EXIT_SUCCESS;
}
