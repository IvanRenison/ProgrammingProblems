-- https://adventofcode.com/2022/day/1

import Data.List.Extra (null, split)

parse :: String -> [[Int]]
parse = map (map read) . split null . lines

solve :: [[Int]] -> Int
solve = maximum . map sum

main :: IO ()
main = interact $ show . solve . parse
