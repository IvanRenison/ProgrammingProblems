// https://competencialeopoldotaravilse.com.ar/contest/problems/5

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



void interpret(const string& code) {
  ull code_size = code.size();

  // First check that () and [] are balanced, and compute where the other is
  vu others(code_size, -1);
  vector<pair<char, ull>> stack;
  fore(i, 0, code_size) {
    char c = code[i];
    if (c == '(' || c == '[') {
      stack.push_back({c, i});
    } else if (c == ')' || c == ']') {
      if (stack.empty()) {
        cerr << "Unbalanced parentheses" << endl;
        return;
      }
      auto [d, j] = stack.back();
      stack.pop_back();
      if ((c == ')' && d != '(') || (c == ']' && d != '[')) {
        cerr << "Unbalanced parentheses" << endl;
        return;
      }
      others[j] = i;
      others[i] = j;
    }
  }
  if (!stack.empty()) {
    cerr << "Unbalanced parentheses" << endl;
    return;
  }


  vi work, aux;
  for (ull i = 0; i < code_size; i++) {
    char c = code[i];

    if ('0' <= c && c <= '9') {
      work.push_back(c - '0');
    } else if ('a' <= c && c <= 'f') {
      work.push_back(c - 'a' + 10);
    } else if ('A' <= c && c <= 'F') {
      work.push_back(c - 'A' + 10);
    } else if (c == ':') {
      work.push_back(work.back());
    } else if (c == '$') {
      work.pop_back();
    } else if (c == '@') {
      aux.push_back(work.back());
      work.pop_back();
    } else if (c == '#') {
      work.push_back(aux.back());
      aux.pop_back();
    } else if (c == '?') {
      ll n;
      cin >> n;
      work.push_back(n);
    } else if (c == '!') {
      cout << work.back();
      cout.flush();
    } else if (c == '.') {
      cout << ((char)work.back());
      cout.flush();
    } else if (c == '~') {
      ll x = work.back();
      work.pop_back();
      x = ~x;
      work.push_back(x);
    } else if (c == '<') {
      ll x = work.back();
      work.pop_back();
      x = x << 1;
      work.push_back(x);
    } else if (c == '>') {
      ll x = work.back();
      work.pop_back();
      x = x >> 1;
      work.push_back(x);
    } else if (c == '+') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a + b;
      work.push_back(x);
    } else if (c == '-') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a - b;
      work.push_back(x);
    } else if (c == '*') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a * b;
      work.push_back(x);
    } else if (c == '/') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a / b;
      work.push_back(x);
    } else if (c == '%') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a % b;
      work.push_back(x);
    } else if (c == '&') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a & b;
      work.push_back(x);
    } else if (c == '|') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a | b;
      work.push_back(x);
    } else if (c == '^') {
      ll b = work.back();
      work.pop_back();
      ll a = work.back();
      work.pop_back();
      ll x = a ^ b;
      work.push_back(x);
    } else if (c == '=') {
      ll x = work.back();
      work.pop_back();
      x = x > 0 ? 0 : 1;
      work.push_back(x);
    } else if (c == '[') {
      if (work.back() == 0) {
        i = others[i] - 1;
      }
    } else if (c == ']') {
      if (work.back() != 0) {
        i = others[i] - 1;
      }
    } else if (c == '(') {
      if (work.back() == 0) {
        i = others[i] - 1;
      }
    } else if (c == ')') {

    }


  }




}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string file = "5.in";

  // Read entire file to a string
  ifstream t(file);
  stringstream buffer;
  buffer << t.rdbuf();
  string code = buffer.str();


  interpret(code);


}
