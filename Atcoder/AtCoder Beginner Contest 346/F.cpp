// https://atcoder.jp/contests/abc346/tasks/abc346_f

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/* // Es S subsequencia de T?
bool subseq(const string& S, const string& T) {
  ull n = T.size(), m = S.size();

  ull i = 0, j = 0;

  while (i < n && j < m) {
    j += S[j] == T[i];
    i++;
  }

  return j == m;
}

ull force(ull N, const string& S, const string& T) {

  string s;
  fore(_, 0, N) {
    s += S;
  }

  for (ull k = 1;; k++) {
    string t;
    for (char c : T) {
      fore(_, 0, k) {
        t += c;
      }
    }

    if (!subseq(t, s)) {
      return k - 1;
    }
  }
} */

ull solve(ull N, const string& S, const string& T) {

  vector<vu> apps_S(26);

  fore(i, 0, S.size()) {
    apps_S[S[i] - 'a'].push_back(i);
  }

  function<bool(ull)> can = [&](ull k) {
    ull n = 0, p = 0;

    fore(i, 0, T.size()) {
      ull c = T[i] - 'a';
      ull k_ = k;
      if (apps_S[c].size() == 0) {
        return false;
      }

      ull new_p_j = lower_bound(apps_S[c].begin(), apps_S[c].end(), p) - apps_S[c].begin();
      if (new_p_j >= apps_S[c].size()) {
        n++;
        new_p_j = 0;
      }

      n += (new_p_j + k_ - 1) / apps_S[c].size();

      p = apps_S[c][(new_p_j + k_ - 1) % apps_S[c].size()] + 1;

      if (p >= S.size()) {
        n++;
        p %= S.size();
      }

      if ((n >= N && p > 0) || n > N) {
        return false;
      }

    }

    return true;
  };

  ull l = 0, r = S.size() * N / T.size() + 1;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (!can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  ull ans = l;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  string S, T;
  cin >> N >> S >> T;

  auto ans = solve(N, S, T);
  cout << ans << '\n';

/*   fore(_, 0, 100) {
    ull N = rand() % 5 + 1;
    string S, T;
    fore(__, 0, rand() % 5 + 1) {
      S.push_back('a' + rand() % 5);
    }
    fore(__, 0, rand() % 5 + 1) {
      T.push_back('a' + rand() % 5);
    }
    ull ans = solve(N, S, T);
    ull ans2 = force(N, S, T);

    if (ans != ans2) {
      cerr << "ERROR:\n";
      cerr << N << '\n' << S << '\n' << T << '\n';
      cerr << "ans: " << ans << "\nans2: " << ans2 << endl;
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
