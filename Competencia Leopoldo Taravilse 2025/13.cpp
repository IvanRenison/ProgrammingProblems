// https://competencialeopoldotaravilse.com.ar/contest/problems/13

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
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

/*
       0  1
       2  3
 1  5  8  9 12 13 16 17
 6  7 10 11 14 15 18 19
      20 21
      22 23

*/

vector<array<array<ull, 4>, 3>> moves1 = {
  {array<ull, 4>{ 8,  9, 11, 10}, { 2, 12, 21,  7}, { 3, 14, 20,  5}}, // cara frontal
  {array<ull, 4>{16, 17, 19, 18}, {13,  0,  6, 23}, {15,  1,  4, 22}}, // cara trasera
  {array<ull, 4>{ 0,  1,  3,  2}, {17, 13,  9,  5}, {16, 12,  8,  4}}, // cara arriba
  {array<ull, 4>{20, 21, 23, 22}, {10, 14, 18,  6}, {11, 15, 19,  7}}, // cara abajo
  {array<ull, 4>{ 4,  5,  7,  6}, { 0,  8, 20, 19}, { 2, 10, 22, 17}}, // cara izquierda
  {array<ull, 4>{12, 13, 15, 14}, { 9,  1, 18, 21}, {11,  3, 16, 23}}  // cara derecha
};

string apply_move(string s, ull move) {
  for (auto& [a, b, c, d] : moves1[move]) {
    char t = s[a];
    s[a] = s[b];
    s[b] = s[c];
    s[c] = s[d];
    s[d] = t;
  }
  return s;
}

vector<string> moves(string& s) {
  vector<string> ans;
  fore(i, 0, moves1.size()) {
    string t = apply_move(s, i);
    ans.push_back(t);
    t = apply_move(t, i);
    ans.push_back(t);
    t = apply_move(t, i);
    ans.push_back(t);
  }
  return ans;
}


unordered_map<string, ull> dp;

void init() {

  vector<string> solutions = {
    "YYYYBBBBOOOOBBBBRRRRWWWW", "YYYYRRRRBBBBOOOOBBBBWWWW", "YYYYBBBBRRRRBBBBOOOOWWWW", "YYYYOOOOBBBBRRRRBBBBWWWW",
    "BBBBRRRRWWWWOOOOYYYYBBBB", "BBBBYYYYRRRRWWWWOOOOBBBB", "BBBBOOOOYYYYRRRRWWWWBBBB", "BBBBWWWWOOOOYYYYRRRRBBBB",
    "BBBBYYYYOOOOWWWWRRRRBBBB", "BBBBRRRRYYYYOOOOWWWWBBBB", "BBBBWWWWRRRRYYYYOOOOBBBB", "BBBBOOOOWWWWRRRRYYYYBBBB",
    "OOOOWWWWBBBBYYYYBBBBRRRR", "OOOOBBBBWWWWBBBBYYYYRRRR", "OOOOYYYYBBBBWWWWBBBBRRRR", "OOOOBBBBYYYYBBBBWWWWRRRR",
    "BBBBRRRRYYYYOOOOWWWWBBBB", "BBBBWWWWRRRRYYYYOOOOBBBB", "BBBBOOOOWWWWRRRRYYYYBBBB", "BBBBYYYYOOOOWWWWRRRRBBBB",
    "RRRRBBBBYYYYBBBBWWWWOOOO", "RRRRWWWWBBBBYYYYBBBBOOOO", "RRRRBBBBWWWWBBBBYYYYOOOO", "RRRRYYYYBBBBWWWWBBBBOOOO",
    "WWWWBBBBOOOOBBBBRRRRYYYY", "WWWWRRRRBBBBOOOOBBBBYYYY", "WWWWBBBBRRRRBBBBOOOOYYYY", "WWWWOOOOBBBBRRRRBBBBYYYY",
  };

  vector<pair<string, ull>> q;
  for (string& solution : solutions) {
    dp[solution] = 0;
    q.push_back({solution, 0});
  }
  vb vid_d(50, false);
  for (ull i = 0; i < q.size(); i++) {
    auto [s, d] = q[i];

    vector<string> next = moves(s);
    for (auto& t : next) {
      if (dp.find(t) == dp.end()) {
        dp[t] = d + 1;
        q.push_back({t, d + 1});
      }
    }
    if (!vid_d[d]) {
      vid_d[d] = true;
      cerr << i << " completed, size of q: " << q.size() << ", d = " << d << endl;
    }
  }

  cerr << "init completed, size of q: " << q.size() << endl;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  bool first = true;
  while (!cin.eof()) {
    string s;
    cin >> s;
    ull ans = dp[s];
    if (first) {
      first = false;
    } else {
      cout << ",";
    }
    cout << ans;
  }

}
