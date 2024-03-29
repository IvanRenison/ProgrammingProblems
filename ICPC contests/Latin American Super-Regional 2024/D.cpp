// https://codeforces.com/gym/105053/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

const ll MAX_PR = 1e6 + 5;
bitset<MAX_PR> isprime;
void sieve(ll lim = MAX_PR) {
  isprime.set(); isprime[0] = isprime[1] = 0;
  for (ll i = 4; i < lim; i += 2) isprime[i] = 0;
  for (ll i = 3; i*i < lim; i += 2) if (isprime[i])
    for (ll j = i*i; j < lim; j += i*2) isprime[j] = 0;
}

bool solve(ll N) {

  map<ll, ll> primes;

  for (ll i = 2; i*i <= N; i++) {
    if (isprime[i]) {
      while (N % i == 0) {
        N /= i;
        primes[i]++;
      }
    }
  }
  if (N > 1) {
    primes[N] = 1;
  }

  if (primes.size() == 1) {
    auto [p, e] = *primes.begin();
    return e % 2 == 1;
  } else if (primes.size() == 2) {
    auto it = primes.begin();
    auto [p0, e0] = *it;
    it++;
    auto [p1, e1] = *it;

    return e0 == 1 && e1 == 1;
  }

  return false;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  sieve();


  ll N;
  cin >> N;

  if (solve(N)) {
    cout << "Y\n";
  } else {

    cout << "N\n";
  }

}