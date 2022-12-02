// https://codeforces.com/gym/103388/problem/C

#include <iostream>
#include <tuple>
#include <vector>

#define uint unsigned int

using namespace std;

uint pow(uint b, uint e) {
    uint res = 1;
    for (uint i = 0; i < e; i++) {
        res *= b;
    }
    return res;
}

tuple<int, int> solve(uint B, uint L, vector<uint> Ds) {

    uint rem = 0;
    {
        uint sum = 0;
        for (uint i = 0; i < L; i++) {
            // sum += Ds[i] * B^(L-1-i);
            sum += Ds[i] * pow(B, L-1-i);
        }
        rem = sum % (B + 1);
    }

    if (rem == 0) {
        return {0, 0};
    }

    for (uint j = 0; j < L; j++) {
        uint i = L - 1 - j;
        int new_d = Ds[j] - (i % 2 == 0 ? rem : B + 1 - rem);
        if (new_d >= 0) {
            return {j + 1, new_d};
        }
    }

    return {-1, -1};
}

int main(void) {

    uint B, L;
    cin >> B >> L;

    vector<uint> Ds(L);
    for (uint i = 0; i < L; i++) {
        cin >> Ds[i];
    }

    int res1, res2;
    tie(res1, res2) = solve(B, L, Ds);

    cout << res1 << " " << res2;

    return EXIT_SUCCESS;
}
