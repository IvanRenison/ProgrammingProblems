// https://codeforces.com/gym/104869/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef vector<bool> vb;

const ll mod = 1e9 + 7;

ll force(ll H, ll W, ll h0, ll w0, ll h1, ll w1, ll h2, ll w2) {
  ll ans = 0;

  fore(i0, 0, H - h0 + 1) fore(j0, 0, W - w0 + 1) {
    fore(i1, 0, H - h1 + 1) fore(j1, 0, W - w1 + 1) {
      fore(i2, 0, H - h2 + 1) fore(j2, 0, W - w2 + 1) {
        vector<vb> cover(H, vb(W, false));
        viiii ijhws = {{i0, j0, h0, w0}, {i1, j1, h1, w1}, {i2, j2, h2, w2}};
        for (auto [i, j, h, w] : ijhws) {
          fore(a, i, i + h) fore(b, j, j + w) {
            cover[a][b] = true;
          }
        }

        bool all_cover = true;
        fore(a, 0, H) fore(b, 0, W) {
          if (!cover[a][b]) {
            all_cover = false;
          }
        }

        ans += all_cover;
      }
    }
  }

  return ans;
}

ll cuenta(ll H, ll W, ll h, ll w) {
  return ((H - h + 1) * (W - w + 1)) % mod;
}


ll calcLine(ll H, ll h0, ll h1, ll h2) {
  assert(h0 + h1 + h2 >= H);

  if (h0 + h1 + h2 == H) {
    return 6;
  }

  vi hs({h0, h1, h2});

  ll ans = 0;

  fore(i, 0, 3) {
    ll h0 = hs[i];

    fore(j, 0, 2) {
      ll h1 = hs[(i + 1 + j) % 3];
      ll h2 = hs[(i + 1 + !j) % 3];

      // h0 al comienzo, h1 al final

      if (h0 + h1 >= H) {
        ans += H - h2 + 1;
        ans %= mod;
      } else {
        ll d = H - h0 - h1;
        assert(d <= h2);
        ans += min({h0 + 1, h1 + 1, H - h2 + 1, h2 - d + 1});
      }
    }
  }

  ans %= mod;

  fore(i, 0, 3) {
    ll h0 = hs[i], h1 = hs[(i + 1) % 3], h2 = hs[(i + 2) % 3];

    ll h01 = max(h0, h1);

    if (h01 + h2 >= H) {
      ans = (ans + mod - 2) % mod;
    }
  }

  return ans;
}

ll solve(ll H, ll W, ll h0, ll w0, ll h1, ll w1, ll h2, ll w2) {

  if ((H == h0 && W == w0) || (H == h1 && W == w1) || (H == h2 && W == w2)) {
    ll ans = (cuenta(H, W, h0, w0) * cuenta(H, W, h1, w1) % mod) * cuenta(H, W, h2, w2);
    ans %= mod;

    return ans;
  }

  if (h0 == H && h1 == H && h2 == H) {
    if (w0 + w1 + w2 < W) {
      return 0;
    }

    ll ans = calcLine(W, w0, w1, w2);
    return ans;
  }

  if (w0 == W && w1 == W && w2 == W) {
    if (h0 + h1 + h2 < H) {
      return 0;
    }

    ll ans = calcLine(H, h0, h1, h2);
    return ans;
  }

  if (h0 == H && h2 == H) {
    swap(h1, h2), swap(w1, w2);
  }

  if (h1 == H && h2 == H) {
    swap(h0, h2), swap(w0, w2);
  }

  if (h0 == H && h1 == H) {
    if (w0 + w1 >= W) {
      ll ans = (2 * cuenta(H, W, h2, w2)) % mod;
      return ans;
    } else {
      if (h2 == H) {
        if (w0 + w1 + w2 < W) {
          return 0;
        } else {
          ll ans = ((w0 + w1 + w2 - W + 1) * 2) % mod;
          return ans;
        }
      } else {
        return 0;
      }
    }
  }



  if (w0 == W && w2 == W) {
    swap(w1, w2), swap(h1, h2);
  }

  if (w1 == W && w2 == W) {
    swap(w0, w2), swap(h0, h2);
  }

  if (w0 == W && w1 == W) {
    if (h0 + h1 >= H) {
      ll ans = (2 * cuenta(H, W, h2, w2)) % mod;
      return ans;
    } else {
      if (w2 == W) {
        if (h0 + h1 + h2 < H) {
          return 0;
        } else {
          ll ans = ((h0 + h1 + h2 - H + 1) * 2) % mod;
          return ans;
        }
      } else {
        return 0;
      }
    }
  }

  if (h1 == H) {
    swap(w0, w1), swap(h0, h1);
  }
  if (h2 == H) {
    swap(w0, w2), swap(h0, h2);
  }

  if (w1 == W) {
    swap(w0, w1), swap(h0, h1);
  }
  if (w2 == W) {
    swap(w0, w2), swap(h0, h2);
  }

  if (h0 == H && w1 == W) {
    ll h_ = H - h1;
    ll w_ = W - w0;
    ll ans = (h_ >= h2 && w_ >= w2) * 4;
    return ans;
  }

  if (h0 == H) {
    ll w_ = W - w0;
    ll ans = (w_ <= w1 && w_ <= w2 && h1 + h2 >= H) * 4;
    return ans;
  }

  if (w0 == W) {
    ll h_ = H - h0;
    ll ans = (h_ <= h1 && h_ <= h2 && w1 + w2 >= W) * 4;
    return ans;
  }

  return 0;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

#ifndef TEST
  ll T;
  cin >> T;
  while (T--) {
    ll H, W, h0, w0, h1, w1, h2, w2;
    cin >> H >> W >> h0 >> w0 >> h1 >> w1 >> h2 >> w2;
    cout << solve(H, W, h0, w0, h1, w1, h2, w2) << '\n';
  }
#else
  fore(_, 0, 1000) {
    ll H = rand() % 7 + 1, W = rand() % 7 + 1;
    ll h0 = rand() % H + 1, w0 = rand() % W + 1;
    ll h1 = rand() % H + 1, w1 = rand() % W + 1;
    ll h2 = rand() % H + 1, w2 = rand() % W + 1;

    ll ans = solve(H, W, h0, w0, h1, w1, h2, w2);
    ll ansf = force(H, W, h0, w0, h1, w1, h2, w2);

    if (ans != ansf) {
      cerr << "ERROR\n";
      cerr << H << ' ' << W << '\n';
      cerr << h0 << ' ' << w0 << '\n';
      cerr << h1 << ' ' << w1 << '\n';
      cerr << h2 << ' ' << w2 << '\n';
      cerr << ans << ' ' << ansf << '\n';
      return 1;
    }
  }
#endif
}
