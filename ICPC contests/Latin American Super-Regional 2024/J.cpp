// https://codeforces.com/gym/105053/problem/J

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
const ld eps = 1e-12;

bool ord(uuuu a, uuuu b) {
  auto [A0, U0, B0, W0] = a;
  auto [A1, U1, B1, W1] = b;

  //return (ld)A0 / (ld)B0 < (ld)A1 / (ld)B1;
  return A0 * B1 < A1 * B0;
}

ld solve(const vuuuu& resources) {

  vuuuu resources_A, resources_B;
  for (auto [A, U, B, W] : resources) {
    if (A <= B) {
      resources_A.push_back({A, U, B, W});
    } else {
      resources_B.push_back({A, U, B, W});
    }
  }

  sort(ALL(resources_A), ord);
  sort(ALL(resources_B), ord);
  reverse(ALL(resources_B));

  resources_A.insert(resources_A.end(), ALL(resources_B));

  ull total_A = 0, total_B = 0; // number of persons

  for (auto [A, U, B, W] : resources) {
    total_A += A * U, total_B += B * W;
  }

  ld used_A = 0, used_B = 0;
  for (auto [A, U, B, W] : resources_A) {
    if (A <= B && used_A < (ld)total_A) {
      if (used_A + (ld)A * (U + W) <= (ld)total_A + eps) {
        used_A += A * (U + W);
      } else {
        ld d = total_A - used_A;

        used_A += d;

        ld left = (ld)(U + W) - d / (ld)A;
        assert(left > 0);

        used_B += left * (ld)B;
      }
    } else {
      if (used_B + (ld)B * (U + W) <= (ld)total_B + eps) {
        used_B += B * (U + W);
      } else {
        ld d = (ld)total_B - used_B;

        used_B += d;

        ld left = (ld)(U + W) - (ld)d / (ld)B;
        assert(left > 0);

        used_A += left * (ld)A;
      }
    }
  }

  assert(used_A <= (ld)total_A + eps);
  assert(used_B <= (ld)total_B + eps);

  ld ans = used_A + used_B;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vuuuu resources(N);
  for (auto& [A, U, B, W] : resources) {
    cin >> A >> U >> B >> W;
  }

  auto ans = solve(resources);
  cout << setprecision(10) << fixed;
  cout << ans << '\n';

/*   fore(_, 0, 100) {
    ull N = 2;
    vuuuu resources(N);
    for (auto& [A, U, B, W] : resources) {
      A = rand() % 3 + 1;
      U = rand() % 3 + 1;
      B = rand() % 3 + 1;
      W = rand() % 3 + 1;
    }

    cerr << N << '\n';
    for (auto [A, U, B, W] : resources) {
      cerr << A << ' ' << U << ' ' << B << ' ' << W << '\n';
    }
    cerr << endl;

    auto ans = solve(resources);
  } */

  return EXIT_SUCCESS;
}
