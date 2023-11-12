-- https://codeforces.com/gym/103960/problem/D

parse :: String -> (Word, Word, Word)
parse ss =
  let [n, x, y] = map read . words $ ss
   in (n, x, y)

solve1D :: Word -> Word -> Word
solve1D n x
  | x == 2 ^ (n - 1) = 0
  | x < 2 ^ (n - 1) = 1 + solve1D n (2 * x)
  | otherwise = solve1D n (2 ^ n - x)

solve :: (Word, Word, Word) -> Word
solve (n, x, y) = solve1D n x

output :: Word -> String
output = show

main :: IO ()
main = interact $ output . solve . parse
