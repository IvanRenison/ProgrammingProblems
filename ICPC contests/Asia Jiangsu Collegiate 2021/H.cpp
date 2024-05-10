#include <bits/stdc++.h>
#define fst fist
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

string force(const string s) {
  ll n = s.size();

  string ans = s;

  fore(i, 0, n) {
    fore(j, i + 1, n + 1) {
      string this_ans = "";

      fore(k, 0, i) {
        this_ans.push_back(s[k]);
      }
      fore(k, i, j) {
        this_ans.push_back(s[j - k + i - 1]);
      }
      fore(k, j, n) {
        this_ans.push_back(s[k]);
      }

      ans = min(ans, this_ans);
    }
  }

  return ans;
}

struct SuffixArray {
  vi sa, lcp;
  SuffixArray(string& s, ll lim=256) {
    ll n = SZ(s) + 1, k = 0, a, b;
    vi x(ALL(s)+1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y, iota(ALL(sa), 0);
    for (ll j = 0, p = 0; p < n; j = max(1ll, j*2), lim = p) {
      p = j, iota(ALL(y), n - j);
      fore(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(ALL(ws), 0);
      fore(i, 0, n) ws[x[i]]++;
      fore(i, 1, lim) ws[i] += ws[i-1];
      for (ll i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      fore(i, 1, n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    fore(i, 1, n) rank[sa[i]] = i;
    for (ll i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
  }
};

struct H {
  ull x;
  H(ull x = 0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) {
    auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64);
  }
  ull get() const {
    return x + !~x;
  }
  bool operator==(H o) const {
    return get() == o.get();
  }
  bool operator<(H o) const {
    return get() < o.get();
  }
};

static const H C = (ll)1e11 + 3;

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(SZ(str) + 1), pw(ha) {
    pw[0] = 1;
    fore(i, 0, SZ(str)) {
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
    }
  }
  H hashInterval(ll a, ll b) {
    return ha[b] - ha[a] * pw[b - a];
  }
};

ll firstDiff(HashInterval& h0, ll a0, HashInterval& h1, ll a1) {
  ll n0 = h0.ha.size() - 1;
  ll n1 = h1.ha.size() - 1;

  ll n = min(n0, n1);

  ll l = 0, r = n;

  while (l + 1 < r) {
    ll m = (l + 1) / 2;

    if (h0.hashInterval(a0, a0 + m) == h1.hashInterval(a1, a1 + m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return r;
}



ll solvePrefix(string& s) {
  ll n = s.size();

  string t = s;
  reverse(ALL(t));

  HashInterval hs(s), ht(t);

  auto less = [&](ll i, ll j) -> bool {
    assert(i < j);
    // t[n-i:] + s[i:] < t[n-j:] + s[j:]

    // Comparar pedazos en t
    {
      ll ai = n - i, aj = n - j;
      ll d = i;

      if (!(ht.hashInterval(ai, ai + d) == ht.hashInterval(aj, aj + d))) {
        ll l = 0, r = d;
        while (l + 1 < r) {
          ll m = (l + r) / 2;
          if (ht.hashInterval(ai, ai + m) == ht.hashInterval(aj, aj + m)) {
            l = m;
          } else {
            r = m;
          }
        }

        return t[ai + l] < t[aj + l];
      }
    }

    // Comparar prefijo de s con sufijo de t
    {
      ll ai = i, aj = n - j + i;
      ll d = n - aj;
      if (!(hs.hashInterval(ai, ai + d) == ht.hashInterval(aj, aj + d))) {
        ll l = 0, r = d;
        while (l + 1 < r) {
          ll m = (l + r) / 2;
          if (hs.hashInterval(ai, ai + m) == ht.hashInterval(aj, aj + m)) {
            l = m;
          } else {
            r = m;
          }
        }

        return s[ai + l] < t[(aj + l) % n];
      }
    }

    // Comparar pedazos en s
    return false;
    {
      ll ai = j, aj = j;
      ll d = n - j;
      if (hs.hashInterval(ai, ai + d) == hs.hashInterval(aj, aj + d)) {
        return false; // son iguales
      }
      ll l = 0, r = d;
      while (l + 1 < r) {
        ll m = (l + r) / 2;
        if (hs.hashInterval(ai, ai + m) == hs.hashInterval(aj, aj + m)) {
          l = m;
        } else {
          r = m;
        }
      }

      return s[ai + l] < s[aj + l];
    }
  };

  ll ans = 0;

  fore(i, 1, n + 1) {
    // case reversed(s[:i]) + s[i:]
    //       = t[-i:] + s[i:]
    //       = t[n-i:] + s[i:]
    //
    // cmp with t[n-ans:] + s[ans:]

    if (!less(ans, i)) {
      ans = i;
    }
  }

  return ans;
}

string solve(const string& s) {
  ll n = s.size();

  vi last(26, -1);
  fore(i, 0, n) {
    last[s[i] - 'a'] = i;
  }

  char m = *min_element(ALL(s));

  ll real_0 = 0;
  if (s[0] == m) {
    fore(i, 0, n) {
      if (s[i] > m) {
        break;
      } else {
        if (last[m - 'a'] == i) {
          m++;
          while (m <= 'z' && last[m - 'a'] == -1) {
            m++;
          }
          if (m > 'z') {
            return s;
          }
        }
        real_0++;
      }
    }
  }

  if (real_0 == n) {
    return s;
  }

  string s_;
  fore(i, real_0, n) {
    s_.push_back(s[i]);
  }

/*   reverse(ALL(s_));

  SuffixArray sa(s_);

  ll k = 1;
  ll j = sa.sa[k];

  while (k + 1 < n && sa.lcp[k + 1] == s_.size() - j) {
    k++;
    j = sa.sa[k];
  } */

  ll j = solvePrefix(s_);

  string t = s_;
  reverse(ALL(t));

  string ans = "";
  fore(i, 0, real_0) {
    ans.push_back(s[i]);
  }

  // ans += t[n-j:] + s[j:]

  fore(i, n - real_0 - j, n - real_0) {
    ans.push_back(t[i]);
  }
  fore(i, j, n - real_0) {
    ans.push_back(s_[i]);
  }
  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;

    cout << solve(s) << '\n';
  }
/*
  fore(_, 0, 1000) {
    ll n = rand() % 10 + 1;
    string s = "";
    fore(i, 0, n) {
      s.push_back('a' + rand() % 10);
    }

    string ans = solve(s);
    string ansf = force(s);

    if (ans != ansf) {
      cerr << "ERROR\n";
      cerr << s << endl;
      cerr << "ans: " << ans << " ansf: " << ansf << endl;
      return 1;
    }

  } */

}
/*
ERROR
cabigdecaf
ans: acedgibacf
ansf: acbigdecaf


*/
