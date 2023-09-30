// https://codeforces.com/gym/104603/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

ull minimumSpanningTreeCost(ull n, const vuuu& edges) {
  ull ans = 0;
  UF uf(n);
  for (auto [w, u, v] : edges) {
    // cerr << "edge: " << u << " " << v << " " << w << endl;
    if (uf.join(u, v)) ans += w;
  }
  return ans;
}

vuuu down_right_edges(const viii& HLRs) {
  ull N = HLRs.size();

  viii lefts(N), rights(N);
  fore(i, 0, N) {
    auto [H, L, R] = HLRs[i];
    lefts[i] = {L + H, H, i + 1};
    rights[i] = {R + H, H, i + 1};
  }

  sort(lefts.begin(), lefts.end()), sort(rights.begin(), rights.end());

  vuuu edges;

  set<pair<ull, ull>> active;
  active.insert({0, 0});
  ull j = 0;
  for(auto [x, H, u] : lefts) {
    while (j < N && get<0>(rights[j]) < x) {
      auto [_, Hv, v] = rights[j];
      active.erase({Hv, v});
      j++;
    }

    auto it = active.lower_bound({H, 0});
    if (it != active.end()) {
      auto [Hv, v] = *it;
      edges.push_back({Hv - H, v, u});
    }
    it--;
    auto [Hv, v] = *it;
    edges.push_back({H - Hv, v, u});

    active.insert({H, u});
  }

  return edges;
}

ull solve(viii& HLRs) {
  ull N = HLRs.size();

  ll H_max = 0;
  for (auto& [H, L, R] : HLRs) {
    H_max = max(H_max, H);
  }
  H_max++;

  vuuu edges = down_right_edges(HLRs);
  for (auto& [H, L, R] : HLRs) {
    swap(L, R);
    L = -L, R = -R;
  }

  auto edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    edges.push_back({w, u, v});
  }

  reverse(HLRs.begin(), HLRs.end());
  for(auto& [H, L, R] : HLRs) {
    H = H_max - H;
  }

  edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    if (u != 0) {
      edges.push_back({w, N + 1 - v, N + 1 - u});
    }
  }

  for (auto& [H, L, R] : HLRs) {
    swap(L, R);
    L = -L, R = -R;
  }

  edges2 = down_right_edges(HLRs);
  for(auto& [w, u, v] : edges2) {
    if (u != 0) {
      edges.push_back({w, N + 1 - v, N + 1 - u});
    }
  }

  sort(edges.begin(), edges.end());

  ull ans = minimumSpanningTreeCost(N + 1, edges);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  viii HLRs(N);
  for (auto& [H, L, R] : HLRs) {
    cin >> H >> L >> R;
  }

  auto ans = solve(HLRs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
