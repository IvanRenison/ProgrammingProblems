// https://codeforces.com/gym/104736/problem/F
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool isPal(ull N, ull b) {
  vu rep;
  while (N > 0) {
    rep.push_back(N % b);
    N /= b;
  }
  fore(i, 0, rep.size()/2) {
    if (rep[i] != rep[rep.size() - 1 - i]) {
      return false;
    }
  }

  return true;
}

ull sqrtull(ull N) {
  ull l = 0, r = N;
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (m * m >= N) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

vu force(ull N) {
  if (N == 2) {
    return {};
  }
  vu ans;

  fore(b, 2, N) {
    if (isPal(N, b)) {
      ans.push_back(b);
    }
  }
  return ans;
}

vu solve(ull N) {
  if (N == 2) {
    return {};
  }
  vu ans;

  ull lim = sqrtull(N);

  //cerr << "lim: " << lim << endl;

  fore(b, 2, lim + 1) {
    if (isPal(N, b)) {
      ans.push_back(b);
    }
  }
  fore(d, 1, lim) {
    // d = N / b
    // b*d + x = N
    // b = (N - x)/d
    ull N_ = N - d;
    ull b = N_ / d;
    if (b > lim && N_ % b == 0) {
      ans.push_back(b);
    }
  }

  sort(ans.begin(), ans.end());

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;

  auto ans = solve(N);
  if (ans.size() == 0) {
    cout << "*\n";
  } else {
    for (ull a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }


/*   fore(N, 2, 10)
    fore(b, 2, N) {
      if (isPal(N, b))
        cout << b << ' ' << N << '\n';
  } */

/*   fore(N, 2, 1000) {
    vu ans = solve(N);
    vu ans2 = force(N);
    if (ans != ans2) {
      cout << N << ": ";
      if (ans.size() == 0) {
        cout << "*\n";
      } else {
        for (ull a : ans) {
          cout << a << ' ';
        }
        cout << '\n';
      }
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
