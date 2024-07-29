// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

enum AbilityType {
  Defence, DefenceOn, DefenceNear, DefenceVersus,
  Attack, AttackOn, AttackNear, AttackVersus,
  Points, PointsOn, PointsForConquest
};

struct Ability {
  AbilityType ty;
  ull k;
  ull target; // Race or Terrain type, depending on AbilityType
};

struct Area {
  ull terrain;
  bool border;
  optional<uu> race_amount;
  vu adj;
};

ull solve(ull t, const vector<vector<Ability>>& abilities, const vector<Area>& areas, ull n, ull my_race) {
  ull r = abilities.size(), a = areas.size();

  vu defence(r, 0), attack(r, 0);
  vector<vu> defence_on(r, vu(t, 0)), defence_near(r, vu(t, 0)), defence_versus(r, vu(r, 0));
  vector<vu> attack_on(r, vu(t, 0)), attack_near(r, vu(t, 0)), attack_versus(r, vu(r, 0));
  ull points = 1, points_for_conquest = 0;
  vu points_on(t, 0);

  fore(i, 0, r) {
    for (auto [ty, k, target] : abilities[i]) {
      if (ty == Defence) {
        defence[i] += k;
      } else if (ty == DefenceOn) {
        defence_on[i][target] += k;
      } else if (ty == DefenceNear) {
        defence_near[i][target] += k;
      } else if (ty == DefenceVersus) {
        defence_versus[i][target] += k;
      } else if (ty == Attack) {
        attack[i] += k;
      } else if (ty == AttackOn) {
        attack_on[i][target] += k;
      } else if (ty == AttackNear) {
        attack_near[i][target] += k;
      } else if (ty == AttackVersus) {
        attack_versus[i][target] += k;
      }
      if (i == my_race) {
        if (ty == Points) {
          points += k;
        } else if (ty == PointsOn) {
          points_on[target] += k;
        } else if (ty == PointsForConquest) {
          points_for_conquest += k;
        }
      }
    }
  }

  ull empty_areas = 0;
  fore(i, 0, a) {
    if (!areas[i].race_amount.has_value()) {
      empty_areas |= 1ull << i;
    }
  }

  vu conquest_units(a, 0);
  fore(i, 0, a) {
    ll b = 0, c = 0;
    b -= attack[my_race];
    b -= attack_on[my_race][areas[i].terrain];

    vb attack_near_used(t, false);
    for (ull j : areas[i].adj) {
      if (!attack_near_used[areas[j].terrain]) {
        b -= attack_near[my_race][areas[j].terrain];
        attack_near_used[areas[j].terrain] = true;
      }
    }
    if (!(empty_areas & (1ull << i))) {
      ull race = areas[i].race_amount->first;

      b += defence[race];
      b += defence_on[race][areas[i].terrain];
      for (ull j : areas[i].adj) {
        b += defence_near[race][areas[j].terrain];
      }
      b += defence_versus[race][my_race];

      b -= attack_versus[my_race][race];

      c = areas[i].race_amount->second;
    }
    ull val = max(1ll, 2ll + c + b);
    conquest_units[i] = val;
  }

  auto total_points_of = [&](ull x) -> ull {
    ull ans = 0;
    fore(i, 0, a) {
      if (x & (1ull << i)) {
        ans += points;
        ans += points_on[areas[i].terrain];
        if (!(empty_areas & (1ull << i))) {
          ans += points_for_conquest;
        }
      }
    }
    return ans;
  };

  unordered_map<ull, ull> dp;

  function<ull(ull, ull, ull)> f = [&](ull x, ull y, ull n) -> ull {
    // x: Conquered areas, y = areas for conquering

    if (x != 0 && dp.count(x)) {
      return dp[x];
    }

    ull ans = 0;
    if (n == 0 || x == (1ull << a) - 1) {
      ans = total_points_of(x);
    } else {
      bool rec = false;
      fore(i, 0, a) {
        if ((y & (1ull << i)) && conquest_units[i] <= n) {
          rec = true;
          ull new_x = x | (1ull << i);
          ull new_y = y & ~(1ull << i);
          for (ull j : areas[i].adj) {
            if (!(x & (1ull << j))) {
              new_y |= 1ull << j;
            }
          }
          ull new_n = n - conquest_units[i];

          ull this_ans = f(new_x, new_y, new_n);
          ans = max(ans, this_ans);
        }
      }

      if (!rec) {
        ans = total_points_of(x);
      }
    }

    dp[x] = ans;
    return ans;
  };

  ull ans = 0;

  fore(i, 0, a) {
    if (areas[i].border) {
      ull this_ans = f(0, 1ull << i, n);
      ans = max(ans, this_ans);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("jumbo.in", "r", stdin);
  freopen("jumbo.out", "w", stdout);
#endif

  ull t, r, a, n;
  cin >> t >> r >> a >> n;

  map<string, ull> terrains_ids;
  fore(i, 0, t) {
    string s;
    cin >> s;
    terrains_ids[s] = i;
  }
  map<string, ull> races_ids;
  vector<vector<string>> abilities_s(r);
  fore(i, 0, r) {
    string name;
    cin >> name;
    races_ids[name] = i;
    ull v;
    cin >> v;
    abilities_s[i] = vector<string>(v);
    getline(cin, name);
    for(string& s : abilities_s[i]) {
      getline(cin, s);
    }
  }
  vector<vector<Ability>> abilities(r);
  fore(i, 0, r) {
    ull v = abilities_s[i].size();
    abilities[i] = vector<Ability>(v);
    fore(j, 0, v) {
      string& s = abilities_s[i][j];
      istringstream iss(s);
      char c;
      iss >> c;
      assert(c == '+');
      ull k;
      iss >> k;
      string type;
      iss >> type;
      if (type == "defence") {
        if (iss.eof()) {
          abilities[i][j] = {Defence, k, 0};
        } else {
          string sub_type, target_s;
          iss >> sub_type >> target_s;
          AbilityType ty =
              sub_type == "on" ? DefenceOn
            : sub_type == "near" ? DefenceNear
            : DefenceVersus;
          ull target = ty == DefenceVersus ? races_ids[target_s] : terrains_ids[target_s];
          abilities[i][j] = {ty, k, target};
        }
      } else if (type == "attack") {
        if (iss.eof()) {
          abilities[i][j] = {Attack, k, 0};
        } else {
          string sub_type, target_s;
          iss >> sub_type >> target_s;
          AbilityType ty =
              sub_type == "on" ? AttackOn
            : sub_type == "near" ? AttackNear
            : AttackVersus;
          ull target = ty == AttackVersus ? races_ids[target_s] : terrains_ids[target_s];
          abilities[i][j] = {ty, k, target};
        }
      } else {
        assert(type == "points");
        if (iss.eof()) {
          abilities[i][j] = {Points, k, 0};
        } else {
          string sub_type;
          iss >> sub_type;
          if (sub_type == "on") {
            string target_s;
            iss >> target_s;
            abilities[i][j] = {PointsOn, k, terrains_ids[target_s]};
          } else {
            assert(sub_type == "for");
            abilities[i][j] = {PointsForConquest, k, 0};
          }
        }
      }
    }
  }
  vector<Area> areas(a);
  fore(i, 0, a) {
    string terrain_s;
    cin >> terrain_s;
    ull terrain = terrains_ids[terrain_s];
    string border_s;
    cin >> border_s;
    bool border = border_s == "border";
    string race_s;
    cin >> race_s;
    optional<uu> race_amount;
    if (race_s != "empty") {
      ull race = races_ids[race_s];
      ull amount;
      cin >> amount;
      race_amount = {{race, amount}};
    }
    ull b;
    cin >> b;
    vu adj(b);
    for(ull& x : adj) {
      cin >> x;
      x--;
    }
    areas[i] = {terrain, border, race_amount, adj};
  }
  string my_race_s;
  cin >> my_race_s;
  ull my_race = races_ids[my_race_s];

  ull ans = solve(t, abilities, areas, n, my_race);
  cout << ans << '\n';

}
