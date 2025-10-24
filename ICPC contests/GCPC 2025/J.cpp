#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;




string encode(string s) {
  ll n = s.size();

  ll count0 = 0;
  for (char c : s) {
    count0 += c == '0';
  }

  if (count0 == 0 || count0 == n) {
    return s;
  }

  char first = s[0];
  for (ll i = 0; s[i] == first; i++) {
    s[i] = '2';
  }

  return s;
}

string decode(string s) {
  ll n = s.size();

  ll first2 = -1;
  if (s.back() == '2') {
    for (ll i = n; i--; ) {
      if (s[i] != '2') {
        first2 = i + 1;
        break;
      }
    }
  } else {
    fore(i, 0, n) {
      if (s[i] == '2') {
        first2 = i;
        break;
      }
    }
  }

  if (first2 == -1) {
    return s;
  }

  char rep2 = '#';
  fore(i, 1, n) {
    char c = s[(first2 + i) % n];
    if (c != '2') {
      rep2 = c == '0' ? '1' : '0';
      break;
    }
  }

  assert(rep2 != '#');

  string ans;
  fore(i, 0, n) {
    char c = s[(first2 + i) % n];
    if (c == '2') {
      ans += rep2;
    } else {
      ans += c;
    }
  }

  return ans;
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  string e, s;
  ll n;
  cin >> e >> n >> s;

  if (e[0] == 'E') {
    cout << encode(s) << '\n';
  } else {
    cout << decode(s) << '\n';
  }
#else
  fore(n, 1, 8) {
    fore(x, 0, 1 << n) {
      string s;
      ll y = x;
      fore(i, 0, n) {
        s += '0' + (y % 2);
        y /= 2;
      }

      string code = encode(s);

      fore(i, 0, n) {
        string code2;
        fore(j, 0, n) {
          code2 += code[(i + j) % n];
        }
        string dec = decode(code2);
        if (s.size() != code.size() || code.size() != dec.size() || s != dec) {
          cout << s << ' ' << code << ' ' << code2 << ' ' << dec << '\n';
          return 1;
        }
      }
    }
  }
#endif
}
