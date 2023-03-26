// https://codeforces.com/contest/1744/problem/E1

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;
typedef long long int lint;

pair<lint, lint> solve1(lint a, lint b, lint c, lint d) {

    lint divisor = a*b;

    for (lint x = a+1; x <= c; x++) {
        lint we_have = __gcd(x, divisor);
        lint we_need = a*b / we_have;

        lint y = (b / we_need + 1) * we_need;
        if ( y <= d ) {
            return {x, y};
        }
    }

    return {-1, -1};
}

int main(void) {
    uint t;
    cin >> t;
    for (uint i = 0; i < t; i++) {
        lint a, b, c, d;
        cin >> a >> b >> c >> d;
        pair<lint, lint> res = solve1(a, b, c, d);
        cout << res.first << " " << res.second << "\n";
    }

    return EXIT_SUCCESS;
}
