// https://codeforces.com/gym/102428

#include <bits/stdc++.h>

using namespace std;

typedef __int128_t u128;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) ((x).size())

/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(VE)
 * Usage: vi btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	fore(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim = MAX_PR) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vi pr;
	fore(i,2,lim) if (isprime[i]) pr.push_back(i);
	return pr;
}


ull solve(const vector<vu>& sets) {

  vi primes = eratosthenesSieve(7927 + 1);

  random_shuffle(all(primes));

  map<u128, ull> nodes = {{{}, 0}};
  vector<vi> edges = {{}};

  for(const vu& s : sets) {
    ull A = s.size();

    fore(x, 1, (1 << A)) {
      u128 t = 1;
      fore(i, 0, A) if (x & (1 << i)) {
        t *= primes[s[i]];
      }

      if (nodes.find(t) == nodes.end()) {
        nodes[t] = nodes.size();
        edges.push_back({});
        fore(i, 0, A) if (x & (1 << i)) {
          edges.back().push_back(nodes[t/primes[s[i]]]);
        }
      }
    }
  }

  ull K = edges.size();
  vi btoa(K, -1);

  ull ans = dfsMatching(edges, btoa);

  return K - ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

/*   vi primes = eratosthenesSieve();
  fore(i, 981, 991) {
    cerr << primes[i] << endl;
  } */

  ull N;
  cin >> N;
  map<string, ull> ids;
  vector<vu> sets(N);
  fore(i, 0, N) {
    ull A;
    cin >> A;
    fore(j, 0, A) {
      string s;
      cin >> s;
      if (ids.find(s) == ids.end()) {
        ids[s] = ids.size();
      }
      sets[i].push_back(ids[s]);
    }
  }

  auto ans = solve(sets);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
