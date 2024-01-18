// https://codeforces.com/gym/104736/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool isChar(char c) {
  return 'a' <= c && c <= 'z';
}

bool isSymb(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

/*
Compatible:
aa
a+
+a
a)
(a
((
+(
)+
))

Incompatible:
a(
++
+)
)a
)(
(+
()
*/
bool areCompatible(char a, char b) {
  return
    (isChar(a) && b != '(')
    || (isChar(b) && a != ')')
    || (isSymb(a) && b == '(')
    || (isSymb(b) && a == ')')
    || (a == '(' && b == '(')
    || (a == ')' && b == ')')
  ;
}

// solve if there are no incompatible chars one after the other
ull solveCompatible(const string& S) {
  ull ans = 0;

  vu validStarts = {0};
  for (char c : S) {
    if (c == '(') {
      validStarts.push_back(0);
    } else {
      if (c == ')') {
        if (validStarts.size() == 1) {
          validStarts[0] = 0;
        } else {
          validStarts.pop_back();
          validStarts.back()++;
        }
      } else if (isChar(c)) {
        validStarts.back()++;
      }

      if (!isSymb(c)) {
        ans += validStarts.back();
      }
    }
  }

  return ans;
}

ull solve(const string& S) {
  ull N = S.size();

  ull i = 0;
  ull ans = 0;
  fore(j, 1, N) {
    if (!areCompatible(S[j - 1], S[j])) {
      ans += solveCompatible(S.substr(i, j - i));
      i = j;
    }
  }
  ans += solveCompatible(S.substr(i, N - i));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string S;
  cin >> S;

  auto ans = solve(S);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
