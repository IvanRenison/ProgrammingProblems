// https://codeforces.com/contest/1829/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<bool> parse1(void) {
  ull n;
  cin >> n;
  vector<bool> bs(n);
  fore(i, 0, n) {
    char c;
    cin >> c;
    bs[i] = c == '1';
  }
  return bs;
}

ull solve1(vector<bool> bs) {
  ull n = bs.size();
  ull count = 0;
  ull my_max = 0;
  fore(i, 0, n) {
    if (!bs[i]) {
      count++;
    }
    else {
      my_max = max(my_max, count);
      count = 0;
    }
  }
  my_max = max(my_max, count);

  return my_max;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
