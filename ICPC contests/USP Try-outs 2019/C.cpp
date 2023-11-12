// https://codeforces.com/gym/102299/problem/C

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


struct Problem {
  set<pair<ull, ull>> ws;
  map<ull, ull> id_w;
  Problem(vu _ws) {
    fore(i, 0, _ws.size()) {
      ws.insert({_ws[i], i});
      id_w[i] = _ws[i];
    }
  }

  void add(ull W, ull id) {
    ws.insert({W, id});
    id_w[id] = W;
  }

  void del(ull id) {
    ws.erase({id_w[id], id});
    id_w.erase(id);
  }

  ull calc(ull id) {
    ull w = id_w[id];
    auto it_w = ws.lower_bound({w, id});

    ull ans = 0;
    ull sum = 0;
    for (auto it = ws.begin(); it != ws.end();) {
      if (sum + it->first <= w || it == it_w || it_w == ws.end()) {
        ans++;
        sum += it->first;

        if (it == it_w) {
          it_w = ws.end();
        }
        
        it = ws.lower_bound({sum, sum == it->first ? it->second + 1 : 0});
      } else {
        it = it_w;
        it_w = ws.end();
      }
    }

    return ans;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, Q;
  cin >> N >> Q;
  vu ws(N);
  for(ull& w : ws) {
    cin >> w;
  }

  Problem p(ws);

  fore(i, 0, Q) {
    char c;
    cin >> c;
    if (c == '+') {
      ull W, id;
      cin >> W >> id;
      id--;
      p.add(W, id);
    } else if (c == '-') {
      ull id;
      cin >> id;
      id--;
      p.del(id);
    } else {
      ull id;
      cin >> id;
      id--;
      cout << p.calc(id) << '\n';
    }
  }

  return EXIT_SUCCESS;
}

/*

Si fuera una sola query ? (sin ID) hacer greedy (desde el comienzo agarrando siempre que se puede)
Si ademas hubiera updates (pero ? sin ID) hacer el mismo greedy pero usando lower_bound para buscar el siguiente (para que quede log²)
Para las querys con ID, hacer el greedy hasta que no se puede agregar ID, sacar el último, agregar ID y seguir con el greedy


*/