-- https://adventofcode.com/2022/day/8

import Data.Char (digitToInt)

parse :: String -> [[Int]]
parse = map (map digitToInt) . lines

takeUntil :: (a -> Bool) -> [a] -> [a]
takeUntil _ [] = []
takeUntil p (x : xs) = if p x then [x] else x : takeUntil p xs

takeUntilEnd :: (a -> Bool) -> [a] -> [a]
takeUntilEnd p = reverse . takeUntil p . reverse

scenicScore :: Ord a => [[a]] -> Int -> Int -> Int
scenicScore xss i j =
  let row = xss !! i
      col = map (!! j) xss
      x = row !! j
   in length (takeUntilEnd (>= x) (take j row))
        * length (takeUntil (>= x) (drop (j + 1) row))
        * length (takeUntilEnd (>= x) (take i col))
        * length (takeUntil (>= x) (drop (i + 1) col))

solve :: [[Int]] -> Int
solve xss =
  let n = length xss
      m = length (head xss)
   in maximum $ [scenicScore xss i j | i <- [0 .. n - 1], j <- [0 .. m - 1]]

main :: IO ()
main = interact $ show . solve . parse
