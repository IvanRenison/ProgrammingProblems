// https://codeforces.com/gym/102428

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
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(a) begin(a), end(a)

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = s.size() + 1, k = 0, a, b;
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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
			jmp.emplace_back(V.size() - pw * 2 + 1);
			fore(j,0,jmp[k].size())
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

vi solve(const string& C, const vector<string>& ss) {
  ull N = ss.size();

  string S = C;
  vu starts(N);
  fore(i, 0, N) {
    S.push_back('[');
    starts[i] = S.size();
    S += ss[i];
  }
  S.push_back('[');
  ull S_size = S.size();

  SuffixArray sa(S);

  vu inv_sa(S.size());
  fore(i, 0, S.size()) {
    inv_sa[sa.sa[i+1]] = i + 1;
  }

  vu prevsInC(S_size, -1);
  fore(i, 0, S_size) {
    if (sa.sa[i + 1] < C.size()) {
      prevsInC[i] = i;
    } else if (i > 0) {
      prevsInC[i] = prevsInC[i - 1];
    }
  }

  vu nextsInC(S_size, -1);
  for(ull i = S_size - 1; i < S_size; i--) {
    if (sa.sa[i + 1] < C.size()) {
      nextsInC[i] = i;
    } else if (i + 1 < S_size) {
      nextsInC[i] = nextsInC[i + 1];
    }
  }

  RMQ<ll> rmq(sa.lcp);

  vi ans(N);

  fore(i, 0, N) {
    ll this_ans = 0, n = ss[i].size();
    for(ull j = 0; j < n; this_ans++) {
      ull Sj = starts[i] + j;
      ull prev = prevsInC[inv_sa[Sj] - 1] + 1;
      ull next = nextsInC[inv_sa[Sj] - 1] + 1;
      assert(prev == 0 || prev < inv_sa[Sj]);
      assert(next == 0 || next > inv_sa[Sj]);

      ll prev_m = prev == 0 ? 0 : rmq.query(prev + 1, inv_sa[Sj] + 1);
      ll next_m = next == 0 ? 0 : rmq.query(inv_sa[Sj] + 1, next + 1);

      ll m = max(prev_m, next_m);

      if (m == 0) {
        this_ans = -1ull;
        break;
      }

      j += m;
    }

    ans[i] = this_ans;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string C;
  cin >> C;

  ull N;
  cin >> N;
  vector<string> ss(N);
  for(string& s : ss) {
    cin >> s;
  }

  auto ans = solve(C, ss);
  for(ll a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
