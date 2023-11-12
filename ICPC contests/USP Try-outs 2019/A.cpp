// https://codeforces.com/gym/102299/problem/A

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
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull KTOP = 5 * 1e4 + 1;

vu solveSimple(const vu& ks, const vuuu& querys) {
  ull n = ks.size(), q = querys.size();

  vu ans(q);

  // Solve for m*m ≤ n
  {
    ull rt = sqrt(n) + 1;

    vector<vu> ans_map(rt);
    fore(i, 0, rt) {
      ans_map[i] = vu(i);
    }

    ull j = 0;
    fore(i, 0, q) {
      auto [r, x, m] = querys[i];
      if (m*m <= n) {
        for(; j < r; j++) {
          ull k = ks[j];
          fore(m2, 1, rt) {
            ull x = k % m2;
            ans_map[m2][x]++;
          }
        }
        ans[i] = ans_map[m][x];
      }
    }
  }

  // solve for m*m > n
  {
    vu ocurr(KTOP);

    ull j = 0;
    fore(i, 0, q) {
      auto [r, x, m] = querys[i];
      if (m*m > n) {
        for(; j < r; j++) {
          ull k = ks[j];
          ocurr[k]++;
        }

        for(ull e = x; e < KTOP; e += m) {
          ans[i] += ocurr[e];
        }
      }
    }
  }

  return ans;
}

enum LR { L, R };

vu solve(vu ks, vuuuu querys) {
  ull q = querys.size();

  vuuuuu ordered_querys;
  fore(i, 0, q) {
    auto [l, r, x, m] = querys[i];
    ordered_querys.push_back({l, x, m, L, i});
    ordered_querys.push_back({r, x, m, R, i});
  }
  sort(all(ordered_querys));

  vuuu simpQuerys;
  for(auto [l, x, m, _, __] : ordered_querys) {
    simpQuerys.push_back({l, x, m});
  }

  vu simpAns = solveSimple(ks, simpQuerys);

  vu ans(q);

  fore(i, 0, 2*q) {
    auto [l, x, m, lr, qi] = ordered_querys[i];
    if(lr == L) {
      ans[qi] = simpAns[i];
    } else {
      ans[qi] = simpAns[i] - ans[qi];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vu ks(n);
  vuuuu querys(q);
  for(ull& k : ks) {
    cin >> k;
  }
  for(auto& [l, r, x, m] : querys) {
    cin >> l >> r >> x >> m;
    l--;
  }

  auto ans = solve(ks, querys);
  for(ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}

/*

Observar que las querys de [L,R] se pueden descomponer en [0,L-1],[0,R]

Responder querys offline descompuestas ordenadas por R


Para las querys m ≤ √N
    Hacer un arreglo de √n elementos con el arreglo i de longitud i
    Para cada elemento sumar 1 en cada arreglo del arreglo en la posición elem % i (para el arreglo i)
    Y después responder cada query en Ο(1)

Para las querys m > √n
    Notar que para cada resto hay pocos números que pueden dar ese resto (máximo √n)

    Tener un arreglo de ocurrencias
    Para cada query (m, x) recorrer los elementos que e % m = x y sumar las ocurrencias




*/