// https://codeforces.com/contest/1890/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

template <typename T> ostream &operator<<(ostream &out, const vector<T>& vs) {
  ull N = vs.size();
  fore(i, 0, N) {
    out << vs[i];

  }
  return out;
}

#include <ext/rope>
using namespace __gnu_cxx;
//rope<int> s;
// Sequence with O(log(n)) random access, insert, erase at any position
// s.push_back(x);
// s.insert(i,r) // insert rope r at position i
// s.erase(i,k) // erase subsequence [i,i+k)
// s.substr(i,k) // return new rope corresponding to subsequence [i,i+k)
// s[i] // access ith element (cannot modify)
// s.mutable_reference_at(i) // acces ith element (allows modification)
// s.begin() and s.end() are const iterators (use mutable_begin(), mutable_end() to allow modification)


bool is_good(const rope<bool>& s) {
  ull n = s.size();

  fore(i, 0, n/2) {
    if (s[i] == s[n - i - 1]) {
      return false;
    }
  }

  return true;
}


optional<vu> solve1(vector<bool>& s) {
  ull n = s.size();
  if (n % 2 != 0) {
    return {};
  }

  ull count0 = 0, count1 = 0;
  fore(i, 0, n) {
    if (s[i]) {
      count1++;
    } else {
      count0++;
    }
  }

  if (count0 != count1) {
    return {};
  }

  rope<bool> sr;
  fore(i, 0, n) {
    sr.push_back(s[i]);
  }

  vu ans;

  for(ull i = 0; i < sr.size()/2; i++) {
    ull j = sr.size() - i - 1;
    if (sr[i] != sr[j]) {
      continue;
    }

    if (sr[i] == 0) {
      ans.push_back(j + 1);
      sr.insert(j + 1, false);
      sr.insert(j + 2, true);
    } else {
      ans.push_back(i);
      sr.insert(i, false);
      sr.insert(i + 1, true);
    }
  }

  // DBG(s);
  if(!is_good(sr) || ans.size() > 300) {
    DBG(s);

    // Print sr
    fore(i, 0, sr.size()) {
      cerr << sr[i];
    }
    cerr << '\n';
    assert(false);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

/*   fore(i, 0, 1000000) {
    ull n = 1 + rand() % 100;
    vector<bool> s(n);
    fore(j, 0, n) {
      s[j] = rand() % 2;
    }
    auto ans = solve1(s);
  } */

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<bool> s(n);
    fore(j, 0, n) {
      char c;
      cin >> c;
      s[j] = c == '1';
    }

    auto ans = solve1(s);
    if (!ans.has_value()) {
      cout << "-1\n";
    } else {
      cout << ans.value().size() << '\n';
      for(ull a : ans.value()) {
        cout << a << ' ';
      }
      cout << '\n';
    }
  }

  return EXIT_SUCCESS;
}
