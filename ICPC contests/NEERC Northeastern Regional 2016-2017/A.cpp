// https://codeforces.com/gym/101190
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

bool isLower(char c) {
  return 'a' <= c && c <= 'z';
}

bool isUpper(char c) {
  return 'A' <= c && c <= 'Z';
}

bool isLetter(char c) {
  return isLower(c) || isUpper(c);
}

bool isCapWord(string& s) {
  ll n = s.size();
  if (n < 2) {
    return false;
  }
  if (!isUpper(s[0])) {
    return false;
  }
  fore(i, 1, n) {
    if (!isLower(s[i])) {
      return false;
    }
  }
  return true;
}

string solve(string& s) {
  ll n = s.size();

  bool in_sep = false;
  vector<string> words_seps = {{}};
  for (char c : s) {
    if (!in_sep) {
      if (isLetter(c)) {
        words_seps.back().push_back(c);
      } else {
        words_seps.push_back({c});
        in_sep = true;
      }
    } else {
      if (isLetter(c)) {
        words_seps.push_back({c});
        in_sep = false;
      } else {
        words_seps.back().push_back(c);
      }
    }
  }
   ll m = words_seps.size();

  string ans = "";

  string sec_abr = "";
  string sec_compete = "";
  fore(i, 0, m) {
    if (i % 2 == 0) { // Word
      if (isCapWord(words_seps[i])) {
        sec_abr += words_seps[i][0];
        sec_compete += words_seps[i] + " ";
      } else {
        if (sec_abr.size() >= 2) {
          sec_compete.pop_back();
          ans += sec_abr + " (" + sec_compete + ") " + words_seps[i];
        } else if (sec_abr.size() == 1) {
          ans += sec_compete + words_seps[i];
        } else {
          ans += words_seps[i];
        }
        sec_abr = "";
        sec_compete = "";
      }
    } else { // Sep
      if (words_seps[i] != " ") {
        if (sec_abr.size() >= 2) {
          sec_compete.pop_back();
          ans += sec_abr + " (" + sec_compete + ")" + words_seps[i];
        } else if (sec_abr.size() == 1) {
          sec_compete.pop_back();
          ans += sec_compete + words_seps[i];
        } else {
          ans += words_seps[i];
        }
        sec_abr = "";
        sec_compete = "";
      } else {
        if (sec_abr.size() == 0) {
          ans += " ";
        }
      }
    }
  }

  if (sec_abr.size() >= 2) {
    sec_compete.pop_back();
    ans += sec_abr + " (" + sec_compete + ")";
  } else if (sec_abr.size() == 1) {
    sec_compete.pop_back();
    ans += sec_compete;
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("abbreviation.in", "r", stdin);
  freopen("abbreviation.out", "w", stdout);
#endif

  while (!cin.eof()) {
    string s;
    getline(cin, s);
    if (!s.empty()) {
      cout << solve(s) << '\n';
    }
  }

}
