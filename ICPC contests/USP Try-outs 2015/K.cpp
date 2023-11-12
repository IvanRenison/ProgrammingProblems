// https://codeforces.com/gym/101047/problem/K
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull binary_search(vector<double>& as, double a) {
  ull lower = 0, upper = as.size();
  if (as[0] > a) {
    return 0;
  }
  if (as[upper - 1] <= a) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (as[m] > a) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

double solve1(vector<double> as) {
  ull N = as.size();

  double ans = numeric_limits<double>::infinity();

  sort(as.begin(), as.end());

  fore(i, 0, N) {
    fore(j, i + 1, N) {
      double a = as[i], b = as[j];
      if (a < b) {
        swap(a, b);
      }
      ull k = binary_search(as, a - b);
      while (k == i || k == j) {
        k++;
      }
      if (k != N) {
        double c = as[k];

        if (c < a + b) {

          double p = (a + b + c) / 2;
          double area = sqrt(p * (p - a) * (p - b) * (p - c));

          if (area < ans) {
            ans = area;
          }
        }
      }
    }
  }

  if (ans == numeric_limits<double>::infinity()) {
    ans = -1;
  }

  return ans;
}

int main() {
  FIN;

  cout << setprecision(8);

  ull T;
  cin >> T;
  while (T--) {
    ull N;
    cin >> N;
    vector<double> as(N);
    for (double& a : as) {
      cin >> a;
    }
    cout << solve1(as) << '\n';
  }

  return 0;
}