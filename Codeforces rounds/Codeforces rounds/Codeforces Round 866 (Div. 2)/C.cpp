// https://codeforces.com/contest/1820/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

bool solve1(vector<ull> as) {
  ull n = as.size();

  vector<ull> amounts(n+2, 0);
  ull biggers = 0;

  for (ull a : as) {
    if (a < n + 2) {
      amounts[a]++;
    }
    else {
      biggers++;
    }
  }

  ull mex = 0;
  optional<ull> min_repeated;
  fore(i, 0, n+2) {
    if (amounts[i] == 0) {
      mex = i;
      break;
    }
    if (!min_repeated.has_value() && amounts[i] > 1) {
      min_repeated = i;
    }
  }

  ull mexpp = mex+1;

  bool mexpp_found = false;
  ull first_mexpp = 0;
  ull last_mexxpp = 0;
  fore(i, 0, n) {
    if (as[i] == mexpp) {
      if (!mexpp_found) {
        mexpp_found = true;
        first_mexpp = i;
      }
      last_mexxpp = i;
    }
  }

  if (mexpp_found) {
    fore(i, first_mexpp, last_mexxpp+1) {
      as[i] = mex;
    }

    vector<ull> new_amounts(n+2, 0);

    for (ull a : as) {
      if (a < n + 2) {
        new_amounts[a]++;
      }
    }

    ull new_mex = 0;
    fore(i, 0, n+2) {
      if (new_amounts[i] == 0) {
        new_mex = i;
        break;
      }
    }

    return new_mex == mexpp;
  }
  else {
    ull biggers_than_mex = biggers;
    fore(i, mex, n+2) {
      biggers_than_mex += amounts[i];
    }

    return (min_repeated.has_value() && min_repeated.value() < mex) || biggers_than_mex > 0;
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    if (solve1(parse1())) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
