-- https://adventofcode.com/2022/day/1

import Data.List.Extra (null, split)
import Data.List (sortBy)

parse :: String -> [[Int]]
parse = map (map read) . split null . lines

solve :: [[Int]] -> Int
solve = sum . take 3 . sortBy (flip compare) . map sum

main :: IO ()
main = interact $ show . solve . parse
