// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

bool force(string s) {
  ll n = s.size();
  bool ans = false;

  string t = s;
  sort(ALL(t));
  do {
    bool valid = true;
    fore(i, 1, n) {
      string s0 = s.substr(0, i), s1 = s.substr(i);
      string t0 = t.substr(0, i), t1 = t.substr(i);

      sort(ALL(s0)), sort(ALL(s1)), sort(ALL(t0)), sort(ALL(t1));

      if (s0 == t0 && s1 == t1) {
        valid = false;
        break;
      }
    }

    if (valid) {
      ans = true;
      break;
    }

  } while (next_permutation(ALL(t)));

  return ans;
}

bool idea(string s) {
  vi diff(26);
  for (char c : s) {
    diff[c - 'a'] ++;
  }

  bool ans;

  if (s.size() == 1) {
    ans = true;
  } else if (s[0] != s.back()) {
    ans = true;
  } else {
    ll c = s[0] - 'a';

    ll count = 0;
    fore(i, 0, 26) {
      count += diff[i] > 0;
    }

    ans = count >= 3;
  }
  return ans;
}

void test() {
  fore(_, 0, 100000) {
    ll n = rand() % 10 + 1;
    string s;
    fore(i, 0, n) {
      s.push_back('a' + rand() % 5);
    }

    bool ans = idea(s);
    bool ansf = force(s);

    if (ans != ansf) {
      cerr << s << '\n';
      cerr << ans << ' ' << ansf << '\n';
      return;
    }

  }
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);

/*     test();
  return 0; */

  string s;
  cin >> s;

  ll n = s.size();

  vector<vi> sums(n + 1, vi(26));
  fore(i, 0, n) {
    sums[i + 1] = sums[i];
    sums[i + 1][s[i] - 'a']++;
  }

  ll q;
  cin >> q;
  while (q--) {
    ll l, r;
    cin >> l >> r;
    l--;

    vi& vl = sums[l];
    vi& vr = sums[r];

    vi diff(26);
    fore(i, 0, 26) {
      diff[i] = vr[i] - vl[i];
    }

    bool ans;

    if (l + 1 == r) {
      ans = true;
    } else if (s[l] != s[r - 1]) {
      ans = true;
    } else {
      ll count = 0;
      fore(i, 0, 26) {
        count += diff[i] > 0;
      }

      ans = count >= 3;
    }

    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

}