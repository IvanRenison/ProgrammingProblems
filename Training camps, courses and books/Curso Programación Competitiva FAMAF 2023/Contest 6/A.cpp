// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

void parse1(void) {

}

ull solve1(ull v) {
  if (v == 2) {
    return v;
  }
  return 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull v;
  cin >> v;
  cout << solve1(v) << '\n';

  return EXIT_SUCCESS;
}
