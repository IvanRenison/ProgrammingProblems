// https://codeforces.com/gym/104252/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<int> vi;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define all(x) x.begin(), x.end()
#define sz(x) ((int)(x).size())

/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			fore(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			fore(i,0,n) ws[x[i]]++;
			fore(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			fore(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		fore(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

struct RMQ {
  typedef int T;
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			fore(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

ull solve(string T, ull D) {
  ull n = T.size();

  ull ans = 0;

  SuffixArray sa(T);

  vi inv_sa(n + 1);
  fore(i, 0, n + 1) {
    inv_sa[sa.sa[i]] = i;
  }

  RMQ rmq(sa.lcp);

  for (ull i = 0; i < n;) {
    ans++;
    if (i + D >= n) {
      return ans;
    }

    ull best = D;

    fore(k, 1, D + 1) {
      ull lcp = rmq.query(min(inv_sa[i], inv_sa[i + k]) + 1, max(inv_sa[i], inv_sa[i + k]) + 1);
      best = max(best, k + lcp);
    }

    i += best;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string T;
  ull D;
  cin >> T >> D;

  cout << solve(T, D) << '\n';

  return EXIT_SUCCESS;
}
