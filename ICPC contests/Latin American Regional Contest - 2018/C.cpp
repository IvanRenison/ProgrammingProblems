// https://matcomgrader.com/problem/9544/cheap-trips/
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
constexpr ll MAXN = 1e4 + 10;

  ll n;
vector<ii> trips(MAXN);
vector<vector<vi>> dp(MAXN, vector<vi>(7, vi(120, -1)));
ll f(ll pos, ll prevs, ll time) {
  if (pos == n) return 0;

  if (time >= 120) time = 0;

  ll &r = dp[pos][prevs][time];
  if (r != -1) return r;

  r = trips[pos].snd + f(pos + 1, 1, trips[pos].fst);
  if (1 <= prevs && prevs < 6 && time != 0)
    r = min(r,
      trips[pos].snd / (2*(1+(prevs>=2))) + f(pos + 1, prevs + 1, time + trips[pos].fst)
    );

  return r;

}

int main(){FIN;
  cin >> n;
fore(i, 0, n)
{
  ll d, c; cin >> d >> c;
  trips[i] = {d, c*4};
}

  cout << fixed << setprecision(2) << (ld)f(0, 0, 0) / 4.0 << "\n";

  return 0;
}

/*
ivan@archivan ~/D/P/I/Latin American Regional Contest - 2018 (main)> g++ -Wall -Wextra -fsanitize=address -g c.cpp
ivan@archivan ~/D/P/I/Latin American Regional Contest - 2018 (main)> ./a.out
2
120 10
10 30
32.50
ivan@archivan ~/D/P/I/Latin American Regional Contest - 2018 (main)> ./a.out
3
110 10
10 30
1000 101
280.00
ivan@archivan ~/D/P/I/Latin American Regional Contest - 2018 (main)> ./a.out
7
10 1
10 2
10 4
10 4
10 4
10 4
10 1
=================================================================
==76376==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60d000000680 at pc 0x556822f1d751 bp 0x7ffec1d534a0 sp 0x7ffec1d53490
READ of size 8 at 0x60d000000680 thread T0
    #0 0x556822f1d750 in std::vector<long long, std::allocator<long long> >::operator[](unsigned long) /usr/include/c++/13.2.1/bits/stl_vector.h:1126
    #1 0x556822f1c44a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:26
    #2 0x556822f1c64a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:32
    #3 0x556822f1c64a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:32
    #4 0x556822f1c64a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:32
    #5 0x556822f1c64a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:32
    #6 0x556822f1c64a in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:32
    #7 0x556822f1c529 in f(long long, long long, long long) /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:29
    #8 0x556822f1ca43 in main /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:47
    #9 0x7efebb227ccf  (/usr/lib/libc.so.6+0x27ccf) (BuildId: 316d0d3666387f0e8fb98773f51aa1801027c5ab)
    #10 0x7efebb227d89 in __libc_start_main (/usr/lib/libc.so.6+0x27d89) (BuildId: 316d0d3666387f0e8fb98773f51aa1801027c5ab)
    #11 0x556822f1c264 in _start (/home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/a.out+0x2264) (BuildId: 08515f0773c84b6376d2edc8784e2386132da421)

0x60d000000680 is located 0 bytes after 144-byte region [0x60d0000005f0,0x60d000000680)
allocated by thread T0 here:
    #0 0x7efebbae2002 in operator new(unsigned long) /usr/src/debug/gcc/gcc/libsanitizer/asan/asan_new_delete.cpp:95
    #1 0x556822f1fe2a in std::__new_allocator<std::vector<long long, std::allocator<long long> > >::allocate(unsigned long, void const*) /usr/include/c++/13.2.1/bits/new_allocator.h:147
    #2 0x556822f1f7b6 in std::allocator_traits<std::allocator<std::vector<long long, std::allocator<long long> > > >::allocate(std::allocator<std::vector<long long, std::allocator<long long> > >&, unsigned long) /usr/include/c++/13.2.1/bits/alloc_traits.h:482
    #3 0x556822f1f7b6 in std::_Vector_base<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >::_M_allocate(unsigned long) /usr/include/c++/13.2.1/bits/stl_vector.h:378
    #4 0x556822f1efee in std::_Vector_base<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >::_M_create_storage(unsigned long) /usr/include/c++/13.2.1/bits/stl_vector.h:395
    #5 0x556822f1e22c in std::_Vector_base<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >::_Vector_base(unsigned long, std::allocator<std::vector<long long, std::allocator<long long> > > const&) /usr/include/c++/13.2.1/bits/stl_vector.h:332
    #6 0x556822f205ee in std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >::vector(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_vector.h:600
    #7 0x556822f20177 in void std::_Construct<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&>(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_construct.h:119
    #8 0x556822f1ff78 in std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >* std::__do_uninit_fill_n<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > >(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_uninitialized.h:267
    #9 0x556822f1fb4b in std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >* std::__uninitialized_fill_n<false>::__uninit_fill_n<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > >(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_uninitialized.h:284
    #10 0x556822f1f941 in std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >* std::uninitialized_fill_n<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > >(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_uninitialized.h:327
    #11 0x556822f1f49e in std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >* std::__uninitialized_fill_n_a<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > >(std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >*, unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&, std::allocator<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > >&) /usr/include/c++/13.2.1/bits/stl_uninitialized.h:472
    #12 0x556822f1e6a4 in std::vector<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >, std::allocator<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > > >::_M_fill_initialize(unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&) /usr/include/c++/13.2.1/bits/stl_vector.h:1704
    #13 0x556822f1d65f in std::vector<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > >, std::allocator<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > > >::vector(unsigned long, std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > const&, std::allocator<std::vector<std::vector<long long, std::allocator<long long> >, std::allocator<std::vector<long long, std::allocator<long long> > > > > const&) /usr/include/c++/13.2.1/bits/stl_vector.h:569
    #14 0x556822f1cd83 in __static_initialization_and_destruction_0 /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:20
    #15 0x556822f1d031 in _GLOBAL__sub_I_n /home/ivan/Desktop/ProgrammingProblems/ICPC contests/Latin American Regional Contest - 2018/c.cpp:50
    #16 0x7efebb227dfd in __libc_start_main (/usr/lib/libc.so.6+0x27dfd) (BuildId: 316d0d3666387f0e8fb98773f51aa1801027c5ab)

SUMMARY: AddressSanitizer: heap-buffer-overflow /usr/include/c++/13.2.1/bits/stl_vector.h:1126 in std::vector<long long, std::allocator<long long> >::operator[](unsigned long)
Shadow bytes around the buggy address:
  0x60d000000400: 00 00 fa fa fa fa fa fa fa fa 00 00 00 00 00 00
  0x60d000000480: 00 00 00 00 00 00 00 00 00 00 00 00 fa fa fa fa
  0x60d000000500: fa fa fa fa 00 00 00 00 00 00 00 00 00 00 00 00
  0x60d000000580: 00 00 00 00 00 00 fa fa fa fa fa fa fa fa 00 00
  0x60d000000600: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x60d000000680:[fa]fa fa fa fa fa fa fa 00 00 00 00 00 00 00 00
  0x60d000000700: 00 00 00 00 00 00 00 00 00 00 fa fa fa fa fa fa
  0x60d000000780: fa fa 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x60d000000800: 00 00 00 00 fa fa fa fa fa fa fa fa 00 00 00 00
  0x60d000000880: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 fa fa
  0x60d000000900: fa fa fa fa fa fa 00 00 00 00 00 00 00 00 00 00
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
==76376==ABORTING


*/