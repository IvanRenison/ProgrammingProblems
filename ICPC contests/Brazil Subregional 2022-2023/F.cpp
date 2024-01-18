// https://codeforces.com/gym/103960/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

static inline vector<string> parse(void) {
  uint N, C;
  cin >> N >> C;

  vector<string> ws(N);
  for (uint i = 0; i < N; ++i) {
    cin >> ws[i];
  }

  return ws;
}

static inline pair<string, uint> solve(vector<string> ws) {
  uint C = ws[0].size();

  map<string, uint> words;
  for (string w : ws) {
    uint j = 0;
    for (uint i = 0; i < C; i++) {
      if (w[i] == '*') {
        j = i;
        break;
      }
    }

    string prefix = w.substr(0, j);
    string suffix = w.substr(j + 1);

    for (char c = 'a'; c <= 'z'; c++) {
      string word = prefix + c + suffix;
      words[word]++;
    }
  }

  uint max_value = 0;
  string max_word = "";
  for (pair<const string, uint> w : words) {
    if (w.second > max_value) {
      max_value = w.second;
      max_word = w.first;
    }
  }

  return {max_word, max_value};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto ws = parse();
  pair<string, uint> res = solve(ws);

  cout << res.first << " " << res.second << endl;

  return EXIT_SUCCESS;
}
