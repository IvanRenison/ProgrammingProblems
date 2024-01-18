#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<ll> vi;
typedef vector<ull> vu;

struct Tree {
  typedef pair<ull, ull> T;
  static constexpr T unit = {0, 0};
  vector<T> s; int n;
  T f(T a, T b) {return max(a,b);}
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos*2], s[pos*2+1]);
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

vu solve(vu Hs) {
  ull N = Hs.size();

  Tree t(N);
  fore(i, 0, N) {
    t.update(i, {Hs[i], i});
  }

  vi pre_ans(N + 1);


  function<void(ull l, ull r)> f = [&](ull l, ull r){ // [l, r)
    if (r <= l + 1) {
      return;
    }
    auto [max_v, max_i] = t.query(l, r);
    if (max_i == l) {
      pre_ans[l + 1]++, pre_ans[r == N ? N : (l + r + 1)/2]--;
      f(l + 1, r);
    } else if (max_i + 1 == r) {
      pre_ans[l == 0 ? 0 : (l + max_i + 1)/2]++, pre_ans[max_i]--;
      f(l, r - 1);
    } else {
      pre_ans[l == 0 ? 0 : (l + max_i + 1)/2]++, pre_ans[max_i]--;
      pre_ans[max_i + 1]++, pre_ans[r == N ? N : (max_i + r + 1)/2]--;
      f(l, max_i), f(max_i + 1, r);
    }
  };

  f(0, N);

  vu ans(N);
  ans[0] = pre_ans[0];
  fore(i, 1, N) {
    ans[i] = (ll)ans[i-1] + pre_ans[i];
  }

  return ans;
}

int main(){FIN;

  ull N;
  cin >> N;
  vu Hs(N);
  for(ull& H : Hs) {
    cin >> H;
  }

  vu ans = solve(Hs);

  for(ull b : ans) {
    cout << b << ' ';
  }
  cout << '\n';


  return 0;
}
