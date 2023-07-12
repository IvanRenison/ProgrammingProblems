// https://codeforces.com/group/4zVk9dZl6Q/contest/390672/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(vector<ull> fs) {
  ull n = fs.size();
  fore(i, 0, n) {
    if (fs[fs[fs[i]]] == i) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<ull> fs(n);
  for (ull& f : fs) {
    cin >> f;
    f--;
  }

  if (solve(fs)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
