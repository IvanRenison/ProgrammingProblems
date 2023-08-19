// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; i++)
#define SZ(x) (x.size())
#define ALL(x) x.begin(), x.end()
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

pair<double, vector<ll>> hungarian(const vector<vector<double>> &a) {
	if (a.empty()) return {0, {}};
	int n = SZ(a) + 1, m = SZ(a[0]) + 1;
	vector<double> u(n), v(m); vector<ll> p(m), ans(n - 1);
	fore(i,1,n) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vector<double> dist(m, 1e20); vector<ll> pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1; double delta = 1e20;
			fore(j,1,m) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			fore(j,0,m) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	fore(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
	return {-v[0], ans}; // min cost
}

vector<ull> solve(vector<vector<ull>> H) {
  ull N = H.size();

  vector<vector<double>> a(N, vector<double>(N));
  fore(i, 0, N) {
    fore(j, 0, N) {
      a[i][j] = -log((double)H[i][j]);
    }
  }

  vector<ll> _ans = hungarian(a).second;
  vector<ull> ans(N);
  fore(i, 0, N) {
    ans[_ans[i]] = i;
  }

  return ans;
}

int main() {
  FIN;

  ull N;
  cin >> N;
  vector<vector<ull>> H(N, vector<ull>(N));
  fore(i, 0, N) {
    fore(j, 0, N) {
      cin >> H[i][j];
    }
  }

  vector<ull> ans = solve(H);
  for(ull v : ans) {
    cout << v + 1 << ' ';
  }
  cout << '\n';

  return 0;
}