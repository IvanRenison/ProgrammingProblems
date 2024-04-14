// https://codeforces.com/gym/104901/problem/A
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



char open(char c) {
  if (c == '(' || c == ')') {
    return '(';
  } else  {
    return '[';
  }
}

char close(char c) {
  if (c == '(' || c == ')') {
    return ')';
  } else  {
    return ']';
  }
}

char rev(char c) {
  if (c == '(') {
    return ')';
  } else if (c == '[') {
    return ']';
  } else if (c == ')') {
    return '(';
  } else {
    return '[';
  }
}

bool balanced(const string& S) {
  string stack;
  for (char c : S) {
    if (c == '(' || c == '[') {
      stack.push_back(c);
    } else {
      if (stack.empty() || open(c) != stack.back()) {
        return false;
      }
      stack.pop_back();
    }
  }

  return stack.empty();
}

ll force(const string& S) {
  ll n = S.size();

  ll count = 0;

  fore(x, 0, 1 << n) {
    string t;
    fore(i, 0, n) {
      if (x & (1 << i)) {
        t.push_back(rev(S[i]));
      } else {
        t.push_back(S[i]);
      }
    }

    count += balanced(t);
  }

  return count;
}

bool solve(const string& S) {
  ll n = S.size();

  string stack;
  string t;

  fore(i, 0, n) {
    char c = S[i];
    if (stack.empty() || open(c) != stack.back()) {
      t.push_back(open(c));
      stack.push_back(open(c));
    } else {
      t.push_back(close(c));
      assert(!stack.empty());
      stack.pop_back();
    }
  }

  assert(stack.empty());

  //           par, cor
  vector<pair<bool, bool>> have;
  have.push_back({false, false});
  fore(i, 0, n) {
    char c = t[i];
    if (c == '(') {
      if (!have.back().first) {
        have.push_back({false, false});
      } else {
        return false;
      }
    } else if (c == ')') {
      assert(have.size() > 1);
      have.pop_back();
      have.back().first = true;
    } else if (c == '[') {
      if (!have.back().second) {
        have.push_back({false, false});
      } else {
        return false;
      }
    } else {
      assert(have.size() > 1);
      have.pop_back();
      have.back().second = true;
    }
  }

  assert(have.size() == 1);


  return true;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    string S;
    cin >> S;

    bool ans = solve(S);

    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

/*   fore(_, 0, 1000000) {
    ll n = (rand() % 3 + 1) * 2;

    string poss = "([])";
    string S;
    fore(i, 0, n) {
      S.push_back(poss[rand() % 4]);
    }

    ll f = force(S);
    if (f > 0) {
      bool ansf = f == 1;
      bool anss = solve(S);
      if (ansf != anss) {
        cerr << S << endl;
        cerr << "ansf: " << ansf << " anss: " << anss << endl;
        return 1;
      }
    }

  } */
}

/*
][)[)]([


*/