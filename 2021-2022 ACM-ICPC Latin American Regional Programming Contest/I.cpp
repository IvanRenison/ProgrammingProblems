//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef unsigned char uc;
#define fore(i, a, b) for (ull i = a; i < b; i++)


static inline void solve(void) {

}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string T;
  ull N;
  cin >> T >> N;

  uc wday;

  switch (T) {
    case ("Mon") wday = 0;
    case ("Tue") wday = 1;
    case ("Wed") wday = 2;
    case ("Thu") wday = 3;
    case ("Fri") wday = 4;
    case ("Sat") wday = 5;
    case ("Sun") wday = 6;

  }


  return EXIT_SUCCESS;
}
