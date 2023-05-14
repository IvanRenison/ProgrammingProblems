// https://atcoder.jp/contests/abc301/tasks/abc301_e

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/*

Plantear un grafo completo dirigido con cada caramelo mas el inicio y el final
Calcular la distancia de ir de cada caramelo e inicio y final a cada otro (en la matriz original)

Luego el problema consiste en tratar de pasar por la mayor cantidad de caramelos posibles en t pasos
Este problema es np-completo (Traveling salesman problem)

Como c es hasta 20 se puede igual

Haciendo una función que te diga que saliendo desde x y pasando por (x1, x2, x3, ...) cual es el mínimo costo
Y probar esa función con las 2^18 posibilidades de x1, x2, x3, ...

(esa función creo que es cuadratica)


*/

void solve(void) {

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  return EXIT_SUCCESS;
}
