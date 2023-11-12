// https://codeforces.com/gym/103185

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef __uint128_t u128;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const u128 ONE = 1;
/*
ull _128_popcount(u128 x) {
  ull l = x, r = x >> 64;
  return __builtin_popcountll(l) + __builtin_popcountll(r);
}

map<u128, u128> dp;

u128 force(u128 x, ull N) {
  if (dp.count(x)) {
    return dp[x];
  }

  if (x & (ONE << N)) {
    return x;
  }
  if (_128_popcount(x) > 10) {
    return -1;
  }


  u128 ans = -1;
  ull ans_count = 128;

  fore(i, 1, N) if (x & (ONE << i)) {
    fore(j, i, N) if (x & (ONE << j)) {
      if (i + j <= N && (x & (ONE << (i + j))) == 0) {
        u128 this_ans = force(x | (ONE << (i + j)), N);
        ull this_count = _128_popcount(this_ans);
        if (this_count < ans_count) {
          ans = this_ans;
          ans_count = this_count;
        }
      }
    }
  }

  dp[x] = ans;
  return ans;
} */

string force[101] = {
  "",
  "",
  "6",
  "14",
  "22",
  "46",
  "78",
  "158",
  "278",
  "590",
  "1070",
  "2206",
  "4174",
  "8494",
  "16542",
  "33838",
  "65814",
  "131862",
  "262734",
  "526622",
  "1049646",
  "2113694",
  "4196510",
  "8397870",
  "16781390",
  "33588270",
  "67117358",
  "134480462",
  "268451998",
  "537135262",
  "1073775662",
  "2147631262",
  "4295033110",
  "8590131478",
  "17180001046",
  "34361852062",
  "68719739470",
  "137441116462",
  "274878433566",
  "549822931246",
  "1099512677422",
  "2199026402350",
  "4398048624798",
  "8796102460462",
  "17592190240926",
  "35185445864494",
  "70368752575534",
  "140737623622814",
  "281474993492046",
  "562950003757134",
  "1125899940430894",
  "2251799964684366",
  "4503599694487854",
  "9007199808393326",
  "18014398643962446",
  "36028805613095070",
  "72057594306379934",
  "144115188881178782",
  "288230376688847006",
  "576460754719359134",
  "1152921505680622638",
  "2305843018072080558",
  "4611686020575019166",
  "9223376434903400606",
  "18446744078004584726",
  "36893488160304070934",
  "73786976303428337942",
  "147573952628331184414",
  "295147905196532826902",
  "590295810500439638318",
  "1180591620751773155486",
  "2361183241988873453982",
  "4722366482938364953166",
  "9444732965945449120334",
  "18889465931616021971246",
  "37778932988857102140462",
  "75557863726189201852702",
  "151115727454096389833270",
  "302231454904207116607790",
  "604462909816179400114846",
  "1208925819615728687383598",
  "2417851639232556885345326",
  "4835703278460715725227054",
  "9671406556926929003349038",
  "19342813113838464843923614",
  "38685626227704417475363886",
  "77371252455345063283655726",
  "154742504910814371363423390",
  "309485009821362660915021982",
  "618970019642742914011891870",
  "1237940039285415460344988718",
  "2475880078570918879476844702",
  "4951760157141591468349072430",
  "9903520318894728219768012958",
  "19807040628566225136009610398",
  "39614081257134438188775901342",
  "79228162514264619068537442382",
  "158456325028529519612034814030",
  "316912650057057913324179558478",
  "633825300114117234023158779982",
  "1267650600228230527396643636270"
};

u128 strto129(const string& s) {
  ull n = s.size();
  u128 d = 1, ans = 0;
  for(ull i = n - 1; i < n; i--) {
    ans += d * (s[i] - '0');
    d *= 10;
  }
  return ans;
}

vuu solve(ull N) {

  //u128 x = force(0b10, N);
  u128 x = strto129(force[N]);

  vu s;

  fore(i, 1, N+1) if (x & (ONE << i)) {
    s.push_back(i);
  }

/*   for (ull a : s) {
    cerr << a << ' ';
  }
  cerr << '\n';
 */
  vuu ans;

  fore(x, 1, s.size()) {
    fore(i, 0, x) {
      fore(j, i, x) {
        if (s[i] + s[j] == s[x]) {
          ans.push_back({1, s[i]});
          ans.push_back({1, s[j]});
          goto end;
        }
      }
    }
    assert(false);
    end:
    x = x;
  }

  return ans;
}

/* ostream& operator<<(ostream& os, __uint128_t value) {
  if (value >= 10) {
    os << (value / 10);
  }
  os << (char)(value % 10 + '0');
  return os;
} */


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

/*   fore(N, 2, 101) {
    u128 x = force(0b10, N);
    cout << N << ' ' << x << endl;
    dp = {};
  } */

  ull M, N;
  cin >> M >> N;

  if (M != 1) {
    cout << "*\n";
  } else {
    auto ans = solve(N);
    for (auto [A, B] : ans) {
      cout << A << ' ' << B << '\n';
    }
  }

  return EXIT_SUCCESS;
}

/*


Entre alturas 1/n y 1/m se pasa a 1/(n+m)

El problema pasa a ser encontrar la mínima secuencia que empiece en 0 y 1,
cada número es suma de dos anteriores, y el último es N

Usar backtraking y correrlo localmente




*/
