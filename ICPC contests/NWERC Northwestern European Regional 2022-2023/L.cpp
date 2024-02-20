// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define SZ(x) ll(x.size())
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ll inf = 1ll << 48;

/** Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity O(VE\log U)$ where U = \max |\text{cap}|$.
 * O(\min(E^{1/2}, V^{2/3})E)$ if U = 1$; O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
struct Dinic {
  struct Edge {
    ll to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {
    //cerr << n << endl;
  }
  void addEdge(ll a, ll b, ll c, ll rcap = 0) {
    //cerr << a << ' ' << b << ' ' << c << ' ' << rcap << endl;
    adj[a].push_back({b, SZ(adj[b]), c, c});
    adj[b].push_back({a, SZ(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(ll v, ll t, ll f) {
    if (v == t || !f) return f;
    for (ll& i = ptr[v]; i < SZ(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(ll s, ll t) {
    ll flow = 0; q[0] = s;
    fore(L,0,31) do { // 'll L=30' maybe faster for random data
      lvl = ptr = vi(SZ(q));
      ll qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        ll v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(ll a) { return lvl[a] != 0; }
};

string solve(const vector<pair<string, string>>& sts) {
  ll g = sts.size() + 1, l = sts[0].first.size();

  string ans;
  fore(_, 0, l) {
    ans.push_back('*');
  }

  vector<vector<bool>> used(l, vector<bool>(26, false));
  vector<bool> ne_used(26, false);
  vi uses(26, 0);
  fore(i, 0, g - 1) {
    const auto& [s, t] = sts[i];
    vi this_uses(26, 0);
    fore(j, 0, l) {
      char c = s[j], C = t[j];
      if (C != 'B') {
        this_uses[c - 'a']++;
      } else {
        ne_used[c - 'a'] = true;
      }
      if (C == 'G') {
        ans[j] = c;
      }
      used[j][c - 'a'] = true;
    }
    fore(c, 0, 26) {
      uses[c] = max(uses[c], this_uses[c]);
    }
  }

  vi ans_uses(26);
  fore(j, 0, l) {
    if (ans[j] != '*') {
      ans_uses[ans[j] - 'a']++;
    }
  }

  fore(c, 0, 26) {
    uses[c] = max(uses[c], ans_uses[c]);
  }

  ll sum_uses = 0;
  fore(c, 0, 26) {
    sum_uses += uses[c];
  }

  ll n = 1 + 1 + 26 + l + 1;

  Dinic dinic(n);

  dinic.addEdge(0, 1, l - sum_uses);
  fore(c, 0, 26) {
    if (uses[c] > 0) {
      dinic.addEdge(0, 2 + c, uses[c]);
    }

    if (!ne_used[c]) {
      dinic.addEdge(1, 2 + c, inf);
    }
  }

  fore(j, 0, l) {
    if (ans[j] != '*') {
      dinic.addEdge(2 + (ans[j] - 'a'), 2 + 26 + j, 1);
    } else {
      fore(c, 0, 26) {
        if (!used[j][c]) {
          dinic.addEdge(2 + c, 2 + 26 + j, 1);
        }
      }
    }

    dinic.addEdge(2 + 26 + j, n - 1, 1);
  }

  ll flow = dinic.calc(0, n - 1);
  if(flow != l) {
    return ans;
  }

  fore(c, 0, 26) {
    for (auto& e : dinic.adj[2 + c]) {
      if (e.flow() == 1) {
        ll j = e.to - 2 - 26;
        ans[j] = c + 'a';
      }
    }
  }

  return ans;
}

string check_word(const string& word, const string& ans) {
  ll n = word.size();

  string check;

  fore(_, 0, n) {
    check += "&";
  }

  vi ans_counts(26), word_counts(26);

  fore(j, 0, n) {
    if (word[j] == ans[j]) {
      check[j] = 'G';
    } else {
      word_counts[word[j] - 'a']++;
      ans_counts[ans[j] - 'a']++;
    }
  }

  fore(j, 0, n) {
    if (check[j] != 'G') {
      if (word_counts[word[j] - 'a'] > 0 && ans_counts[word[j] - 'a'] > 0) {
        check[j] = 'Y';
        word_counts[word[j] - 'a']--;
        ans_counts[word[j] - 'a']--;
      } else {
        check[j] = 'B';
      }
    }
  }

  return check;
}

pair<vector<pair<string, string>>, string> testGen(ll g, ll l) {
  vector<pair<string, string>> sts(g - 1);

  fore(i, 0, g - 1) {
    fore(j, 0, l) {
      sts[i].first.push_back('a' + rand() % 26);
    }
  }

  string word;
  fore(j, 0, l) {
    word.push_back('a' + rand() % 26);
  }

  fore(i, 0, g - 1) {
    auto& [s, t] = sts[i];
    t = check_word(s, word);
  }

  return {sts, word};
}



bool check(const vector<pair<string, string>>& sts, const string& ans) {
  ll g = sts.size() + 1, l = sts[0].first.size();

  fore(j, 0, l) {
    if (ans[j] < 'a' || ans[j] > 'z') {
      return false;
    }
  }

  vi word_counts(26);
  for (char c : ans) {
    word_counts[c - 'a']++;
  }

  fore(i, 0, g - 1) {
    const auto& [s, t] = sts[i];
    if (t != check_word(s, ans)) {
      return false;
    }
  }

  return true;
}

int main(){FIN;

  ll g, l;
  cin >> g >> l;
  vector<pair<string, string>> sts(g - 1);
  for (auto& [s, t] : sts) {
    cin >> s >> t;
  }

  string ans = solve(sts);
  cout << ans << '\n';

  assert(check(sts, ans));

/*   fore(_, 0, 1000) {
    ll g = rand() % 2 + 2, l = rand() % 2 + 1;

    auto [sts, word] = testGen(g, l);
    string ans = solve(sts);

    bool b = check(sts, ans);
    if (!b) {
      cerr << "ERROR: " << _ << '\n';
      cerr << g << ' ' << l << '\n';
      for (auto& [s, t] : sts) {
        cerr << s << ' ' << t << '\n';
      }
      cerr << "ans: " << ans << '\n';
      cerr << "word: " << word << '\n';
      return EXIT_FAILURE;
    }
  } */

  return 0;
}
