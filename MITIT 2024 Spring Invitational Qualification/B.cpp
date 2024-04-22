// https://codeforces.com/gym/105125/problem/B

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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

bool check(vu As, vu ans) {

  ull j = 1;

  for (ull i : ans) {
    if (As[i] == 0) {
      return false;
    }
    if (j % 2 == 1) {
      As[i]--;
    } else {
      if (As[i] == 1) {
        return false;
      }
      As[i]--;
    }

    j++;
  }

  return true;
}

optional<vu> force(vu As) {
  ull N = As.size();

  vu ans;
  fore(i, 0, N) {
    fore(_, 0, As[i]) {
      ans.push_back(i);
    }
  }

  do {
    if (check(As, ans)) {
      return ans;
    }
  } while (next_permutation(ALL(ans)));

  return {};
}

optional<vu> solve(vu As) {
  ull N = As.size();

  ull odds_count = 0, odds_sum = 0;
  ull even_count = 0, even_sum = 0;

  fore(i, 0, N) {
    if (As[i] % 2 == 1) {
      odds_count++;
      odds_sum += As[i];
    } else if (As[i] > 0) {
      even_count++;
      even_sum += As[i];
    }
  }

  if (odds_count % 2 == 0) {
    return {};
  }

  if (odds_count > odds_sum - odds_count + even_sum - even_count * 2 + 1) {
    return {};
  }





  vu ones, odds, twos, evens;
  fore(i, 0, N) {
    if (As[i] == 1) {
      ones.push_back(i);
    } else if (As[i] == 2) {
      twos.push_back(i);
    } else if (As[i] % 2 == 1) {
      odds.push_back(i);
    } else if (As[i] > 0) {
      evens.push_back(i);
    }
  }

  sort(ALL(odds), [&](ull a, ull b) {
    return As[a] < As[b] || (As[a] == As[b] && a < b);
  });

  vu ans;

  if (!ones.empty()) {
    ull i1 = ones.back();
    ones.pop_back();

    ans.push_back(i1);

    As[i1]--;
  } else {
    ull io = odds.back();
    odds.pop_back();

    ans.push_back(io);

    As[io]--;

    if (As[io] > 2) {
      evens.push_back(io);
    } else if (As[io] == 2) {
      twos.push_back(io);
    }
  }

  while (!ones.empty() && !odds.empty()) {
    ull i1 = ones.back();
    ones.pop_back();
    ull io = odds.back();
    odds.pop_back();

    ans.push_back(io);
    ans.push_back(i1);

    As[io]--;
    As[i1]--;

    if (As[io] > 2) {
      evens.push_back(io);
    } else if (As[io] == 2) {
      twos.push_back(io);
    }
  }

  while (!odds.empty()) {
    ull io = odds.back();
    odds.pop_back();
    ull io_ = odds.back();
    odds.pop_back();

    ans.push_back(io);
    ans.push_back(io_);

    As[io]--;
    As[io_]--;

    if (As[io] > 2) {
      evens.push_back(io);
    } else if (As[io] == 2) {
      twos.push_back(io);
    }

    if (As[io_] > 2) {
      evens.push_back(io_);
    } else if (As[io_] == 2) {
      twos.push_back(io_);
    }
  }

  while (!ones.empty()) {
    ull io = ones.back();
    ones.pop_back();
    ull io_ = ones.back();
    ones.pop_back();

    ull ie = evens.back();
    evens.pop_back();


    ans.push_back(ie);
    ans.push_back(io);
    ans.push_back(ie);
    ans.push_back(io_);

    As[io]--;
    As[io_]--;

    As[ie] -= 2;
    if (As[ie] > 2) {
      evens.push_back(ie);
    } else if (As[ie] == 2) {
      twos.push_back(ie);
    }
  }


  while (!evens.empty()) {
    ull ie = evens.back();
    evens.pop_back();

    fore(_, 0, As[ie]) {
      ans.push_back(ie);
    }

    As[ie] = 0;
  }

  while (!twos.empty()) {
    ull ie = twos.back();
    twos.pop_back();

    fore(_, 0, As[ie]) {
      ans.push_back(ie);
    }

    As[ie] = 0;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  #ifndef TESTING
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu as(N);
    fore(j, 0, N) {
      cin >> as[j];
    }

    auto ans = solve(as);

    if (ans.has_value()) {
      assert(check(as, ans.value()));
      cout << "Yes\n";
      for (ull a : ans.value()) {
        cout << a + 1 << " ";
      }
      cout << "\n";
    } else {
      cout << "No\n";
    }
  }
  #endif

  #ifdef TESTING
  fore(_, 0, 10000) {
    ull N = rand() % 100 + 1;
    vu As(N);
    ull As_sum = 0;
    fore(i, 0, N) {
      As[i] = rand() % 100;
      As_sum += As[i];
    }

    auto ans = solve(As);

    if (ans.has_value()) {
      if(!check(As, ans.value())) {
        cerr << "Error\n";
        cerr << N << "\n";
        for (ull a : As) {
          cerr << a << " ";
        }
        cerr << endl;
        cerr << "ans = ";
        for (ull a : ans.value()) {
          cerr << a << " ";
        }
        cerr << endl;
        return EXIT_FAILURE;
      }
    }


    /* auto ansf = force(As);
    if (ans.has_value() != ansf.has_value()) {
      cout << N << "\n";
      for (ull a : As) {
        cout << a << " ";
      }
      cout << "\n";
      cout << "solve = ";
      if (ans.has_value()) {
        for (ull a : ans.value()) {
          cout << a << " ";
        }
      } else {
        cout << "No";
      }
      cout << "\n";
      cout << "force = ";
      if (ansf.has_value()) {
        for (ull a : ansf.value()) {
          cout << a << " ";
        }
      } else {
        cout << "No";
      }
      cout << "\n" << endl;
      //return EXIT_FAILURE;
    } */
  }
  #endif

  return EXIT_SUCCESS;
}
/*

3
3 3 3

*/