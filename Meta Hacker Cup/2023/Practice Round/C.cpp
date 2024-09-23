// https://www.facebook.com/codingcompetitions/hacker-cup/2023/practice-round/problems/C?source=codeforces

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull with_sum(const vu& As, ull sum) {
  if (sum <= As.back()) {
    return -1;
  }
  ull N = (As.size() + 1)/2;
  ull ans = -1;

  {
    ull this_ans;
    bool used = false, valid = true;
    for(ull i = 0;; i++) {
      if (i - used == N - 1) {
        if (!used) {
          this_ans = sum - As[i];
          used = true;
        } else {
          valid = As[i - used] + As[2*N - 1 - 1 - i] == sum;
        }
        break;
      }
      if (As[i - used] + As[2*N - 1 - 1 - i] != sum) {
        if (used) {
          valid = false;
          break;
        }
        used = true;
        this_ans = sum - As[2*N - 1 - 1 - i];
      }
    }
    if (valid) {
      ans = this_ans;
    }
  }

  {
    ull this_ans;
    bool used = false, valid = true;;
    for(ull i = 0;;i++) {
      if (i - used == N - 1) {
        if (!used) {
          this_ans = sum - As[i];
          used = true;
        } else {
          valid = As[i] + As[2*N - 1 - 1 - i + used] == sum;
        }
        break;
      }
      if (As[i] + As[2*N - 1 - 1 - i + used] != sum) {
        if (used) {
          valid = false;
          break;
        }
        used = true;
        this_ans = sum - As[i];
      }
    }
    if (valid) {
      ans = min(ans, this_ans);
    }
  }

  return ans;
}

ll solve1(vu As) {
  ull N = (As.size() + 1)/2;
  sort(As.begin(), As.end());

  if (N == 1) {
    return 1;
  }

  vector<ull> options;
  options.push_back(As[0] + As[2*N - 2]);
  options.push_back(As[0] + As[2*N - 3]);
  options.push_back(As[1] + As[2*N - 2]);

  ull ans = -1;
  for (auto option : options) {
    auto this_ans = with_sum(As, option);
    ans = min(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N;
    cin >> N;
    vu As(2*N - 1);
    fore(j, 0, 2*N - 1) {
      cin >> As[j];
    }

    auto ans = solve1(As);
    cout << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
