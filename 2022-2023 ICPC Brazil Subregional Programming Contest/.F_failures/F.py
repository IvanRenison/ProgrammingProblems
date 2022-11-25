# https://codeforces.com/gym/103960/problem/F

from typing import Dict, List, Optional, Tuple


def most_common_chars(word: str) -> List[str]:
    """
    >>> most_common_chars('abc')
    ['a', 'b', 'c']
    """
    if word == '':
        return [
            "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
            "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
        ]
    amount_of_chars: Dict[str, int] = {}
    for c in word:
        if c not in amount_of_chars:
            amount_of_chars[c] = 0
        amount_of_chars[c] += 1

    max_amount: int = max(amount_of_chars.values())
    return ["a"] + [c for c in amount_of_chars if amount_of_chars[c] == max_amount]


def solve(words: List[str]) -> Tuple[str, int]:
    indexes: List[int] = [word.find('*') for word in words]

    transpose_words: List[str] = [''.join(
        [word[i] for word in words if word[i] != '*']) for i in range(len(words[0]))]
    most_common_char_column: List[List[str]] = [
        most_common_chars(word) for word in transpose_words]

    valid_words: List[str] = []
    for j, word in enumerate(words):
        i: int = indexes[j]
        for c in most_common_char_column[i]:
            new_word: str = word[:i] + c + word[i+1:]
            valid_words.append(new_word)

    valid_words.sort()

    valid_words_compatibilities: List[int] = [0] * len(valid_words)
    for j, word in enumerate(valid_words):
        for k, word2 in enumerate(words):
            i: int = indexes[k]
            if word[:i] == word2[:i] and word[i+1:] == word2[i+1:]:
                valid_words_compatibilities[j] += 1

    max_compatibilities: int = max(valid_words_compatibilities)
    max_compatibilities_indexes: List[int] = [
        i for i, v in enumerate(valid_words_compatibilities) if v == max_compatibilities]
    new_words: List[str] = [valid_words[k] for k in max_compatibilities_indexes]

    # Find original word
    # original_words: List[str] = []
    # for new_word in new_words:
    #     for j, word2 in enumerate(words):
    #         i: int = indexes[j]
    #         if new_word[:i] == word2[:i] and new_word[i+1:] == word2[i+1:]:
    #             original_words.append(new_word[:i] + 'a' + new_word[i+1:])


    # if max_compatibilities == 1:
    #     return min(original_words), max_compatibilities

    return min(new_words), max_compatibilities


def parse() -> List[str]:
    N, _ = map(int, input().split())
    return [input() for _ in range(N)]


def main():
    words = parse()
    res = solve(words)
    print(*res)


if __name__ == '__main__':
    main()
