-- https://adventofcode.com/2022/day/4

import Data.List.Extra (splitOn)

parse1 :: String -> ((Int, Int), (Int, Int))
parse1 ss =
  let [a, b, c, d] = map read $ concatMap (splitOn "-") $ splitOn "," ss
   in ((a, b), (c, d))

parse :: String -> [((Int, Int), (Int, Int))]
parse = map parse1 . lines

solve :: [((Int, Int), (Int, Int))] -> Int
solve =
  length
    . filter
      ( \((a, b), (c, d)) ->
          (a <= c && c <= b) || (a <= d && d <= b) || (c <= a && a <= d) || (c <= b && b <= d)
      )

main :: IO ()
main = interact $ show . solve . parse
