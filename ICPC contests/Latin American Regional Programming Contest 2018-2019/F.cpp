// https://matcomgrader.com/problem/9547/fantastic-beasts/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

ull lcm(ull a, ull b) {
  return a * b / __gcd(a, b);
}

pair<bool, uu> convine(ull t0, ull q0, ull t1, ull q1) {
  if (t0 > t1) {
    swap(t0, t1), swap(q0, q1);
  }

  if ((t1 - t0) % q0 == 0) {
    return make_pair(true, make_pair(t1, lcm(q0, q1)));
  }

  if (q0 == q1) {
    return make_pair(false, make_pair(0, 0));
  } else if (q0 < q1) {
    vector<bool> vis(q0, false);
    while ((t1 - t0) % q0 != 0) {
      if (vis[(t1 - t0) % q0]) {
        return make_pair(false, make_pair(0, 0));
      }
      vis[(t1 - t0) % q0] = true;
      t1 += q1;
    }
    return make_pair(true, make_pair(t1, lcm(q0, q1)));
  } else {
    while (t0 < t1) {
      t0 += q0;
    }
    vector<bool> vis(q1, false);
    while ((t0 - t1) % q1 != 0) {
      if (vis[(t0 - t1) % q1]) {
        return make_pair(false, make_pair(0, 0));
      }
      vis[(t0 - t1) % q1] = true;
      t0 += q0;
    }
    return make_pair(true, make_pair(t0, lcm(q0, q1)));
  }
}


pair<bool, uu> solve(vector<vu> Pss) {
  ull B = Pss.size(), Z = Pss[0].size() - 1;

  vector<vector<vu>> reaches(B, vector<vu>(Z));

  fore(b, 0, B) {
    for(ull t = 0, z = Pss[b][0]; reaches[b][z].size() < 2; t++) {
      reaches[b][z].push_back(t);
      z = Pss[b][z + 1];
    }
  }

  ull ans_z = -1, ans_t = 1ull << 60;

  fore(z, 0, Z) {
    ull t = 0, q = 1;
    bool valid = true;
    bool only_once = false;

    fore(b, 0, B) {
      if (reaches[b][z].empty()) {
        valid = false;
        break;
      } else if (reaches[b][z].size() == 1) {
        ull this_t = reaches[b][z][0];
        if (only_once) {
          if (this_t != t) {
            valid = false;
            break;
          }
        } else {
          if (this_t < t || (this_t - t) % q != 0) {
            valid = false;
            break;
          } else {
            t = this_t;
            only_once = true;
          }
        }
      } else {
        ull this_t = reaches[b][z][0];
        ull this_q = reaches[b][z][1] - this_t;
        if (only_once) {
          if (t < this_t || (t - this_t) % this_q != 0) {
            valid = false;
            break;
          }
        } else {
          auto new_tq = convine(t, q, this_t, this_q);
          if (!new_tq.first) {
            valid = false;
            break;
          } else {
            t = new_tq.second.first;
            q = new_tq.second.second;
          }
        }
      }
    }

    if (valid) {
      if (t < ans_t) {
        ans_z = z;
        ans_t = t;
      }
    }
  }

  if (ans_z == -1) {
    return make_pair(false, make_pair(0, 0));
  } else {
    return make_pair(true, make_pair(ans_z, ans_t));
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull B, Z;
  cin >> B >> Z;
  vector<vu> Pss(B, vu(Z + 1));
  for (vu& Ps : Pss) {
    for (ull& P : Ps) {
      cin >> P;
      P--;
    }
  }

  auto ans = solve(Pss);
  if (!ans.first) {
    cout << "*\n";
  } else {
    cout << ans.second.first + 1 << ' ' << ans.second.second << '\n';
  }

  return EXIT_SUCCESS;
}
