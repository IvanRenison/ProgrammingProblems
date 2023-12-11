// https://codeforces.com/gym/100623

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

enum RuleType {allow, deny} __attribute__((packed));

struct Rule {
  RuleType t;
  ull ip;
  ull s;
};


vb solve(const vector<Rule>& rules, const vu& ips) {
  ull m = ips.size();

  set<uu> ip_i;
  fore(i, 0, m) {
    ip_i.insert({ips[i], i});
  }

  vb ans(m, true);

  for (auto [t, ip, s] : rules) {
    auto it = ip_i.lower_bound({ip, 0});
    while (it != ip_i.end() && it->first < ip + (1ull << (32 - s))) {
      if (t == deny) {
        ans[it->second] = false;
      }
      it = ip_i.erase(it);
    }
  }

  return ans;
}

int main(void) {
#ifdef ONLINE_JUDGE
  freopen("access.in", "r", stdin);
  freopen("access.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<Rule> rules(n);
  for (auto& [t, ip, s] : rules) {
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    t = s1[0] == 'a' ? allow : deny;

    istringstream iss(s3);
    char _;
    ip = 0;
    fore(i, 0, 4) {
      ull x;
      iss >> x;
      ip = (ip << 8) | x;
      iss >> _;
    }

    if (!(iss >> s)) {
      s = 32;
    }
  }
/*   fore(i, 0, 100000) {
    rules.push_back({allow, i, 32});
  } */
  ull m;
  cin >> m;
  vu ips(m);
  for (auto& ip : ips) {
    ip = 0;
    fore(i, 0, 4) {
      ull x;
      cin >> x;
      ip = (ip << 8) | x;
      if (i < 3) {
        char _;
        cin >> _;
      }
    }
  }
/*   fore(i, 0, 100000) {
    ips.push_back(i);
  } */


  auto ans = solve(rules, ips);
  for (bool a : ans) {
    cout << (a ? 'A' : 'D');
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
