// https://codeforces.com/gym/106682/problem/E
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()


bool solve(vuu& ACs) {
	ull N = ACs.size();

	vu ps(N, -1);
	fore(i, 0, N) {
		auto [A, C] = ACs[i];

		ull B = (1ull << (64 - countl_zero(A))) - 1 - A;

		ull j = lower_bound(ALL(ACs), uu{B, 0}) - ACs.begin();
		if (j < N && ACs[j].first == B) {
			ps[i] = j;
		}
	}

	vu dp(N);
	for (ull u = N; u--; ) {
		if (dp[u] > ACs[u].second) {
			return true;
		}

		dp[u] = ACs[u].second - dp[u];
		if (ps[u] != -1) {
			dp[ps[u]] += dp[u];
		} else {
			if (dp[u] > 0) {
				return true;
			}
		}
	}

	return false;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ull N;
	cin >> N;
	vuu ACs(N);
	for (auto& [A, C] : ACs) {
		cin >> A >> C;
	}

	bool ans = solve(ACs);
	if (ans) {
		cout << "Ana\n";
	} else {
		cout << "Beto\n";
	}

}
