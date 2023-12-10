// https://atcoder.jp/contests/abc332/tasks/abc332_d

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;


ull countToPerm(const vu& as) {
  ull ans = 0;
  fore(i, 0, as.size()) {
    fore(j, i + 1, as.size()) {
      if (as[i] > as[j]) {
        ans++;
      }
    }
  }
  return ans;
}

bool validPerms(const vector<vu>& A, const vector<vu>& B, const vu& rows, const vu& cols) {
  ull H = A.size(), W = A[0].size();

  vector<vu> a_(H);

  fore(i, 0, H) {
    a_[rows[i]] = A[i];
  }

  vector<vu> a(H, vu(W));

  fore(j, 0, W) {
    fore(i, 0, H) {
      a[i][cols[j]] = a_[i][j];
    }
  }

  return a == B;
}

bool elem(const vu& v, ull x) {
  return find(all(v), x) != v.end();
}

optional<ull> solve(const vector<vu>& A, const vector<vu>& B) {
  ull H = A.size(), W = A[0].size();

  ull ans = inf;

  vu rows(H);
  fore(i, 0, H) {
    rows[i] = i;
  }
  do {
    vu cols(W);
    fore(i, 0, W) {
      cols[i] = i;
    }
    do {
      if (validPerms(A, B, rows, cols)) {
        ull this_ans = countToPerm(rows) + countToPerm(cols);
        ans = min(ans, this_ans);
      }
    } while (next_permutation(all(cols)));
  } while (next_permutation(all(rows)));

  if (ans == inf) {
    return {};
  } else {
    return ans;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull H, W;
  cin >> H >> W;
  vector<vu> A(H, vu(W)), B(H, vu(W));
  fore(i, 0, H) {
    fore(j, 0, W) {
      cin >> A[i][j];
    }
  }
  fore(i, 0, H) {
    fore(j, 0, W) {
      cin >> B[i][j];
    }
  }

  auto ans = solve(A, B);

  if (ans.has_value()) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
/*
A:
1 2 4
3 1 1
1 3 2
B:
4 2 1
1 3 1
2 1 3



4 2 1
1 1 3
2 3 1



*/