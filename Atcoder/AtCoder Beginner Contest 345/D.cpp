// https://atcoder.jp/contests/abc345/tasks/abc345_d

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


bool solve(ull H, ull W, vuu ABs) {
  ull N = ABs.size();

  function<bool(ull, vu)> force = [&](ull tiles, const vu& grid) {
    ull i = inf, j = inf;

    fore(x, 0, H) {
      fore(y, 0, W) {
        if (!(grid[x] & (1 << y))) {
          i = x, j = y;
          goto out;
        }
      }
    }

    return true;

    out:;

    ull i_sz = 0, j_sz = 0;

    while (i + i_sz < H && !(grid[i + i_sz] & (1 << j))) {
      i_sz++;
    }

    while (j + j_sz < W && !(grid[i] & (1 << (j + j_sz)))) {
      j_sz++;
    }

    fore(t, 0, N) {
      if (!(tiles & (1 << t))) {
        auto [A, B] = ABs[t];

        if (A <= i_sz && B <= j_sz) {
          vu grid_ = grid;

          fore(i_, i, i + A) {
            fore(j_, j, j + B) {
              grid_[i_] |= 1 << j_;
            }
          }

          if (force(tiles | (1 << t), grid_)) {
            return true;
          }
        }

        if (B <= i_sz && A <= j_sz) {
          vu grid_ = grid;

          fore(i_, i, i + B) {
            fore(j_, j, j + A) {
              grid_[i_] |= 1 << j_;
            }
          }

          if (force(tiles | (1 << t), grid_)) {
            return true;
          }
        }
      }
    }

    return false;
  };

  ull tiles = 0;

  vu grid(H, 0);

  bool ans = force(tiles, grid);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, H, W;
  cin >> N >> H >> W;
  vuu ABs(N);
  for (auto& [A, B] : ABs) {
    cin >> A >> B;
  }

  bool ans = solve(H, W, ABs);
  if (ans) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
