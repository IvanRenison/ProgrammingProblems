// https://codeforces.com/gym/101190
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

ll m = -32768;
ll M = 32767;

ii getInts(string& s) {
  vector<string> words = {""};
  for (char c : s) {
    if (c == ' ') {
      words.push_back("");
    } else {
      words.back().push_back(c);
    }
  }

  if (words.size() == 3) {
    ll x = stoll(words[2]);
    if (words[1] == ">=") {
      return {x, M + 1};
    } else {
      return {m, x + 1};
    }
  }

  ll l = stoll(words[2]), r = stoll(words[6]);
  return {l, r + 1};
}

void addInterval(set<ii>& is, ll L, ll R) {
  //if (L)
  auto it = is.lower_bound({L,R}), before = it;
  while (it != is.end() && it->fst <= R) {
    R = max(R, it->snd);
    before = it = is.erase(it);
  }
  if (it != is.begin() && (--it)->snd >= L) {
    L = min(L, it->fst);
    R = max(R, it->snd);
    is.erase(it);
  }
  is.insert(before, {L, R});
}

void solve() {
  vector<string> lines(1);

  getline(cin, lines[0]);

  while (lines.back().back() == '|') {
    lines.back().pop_back(), lines.back().pop_back(), lines.back().pop_back();
    lines.push_back("");
    getline(cin, lines.back());
  }

  set<ii> ints;
  fore(i, 0, lines.size()) {
    auto [L, R] = getInts(lines[i]);
    if (L < R) {
      addInterval(ints, L, R);
    }
  }

  if (ints.empty()) {
    cout << "false\n";
  } else if (ints.size() == 1) {
    auto [L, R] = *ints.begin();
    if (L == m && R == M + 1) {
      cout << "true\n";
    } else {
      for (auto it = ints.begin(); it != ints.end(); ++it) {
        auto [L, R] = *it;
        if (L == m) {
          cout << "x <= " << R - 1;
        } else if (R == M + 1) {
          cout << "x >= " << L;
        } else {
          cout << "x >= " << L << " && x <= " << R - 1;
        }
        if (next(it) != ints.end()) {
          cout << " ||";
        }
        cout << "\n";
      }
    }
  } else {
    for (auto it = ints.begin(); it != ints.end(); ++it) {
      auto [L, R] = *it;
      if (L == m) {
        cout << "x <= " << R - 1;
      } else if (R == M + 1) {
        cout << "x >= " << L;
      } else {
        cout << "x >= " << L << " && x <= " << R - 1;
      }
      if (next(it) != ints.end()) {
        cout << " ||";
      }
      cout << "\n";
    }
  }

}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("hard.in", "r", stdin);
  freopen("hard.out", "w", stdout);
#endif

  solve();

}
/*
=================================================================
==220355==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7035ad4001e0 at pc 0x6370eb3ac303 bp 0x7ffe17125400 sp 0x7ffe171253f0
READ of size 8 at 0x7035ad4001e0 thread T0
    #0 0x6370eb3ac302 in addInterval(std::set<std::pair<long long, long long>, std::less<std::pair<long long, long long> >, std::allocator<std::pair<long long, long long> > >&, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/H.cpp:47
    #1 0x6370eb3ac8ae in solve() /home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/H.cpp:70
    #2 0x6370eb3ad23b in main /home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/H.cpp:107
    #3 0x7035af034e07  (/usr/lib/libc.so.6+0x25e07) (BuildId: 98b3d8e0b8c534c769cb871c438b4f8f3a8e4bf3)
    #4 0x7035af034ecb in __libc_start_main (/usr/lib/libc.so.6+0x25ecb) (BuildId: 98b3d8e0b8c534c769cb871c438b4f8f3a8e4bf3)
    #5 0x6370eb3ab354 in _start (/home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/a.out+0x6354) (BuildId: a929bf2ea83e31c914477615f271c9fb247bfae7)

Address 0x7035ad4001e0 is located in stack of thread T0 at offset 480 in frame
    #0 0x6370eb3ac448 in solve() /home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/H.cpp:55

  This frame has 14 object(s):
    [48, 49) '<unknown>'
    [64, 65) '<unknown>'
    [80, 88) '<unknown>'
    [112, 120) 'it' (line 82)
    [144, 152) '<unknown>'
    [176, 184) '<unknown>'
    [208, 216) '<unknown>'
    [240, 248) '__x' (line 55)
    [272, 288) '<unknown>'
    [304, 320) '<unknown>'
    [336, 352) '<unknown>'
    [368, 392) 'lines' (line 56)
    [432, 480) 'ints' (line 66) <== Memory access at offset 480 overflows this variable
    [512, 544) '<unknown>'
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ivan/Desktop/ProgrammingProblems/ICPC contests/NEERC Northeastern Regional 2016-2017/H.cpp:47 in addInterval(std::set<std::pair<long long, long long>, std::less<std::pair<long long, long long> >, std::allocator<std::pair<long long, long long> > >&, long long, long long)
Shadow bytes around the buggy address:
  0x7035ad3fff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7035ad3fff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7035ad400000: f1 f1 f1 f1 f1 f1 f8 f2 f8 f2 00 f2 f2 f2 00 f2
  0x7035ad400080: f2 f2 00 f2 f2 f2 00 f2 f2 f2 00 f2 f2 f2 00 f2
  0x7035ad400100: f2 f2 00 00 f2 f2 00 00 f2 f2 00 00 f2 f2 00 00
=>0x7035ad400180: 00 f2 f2 f2 f2 f2 00 00 00 00 00 00[f2]f2 f2 f2
  0x7035ad400200: f8 f8 f8 f8 f3 f3 f3 f3 00 00 00 00 00 00 00 00
  0x7035ad400280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7035ad400300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7035ad400380: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7035ad400400: f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==220355==ABORTING

*/