// https://codeforces.com/gym/101047/problem/A

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
#define DBG(x) cerr << #x << " = " << x << endl

enum Suit { H, S, C, D };
typedef ull Rank;
typedef optional<Suit> Trump;

typedef pair<Suit, Rank> Card;
typedef vector<Card> Hand;


struct DP {
  map<tuple<ull, optional<Suit>, optional<pair<ull, ull>>, vu>, pair<bool, ull>> dp;
  // dp[plays now][Trick suit][Wining player and card of the trick][Available cards]

  Trump trump;
  vector<Hand> hands;
  ull R;

  DP(Trump trump, const vector<Hand>& hands) : trump(trump), hands(hands), R(hands[0].size()) {}

  Card best_card(Card a, Card b) {
    auto [as, ar] = a;
    auto [bs, br] = b;

    if (as == bs) {
      if (ar > br) {
        return a;
      } else {
        return b;
      }
    } else if (trump.has_value() && bs == *trump) {
      return b;
    } else {
      return a;
    }
  }

  pair<bool, ull> f(ull s, optional<Suit> t, optional<pair<ull, ull>> wij, const vu& xs) {
    auto it = dp.find({s, t, wij, xs});
    if (it != dp.end()) {
      return it->second;
    }

    optional<Card> w;
    if (wij.has_value()) {
      w = hands[wij->first][wij->second];
    }
    ull r = __builtin_popcountll(xs[s]);

    pair<bool, ull> ans = {false, 0};

    if (!t.has_value()) { // is first
      fore(i, 0, R) if (xs[s] & (1 << i)) {
        auto [cs, cr] = hands[s][i];
        vu ys = xs;
        ys[s] ^= (1 << i);
        auto [ta, ra] = f((s + 1) % 4, cs, {{s, i}}, ys);
        ull this_ans = r - (ra + ta);
        ans.second = max(ans.second, this_ans);
      }
    } else {

      bool is_last = true;
      {
        ull first_amount = __builtin_popcountll(xs[s != 0 ? 0 : 1]);
        fore(i, 1, 4) if (i != s) {
          if (__builtin_popcountll(xs[i]) != first_amount) {
            is_last = false;
            break;
          }
        }
      }

      bool has_t = false;
      fore(i, 0, R) if (xs[s] & (1 << i)) {
        if (hands[s][i].first == *t) {
          has_t = true;
          break;
        }
      }

      fore(i, 0, R) if (xs[s] & (1 << i)) {
        Card c = hands[s][i];
        auto [cs, cr] = c;
        if (!has_t || cs == *t) {
          vu ys = xs;
          ys[s] ^= (1 << i);
          Card nw = best_card(*w, c);
          pair<ull, ull> nwij;
          if (nw == *w) {
            nwij = *wij;
          } else {
            nwij = {s, i};
          }
          if (!is_last) {
            auto [ta, ra] = f((s + 1) % 4, t, nwij, ys);
            if (r - (ra + ta) > ans.second + ans.first) {
              ans = {!ta, r - ra - 1};
            }
          } else { // is_last
            auto [ta, ra] = f(nwij.first, {}, {}, ys);
            if (nwij.first % 2 == s % 2) { // We win these trick
              if (ra + 1 > ans.second + ans.first) {
                ans = {true, ra};
              }
            } else { // We lose these trick
              if (r - ra - 1 > ans.second + ans.first) {
                ans = {false, r - ra - 1};
              }
            }
          }
        }
      }
    }

    dp[{s, t, wij, xs}] = ans;
    return ans;
  };

};

ull solve1(Trump trump, const vector<Hand>& hands) {
  ull R = hands[0].size();
  DP dp(trump, hands);
  auto [_, ans] = dp.f(0, {}, {}, {(1ull << R) - 1,(1ull << R) - 1,(1ull << R) - 1,(1ull << R) - 1});
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string trp;
    ull R;
    cin >> trp >> R;

    Trump trump;
    if (trp == "H") trump = H;
    else if (trp == "S") trump = S;
    else if (trp == "C") trump = C;
    else if (trp == "D") trump = D;

    vector<Hand> hands(4, Hand(R));

    for(Hand& hand : hands) {
      for(auto& [suit, rank] : hand) {
        char r, s;
        cin >> r >> s;

        if (r == 'A') rank = 13;
        else if (r == 'K') rank = 12;
        else if (r == 'Q') rank = 11;
        else if (r == 'J') rank = 10;
        else if (r == 'T') rank = 9;
        else rank = r - '1';

        if (s == 'H') suit = H;
        else if (s == 'S') suit = S;
        else if (s == 'C') suit = C;
        else if (s == 'D') suit = D;
      }
    }

    auto ans = solve1(trump, hands);
    assert(ans <= R);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
