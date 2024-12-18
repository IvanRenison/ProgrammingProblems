// https://codeforces.com/gym/104857/problem/I

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

ull charToNum(char c) {
  if (c >= 'a') {
    return c - 'a';
  } else {
    return c - 'A' + 26;
  }
}
char numToChar(ull n) {
  if (n < 26) {
    return 'a' + n;
  } else {
    return 'A' + n - 26;
  }
}


bool check(const vector<string>& strs, const vu& ans) {
  ull n = ans.size();

  map<string, ull> counts;
  for (const string& s : strs) {
    counts[s]++;
  }

  map<string, ull> counts_ans;
  fore(i, 0, n) {
    fore(j, 0, n) {
      ull d = i*j;

      string name = "";

      if (d < n) {
        name.push_back(numToChar(ans[d]));
      } else {
        name.push_back(numToChar(ans[d/n]));
        name.push_back(numToChar(ans[d%n]));
      }

      counts_ans[name]++;
    }
  }

  return counts == counts_ans;
}

pair<char, char> zero_one(ull n, const vector<string>& strs) {
  vu counts_digits(n);
  for (string s : strs) {
    if (s.size() == 1) {
      counts_digits[charToNum(s[0])]++;
    }
  }

  ull zero = 0;
  ull one = 0;
  fore(i, 1, n) {
    if (counts_digits[i] > counts_digits[zero]) {
      zero = i;
    }
    if (counts_digits[i] == 1) {
      one = i;
    }
  }

  return {zero, one};
}

struct CNT {
  vu left, right;
  ull i;

  CNT(ull n) : left(n), right(n) {}

  void norm() {
    sort(ALL(left)), sort(ALL(right));
  }

  bool operator<(const CNT& o) const {
    return left < o.left || (left == o.left && right < o.right);
  }
};

vector<CNT> count(ull n, const vector<string>& strs) {

  auto [zero, one] = zero_one(n, strs);

  vector<CNT> counts(n, CNT(n));
  fore(i, 0, n) {
    counts[i].i = i;
  }
  for (string s : strs) {
    ull l, r;
    if (s.size() == 1) {
      l = zero, r = charToNum(s[0]);
    } else {
      l = charToNum(s[0]), r = charToNum(s[1]);
    }

    counts[l].left[r]++;
    counts[r].right[l]++;
  }

  return counts;
}

vector<string> real(ull n) {
  vector<string> ans;
  fore(i, 0, n) {
    fore(j, 0, n) {
      ull d = i*j;
      if (d < n) {
        ans.push_back(string(1, numToChar(d)));
      } else {
        ans.push_back(string(1, numToChar(d/n)) + string(1, numToChar(d%n)));
      }
    }
  }

  return ans;
}

string solve(ull n, const vector<string>& strs) {

  vector<CNT> counts = count(n, strs);
  vector<CNT> real_counts = count(n, real(n));

  fore(i, 0, n) {
    counts[i].norm();
    real_counts[i].norm();
  }

  sort(ALL(counts));
  sort(ALL(real_counts));

  vu ans(n);
  fore(i, 0, n) {
    ans[real_counts[i].i] = counts[i].i;
  }

  assert(check(strs, ans));

  string res;
  fore(i, 0, n) {
    res.push_back(numToChar(ans[i]));
  }

  return res;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull T;
  cin >> T;
  while (T--) {
    ull n;
    cin >> n;
    vector<string> strs(n*n);
    for (string& s : strs) {
      cin >> s;
    }

    auto ans = solve(n, strs);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}