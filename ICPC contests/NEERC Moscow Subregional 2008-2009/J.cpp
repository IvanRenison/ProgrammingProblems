// https://codeforces.com/gym/100861

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const set<string> RomanNumbers = {
  "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII",
  "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV",
  "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI",
  "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII",
  "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
  "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII",
  "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV",
  "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX"
};

bool isValidRomanNumber(string s) {
  return RomanNumbers.count(s);
}

bool isRomanChar(char c) {
  return c == 'I' || c == 'V' || c == 'X' || c == 'L';
}

ull CharVal(char c) {
  switch (c) {
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
  }
}


ull readRoman(string s) {
  ull n = s.size();
  ll ans = 0;

  fore(i, 0, n - 1) {
    char c1 = s[i], c2 = s[i + 1];
    ll v1 = CharVal(c1), v2 = CharVal(c2);
    if (v1 < v2) {
      ans -= v1;
    } else {
      ans += v1;
    }
  }
  ans += CharVal(s[n - 1]);

  return ans;
}

bool validExpresion(string s) {
  ull n = s.size();

  ll part1 = 0;

  ull p = 0;

  if (p >= n || !isRomanChar(s[p])) {
    return false;
  }

  while (p < n && s[p] != '=') {
    ll sign = 1;
    if (s[p] == '-') {
      sign = -1;
      p++;
    } else if (s[p] == '+') {
      p++;
    }

    if (p >= n || !isRomanChar(s[p])) {
      return false;
    }

    string t;
    while (p < n && isRomanChar(s[p])) {
      t += s[p];
      p++;
      while (p < n && s[p] == ' ') {
        p++;
      }
    }

    if (!isValidRomanNumber(t)) {
      return false;
    }

    part1 += sign * (ll)readRoman(t);
  }

  p++;

  if (p >= n || !isRomanChar(s[p])) {
    return false;
  }

  ll part2 = 0;
  while (p < n) {
    if (s[p] == '=') {
      return false;
    }
    ll sign = 1;
    if (s[p] == '-') {
      sign = -1;
      p++;
    } else if (s[p] == '+') {
      p++;
    }

    if (p >= n || !isRomanChar(s[p])) {
      return false;
    }

    string t;
    while (p < n && isRomanChar(s[p])) {
      t += s[p];
      p++;
    }

    if (!isValidRomanNumber(t)) {
      return false;
    }

    part2 += sign * (ll)readRoman(t);
  }

  return part1 == part2;
}

const vector<pair<char, char>> mods = {
  {'I', ' '},
  {'-', ' '},
  {'L', 'I'},
  {'+', 'I'},
  {'+', '-'},
  {'=', '-'}
};

const vector<pair<char, char>> selfMods = {
  {'I', '-'},
  {'L', '+'},
  {'=', '+'},
  {'V', 'X'},
  {'-', 'I'},
  {'+', 'L'},
  {'+', '='},
  {'X', 'V'}
};


set<string> solve(string s) {
  ull n = s.size();

  set<string> ans;

  fore(i, 0, n) {
    char ci = s[i];

    // Try self modification
    for (auto [c1, ci_] : selfMods) {
      if (ci == c1) {
        string s_ = s;
        s_[i] = ci_;
        if (validExpresion(s_)) {
          ans.insert(s_);
        }
      }
    }

    // For each way to remove a char
    for (auto [c1, ci_] : mods) {
      if (ci == c1) {
        fore(j, 0, n) if (i != j) {
          // Try modifying a character
          char cj = s[j];
          for (auto [cj_, c2] : mods) {
            if (cj == c2) {
              string s_ = s;
              s_[i] = ci_;
              s_[j] = cj_;
              if (ci_ == ' ') {
                s_.erase(s_.begin() + i);
              }
              if (validExpresion(s_)) {
                ans.insert(s_);
              }
            }
          }
        }
        fore(j, 0, n + 1) {
          // Try adding a character
          for (auto [c_, c2] : mods) {
            if (c2 == ' ') {
              string s_ = s;
              s_[i] = ci_;
              s_.insert(s_.begin() + j, c_);
              if (ci_ == ' ') {
                s_.erase(s_.begin() + i + (j <= i ? 1 : 0));
              }
              if (validExpresion(s_)) {
                ans.insert(s_);
              }
            }
          }
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;

  auto ans = solve(s);
  for (string t : ans) {
    cout << t << '\n';
  }

  return EXIT_SUCCESS;
}
