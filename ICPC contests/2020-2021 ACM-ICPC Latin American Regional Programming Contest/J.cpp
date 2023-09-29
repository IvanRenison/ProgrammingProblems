// https://codeforces.com/gym/103185/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned char uc;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct KDimArray {
  typedef ull T;
  vu ds;
  vector<T> elems;
  KDimArray() {};
  KDimArray(const vu& ds) : ds(ds) {
    ull p = 1;
    for(ull d : ds) {
      p *= d;
    }
    elems = vector<T>(p);
  }
  T operator[](const vu& id) const {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }
  T& operator[](const vu& id) {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }
};

struct Problem {
  ull K;
  vector<vu> recss;
  KDimArray ans;
  Problem(ull K) : K(K) {
    vu ds(K, 9);
    ans = KDimArray(ds);
  }
  void C(const vu& recs) {
    recss.push_back(recs);

    vu is(K, 0);
    while (true) {
      ans[is]++;
      ull j = K + 1;
      for(ull i = K - 1; i < K; i--) {
        if (is[i] < recs[i]) {
          j = i;
          break;
        }
      }
      if (j == K + 1) {
        break;
      }
      is[j]++;
      fore(i, j + 1, K) {
        is[i] = 0;
      }
    }
  }
  void D(ull i) {
    vu recs = recss[i];
    vu is(K, 0);
    while (true) {
      ans[is]--;
      ull j = K + 1;
      for(ull i = K - 1; i < K; i--) {
        if (is[i] < recs[i]) {
          j = i;
          break;
        }
      }
      if (j == K + 1) {
        break;
      }
      is[j]++;
      fore(i, j + 1, K) {
        is[i] = 0;
      }
    }
  }
  ull J(const vu& recs) const {
    return ans[recs];
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;

  Problem p(K);

  fore(i, 0, N) {
    char c;
    cin >> c;
    if (c == 'D') {
      ull j;
      cin >> j;
      j--;
      p.D(j);
    } else {
      ull R;
      cin >> R;
      vu recs(K, 0);
      fore(i, 0, R) {
        ull T;
        cin >> T;
        T--;
        recs[T]++;
      }
      if (c == 'C') {
        p.C(recs);
      } else {
        ull ans = p.J(recs);
        cout << ans << '\n';
      }
    }
  }

  return EXIT_SUCCESS;
}
