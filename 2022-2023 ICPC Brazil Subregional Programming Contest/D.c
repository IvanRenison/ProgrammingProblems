// https://codeforces.com/gym/103960/problem/D

#include <stdio.h>
#include <stdlib.h>

unsigned int solve(unsigned int N, unsigned int x) {
    unsigned int res = 0;
    while (x != 1 << (N - 1)) {
        if (x < 1 << (N - 1)) {
            res++;
            x = x * 2;
        } else {
            x = (1 << N) - x;
        }
    }
    return res;
}

int main(void) {
    unsigned int N, x;
    scanf("%u", &N);
    scanf("%u", &x);

    unsigned int res = solve(N, x);

    printf("%u", res);

    return EXIT_SUCCESS;
}
