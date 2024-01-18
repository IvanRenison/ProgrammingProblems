// https://codeforces.com/gym/101243

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

ull readHexa(string s) {
  ull ans = 0;
  for(char c : s) {
    ans *= 16;
    if (c >= '0' && c <= '9') {
      ans += c - '0';
    } else {
      ans += c - 'A' + 10;
    }
  }
  return ans;
}

string toExa(ull x) {
  string ans;
  while (x > 0) {
    ull r = x % 16;
    if (r < 10) {
      ans += '0' + r;
    } else {
      ans += 'A' + r - 10;
    }
    x /= 16;
  }
  while (ans.size() < 2) {
    ans += '0';
  }
  reverse(all(ans));
  return ans;
}

enum CommandType {
  MOV_R0_R1,
  MOV_R0_const,
  ADD_R0_R1,
  ADD_R0_const,
  XOR_R0_R1,
  XOR_R0_const,
  PUSH_R0,
  POP_R0,
};

struct Command {
  CommandType type;
  ull R0, R1;
  ull constant;
  ull ndigitsconstant;

  friend istream& operator>>(istream& is, Command& m) {
    char c;
    string s;
    is >> s;
    if (s == "MOV") {
      cin >> c >> m.R0 >> c >> s;
      if (s[0] == 'R') {
        m.type = MOV_R0_R1;
        m.R1 = s[1] - '0';
      } else {
        m.type = MOV_R0_const;
        m.constant = readHexa(s);
        m.ndigitsconstant = s.size();
      }
    } else if (s == "ADD") {
      cin >> c >> m.R0 >> c >> s;
      if (s[0] == 'R') {
        m.type = ADD_R0_R1;
        m.R1 = s[1] - '0';
      } else {
        m.type = ADD_R0_const;
        m.constant = readHexa(s);
        m.ndigitsconstant = s.size();
      }
    } else if (s == "XOR") {
      cin >> c >> m.R0 >> c >> s;
      if (s[0] == 'R') {
        m.type = XOR_R0_R1;
        m.R1 = s[1] - '0';
      } else {
        m.type = XOR_R0_const;
        m.constant = readHexa(s);
        m.ndigitsconstant = s.size();
      }
    } else if (s == "PUSH") {
      cin >> c >> m.R0;
      m.type = PUSH_R0;
    } else if (s == "POP") {
      cin >> c >> m.R0;
      m.type = POP_R0;
    } else {
      assert(false);
    }

    return is;
  }

  friend ostream& operator<<(ostream& os, Command m) {
    if (m.type == MOV_R0_R1) {
      os << "MOV R" << m.R0 << ", R" << m.R1;
    } else if (m.type == MOV_R0_const) {
      os << "MOV R" << m.R0 << ", " << toExa(m.constant);
    } else if (m.type == ADD_R0_R1) {
      os << "ADD R" << m.R0 << ", R" << m.R1;
    } else if (m.type == ADD_R0_const) {
      os << "ADD R" << m.R0 << ", " << toExa(m.constant);
    } else if (m.type == XOR_R0_R1) {
      os << "XOR R" << m.R0 << ", R" << m.R1;
    } else if (m.type == XOR_R0_const) {
      os << "XOR R" << m.R0 << ", " << toExa(m.constant);
    } else if (m.type == PUSH_R0) {
      os << "PUSH R" << m.R0;
    } else if (m.type == POP_R0) {
      os << "POP R" << m.R0;
    } else {
      assert(false);
    }

    return os;
  }
};

vector<Command> solve(vector<Command> commands) {
  vector<Command> ans;

  for (Command cmd : commands) {
    ans.push_back(cmd);

    while (true) {
      ull k = ans.size();

      if (k < 2) {
        break;
      }

      Command last0 = ans[k - 1];
      Command last1 = ans[k - 2];

      // PUSH Ry
      // POP Rx
      if (last1.type == PUSH_R0 && last0.type == POP_R0) {
        ans.pop_back(), ans.pop_back();
        ans.push_back(Command{MOV_R0_R1, last0.R0, last1.R0, 0, 0});
        continue;
      }
      // XOR Rx, Rx
      // ADD Rx, const
      if (last1.type == XOR_R0_R1 && last0.type == ADD_R0_const &&
          last1.R0 == last1.R1 && last1.R0 == last0.R0) {
        ans.pop_back(), ans.pop_back();
        ans.push_back(Command{MOV_R0_const, last1.R0, 0, last0.constant, last0.ndigitsconstant});
        continue;
      }

      if (k < 4) {
        break;
      }

      Command last2 = ans[k - 3];
      Command last3 = ans[k - 4];

      // PUSH Rz
      // MOV Rz, Ry
      // ADD Rx, Rz
      // POP Rz
      if (last3.type == PUSH_R0 && last2.type == MOV_R0_R1 && last1.type == ADD_R0_R1 && last0.type == POP_R0
          && last3.R0 == last2.R0 && last3.R0 == last1.R1 && last3.R0 == last0.R0 && last3.R0 != last1.R0) {
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{ADD_R0_R1, last1.R0, last2.R1, 0, 0});
        continue;
      }

      if (k < 5) {
        break;
      }

      Command last4 = ans[k - 5];

      // PUSH Rz
      // MOV Rz, const
      // ADD Rz, Rx
      // MOV Rx, Rz
      // POP Rz
      if (last4.type == PUSH_R0 && last3.type == MOV_R0_const && last2.type == ADD_R0_R1 && last1.type == MOV_R0_R1 && last0.type == POP_R0
          && last4.R0 == last3.R0 && last4.R0 == last2.R0 && last4.R0 == last1.R1 && last4.R0 == last0.R0
          && last2.R1 == last1.R0 && last4.R0 != last2.R1) {
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{ADD_R0_const, last2.R1, 0, last3.constant, last3.ndigitsconstant});
        continue;
      }

      // PUSH Rz
      // XOR Rz, const
      // XOR Rx, Rz
      // POP Rz
      // XOR Rx, Rz
      if (last4.type == PUSH_R0 && last3.type == XOR_R0_const && last2.type == XOR_R0_R1 && last1.type == POP_R0 && last0.type == XOR_R0_R1
          && last4.R0 == last3.R0 && last4.R0 == last2.R1 && last4.R0 == last1.R0 && last4.R0 == last0.R1
          && last2.R0 == last0.R0 && last4.R0 != last2.R0) {
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{XOR_R0_const, last2.R0, 0, last3.constant, last3.ndigitsconstant});
        continue;
      }

      // MOV Rx, Rz
      // POP Rz
      // XOR Rx, Rz
      // XOR Rz, Rx
      // XOR Rx, Rz
      if (last4.type == MOV_R0_R1 && last3.type == POP_R0 && last2.type == XOR_R0_R1 && last1.type == XOR_R0_R1 && last0.type == XOR_R0_R1
          && last4.R0 == last2.R0 && last4.R0 == last1.R1 && last4.R0 == last0.R0
          && last4.R1 == last3.R0 && last3.R0 == last2.R1 && last3.R0 == last1.R0 && last3.R0 == last0.R1 && last4.R0 != last3.R0) {
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{POP_R0, last4.R0, 0, 0, 0});
        continue;
      }

      if (k < 7) {
        break;
      }

      Command last5 = ans[k - 6];
      Command last6 = ans[k - 7];

      // PUSH Rz
      // MOV Rz, Ry
      // XOR Rz, const
      // XOR Rx, Rz
      // MOV Rz, const
      // XOR Rx, Rz
      // POP Rz
      if (last6.type == PUSH_R0 && last5.type == MOV_R0_R1 && last4.type == XOR_R0_const && last3.type == XOR_R0_R1 && last2.type == MOV_R0_const && last1.type == XOR_R0_R1 && last0.type == POP_R0
          && last6.R0 == last5.R0 && last6.R0 == last4.R0 && last6.R0 == last3.R1 && last6.R0 == last2.R0 && last6.R0 == last1.R1 && last6.R0 == last0.R0
          && last3.R0 == last1.R0
          && last4.constant == last2.constant
          && last6.R0 != last3.R0) {
        assert(last4.ndigitsconstant == last2.ndigitsconstant);
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{XOR_R0_R1, last3.R0, last5.R1, 0, 0});
        continue;
      }

      // PUSH Rx
      // MOV Rx, Rz
      // POP Rz
      // PUSH Rz
      // XOR Rx, Rz
      // XOR Rz, Rx
      // XOR Rx, Rz
      if (last6.type == PUSH_R0 && last5.type == MOV_R0_R1 && last4.type == POP_R0 && last3.type == PUSH_R0 && last2.type == XOR_R0_R1 && last1.type == XOR_R0_R1 && last0.type == XOR_R0_R1
          && last6.R0 == last5.R0 && last6.R0 == last2.R0 && last6.R0 == last1.R1 && last6.R0 == last0.R0
          && last5.R1 == last4.R0 && last5.R1 == last3.R0 && last5.R1 == last2.R1 && last5.R1 == last1.R0 && last5.R1 == last0.R1
          && last6.R0 != last5.R1) {
        ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back(), ans.pop_back();
        ans.push_back(Command{PUSH_R0, last6.R0, 0, 0, 0});
        continue;
      }

      break;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ull n;
  cin >> n;
  vector<Command> cmds(n);
  for (auto& cmd : cmds) {
    cin >> cmd;
  }

  auto ans = solve(cmds);
  cout << ans.size() << '\n';
  for (auto cmd : ans) {
    cout << cmd << '\n';
  }

  return EXIT_SUCCESS;
}
