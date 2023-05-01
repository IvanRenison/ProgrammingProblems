// https://codeforces.com/gym/104252/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

static inline ull solve(ull N, ull E, ull K) {

  ull space0 = E;
  ull space1 = N - (E + K);

  if (space0 != space1 && space0 != K && space1 != K) {
    return 0;
  }

  if (space0 == space1) {
    if (space0 == 0) {
      return 0;
    }
    if (space0 == 1) {
      if (K == 1) {
        return 2;
      }
      return 1;
    }
    if (space0 == 2) {
      if (K == 1) {
        return 2;
      }
      if (K == 2) {
        return 3;
      }
      return 1;
    }
    if (space0 == 3) {
      if (K == 1) {
        return 1;
      }
      if (K == 2) {
        return 2;
      }
      if (K == 3) {
        return 3;
      }
      return 0;
    }
    if (space0 == 4) {
      if (K == 1) {
        return 1;
      }
      if (K == 2) {
        return 0;
      }
      if (K == 3) {
        return 1;
      }
      if (K == 4) {
        return 2;
      }
      return 0;
    }
    return 0;
  }

  if (space0 != K) {
    ull temp = space0;
    space0 = space1;
    space1 = temp;
  }

  assert(space0 == K);
  assert(space1 != K);

  if (space0 == 1) {
    return 1;
  }
  if (space0 == 2) {
    if (space1 == 1) {
      return 2;
    }
    return 1;
  }
  if (space0 == 3) {
    if (space1 == 1) {
      return 1;
    }
    if (space1 == 2) {
      return 2;
    }
    return 0;
  }
  if (space0 == 4) {
    if (space1 == 1) {
      return 1;
    }
    if (space1 == 2) {
      return 0;
    }
    if (space1 == 3) {
      return 1;
    }
    return 0;
  }

  return 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, K, E;

  cin >> N >> K >> E;

  cout << solve(N, E, K) << endl;

  return EXIT_SUCCESS;
}
