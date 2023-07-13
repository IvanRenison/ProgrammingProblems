//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool query(ull n) {
  cout << n << endl;
  string s;
  cin >> s;
  return s == "yes";
}

bool solve(void) {
  vector<ull> ps = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
  for (ull i = 0; ps[i] * ps[i] <= 100; i++) {
    ull p = ps[i];
    if (query(p)) {
      for (ull j = i; p * ps[j] <= 100; j++) {
        if (query(p * ps[j])) {
          return false;
        }
      }
      break;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  if (solve()) {
    cout << "prime" << endl;
  } else {
    cout << "composite" << endl;
  }

  return EXIT_SUCCESS;
}
