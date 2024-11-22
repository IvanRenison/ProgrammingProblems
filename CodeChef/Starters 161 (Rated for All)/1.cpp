// https://www.codechef.com/problems/TWOCARD

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


bool solve(vu& As, vu& Bs) {
  ull N = SZ(As);

  ull max_A = As[0];
  ull max_Ai = 0;
  ull second_max_A = 0;
  ull second_max_Ai = -1;
  fore(i, 1, N) {
    if (As[i] > max_A) {
      second_max_A = max_A;
      second_max_Ai = max_Ai;
      max_A = As[i];
      max_Ai = i;
    } else if (As[i] > second_max_A) {
      second_max_A = As[i];
      second_max_Ai = i;
    }
  }

  fore(i, 0, N) {
    auto [alice_A, alice_B] = make_tuple(As[i], Bs[i]);

    ull bob_A, bob_B;
    if (i != max_Ai) {
      bob_A = max_A;
      bob_B = Bs[max_Ai];
    } else {
      bob_A = second_max_A;
      bob_B = Bs[second_max_Ai];
    }

    if (max(alice_A, alice_B) > max(bob_A, bob_B)) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    ull N;
    cin >> N;
    vu As(N), Bs(N);
    fore(i, 0, N) {
      cin >> As[i];
    }
    fore(i, 0, N) {
      cin >> Bs[i];
    }


    bool ans = solve(As, Bs);
    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

}
