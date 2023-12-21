// https://codeforces.com/gym/101081/problem/F
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, pluton = b; i < pluton; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

struct UF {
  vi e;
  vu vals;
  UF(ll n) : e(n, -1), vals(n, inf) {}
  bool sameSet(ll a, ll b) { return find(a) == find(b); }
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : find(e[x]); }
  bool join(ll a, ll b, ull i) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    vals[b] = i;
    return true;
  }
  ull findJoin(ll a, ll b) {
    assert(a != b);
    vi as = {a};
    vi bs = {b};
    while (e[a] >= 0) {
      a = e[a];
      as.push_back(a);
    }
    while (e[b] >= 0) {
      b = e[b];
      bs.push_back(b);
    }
    assert(as.size() > 0 && bs.size() > 0);
    assert(as.back() == bs.back());
    while (as.size() > 0 && bs.size() > 0 && as.back() == bs.back()) {
      as.pop_back(), bs.pop_back();
    }
    ull ans = 0;
    for (ull a_ : as) {
      ans = max(ans, vals[a_]);
    }
    for (ull b_ : bs) {
      ans = max(ans, vals[b_]);
    }
    return ans;
  }
};

vu solve(ull N, const vuuu& edges, const vuu& queries) {
  ull M = edges.size(), Q = queries.size();

  vuuu W_uvs(M);
  fore(i, 0, M) {
    auto [u, v, W] = edges[i];
    W_uvs[i] = {W, u, v};
  }

  sort(all(W_uvs));

  UF uf(N);

  fore(i, 0, M) {
    auto [W, u, v] = W_uvs[i];
    uf.join(u, v, W);
  }

  vu ans(Q);

  fore(k, 0, Q) {
    auto [u, v] = queries[k];

    ans[k] = uf.findJoin(u, v);
    assert(ans[k] != inf);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;

  vuuu edges(M);
  for (auto& [A, B, C] : edges) {
    cin >> A >> B >> C;
    A--, B--;
  }
  ull Q;
  cin >> Q;
  vuu queries(Q);
  for (auto& [A, B] : queries) {
    cin >> A >> B;
    A--, B--;
  }

  auto ans = solve(N, edges, queries);
  for (auto a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
