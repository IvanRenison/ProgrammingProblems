// https://codeforces.com/gym/103960/problem/N

#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef unsigned int uint;

// Parse N, As, Bs, K, L
static inline void
parse(uint& N, vector<uint>& As, vector<uint>& Bs, uint& K, uint& L) {
    cin >> N;
    As.resize(N);
    Bs.resize(N);
    for (uint i = 0; i < N; i++) {
        cin >> As[i];
    }
    for (uint i = 0; i < N; i++) {
        cin >> Bs[i];
    }

    cin >> K >> L;
}

static inline uint solve(
    uint const N, vector<uint> const As, vector<uint> const Bs, uint const K,
    uint const L
) {
    uint highest_score_possible = 0;

    for (uint i = 0; i <= K; i++) {
        uint score = 0;
        for (uint j = 0; j < i; j++) {
            score += As[j];
        }
        for (uint j = N - (K - i); j < N; j++) {
            score += As[j];
        }

        // Get the L highest cards from Bs[...i] + Bs[N-(K-i)...]

        // set of size L, sorted in ascending order

        multiset<uint> highest_cards;

        for (uint j = 0; j < i; j++) {
            if (highest_cards.size() < L) {
                highest_cards.insert(Bs[j]);
            } else {
                if (Bs[j] > *highest_cards.begin()) {
                    highest_cards.erase(highest_cards.begin());
                    highest_cards.insert(Bs[j]);
                }
            }
        }
        for (uint j = N - (K - i); j < N; j++) {
            if (highest_cards.size() < L) {
                highest_cards.insert(Bs[j]);
            } else {
                if (Bs[j] > *highest_cards.begin()) {
                    highest_cards.erase(highest_cards.begin());
                    highest_cards.insert(Bs[j]);
                }
            }
        }

        for (multiset<uint>::iterator card = highest_cards.begin();
             card != highest_cards.end(); card++) {
            score += *card;
        }

        if (score > highest_score_possible) {
            highest_score_possible = score;
        }
    }

    return highest_score_possible;
}

int main(void) {
    // Parse N, As, Bs, K, L from stdin
    uint N, K, L;
    vector<uint> As, Bs;
    parse(N, As, Bs, K, L);
    uint res = solve(N, As, Bs, K, L);
    cout << res;

    return EXIT_SUCCESS;
}
