-- https://adventofcode.com/2022/day/8

import Data.Char (digitToInt)

parse :: String -> [[Int]]
parse = map (map digitToInt) . lines

isVisible :: Ord a => [[a]] -> Int -> Int -> Bool
isVisible xss i j =
  let row = xss !! i
      col = map (!! j) xss
      x = row !! j
   in all (< x) (take j row)
        || all (< x) (drop (j + 1) row)
        || all (< x) (take i col)
        || all (< x) (drop (i + 1) col)

solve :: [[Int]] -> Int
solve xss =
  let n = length xss
      m = length (head xss)
   in length $ filter (uncurry (isVisible xss)) [(i, j) | i <- [0 .. n - 1], j <- [0 .. m - 1]]

main :: IO ()
main = interact $ show . solve . parse
