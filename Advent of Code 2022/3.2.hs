-- https://adventofcode.com/2022/day/3

import Data.Char (isLower, isUpper, ord, toLower)
import Data.List (intersect)
import Data.List.Extra (chunksOf)

-- Group every 3 lines
parse :: String -> [(String, String, String)]
parse = map (\xs -> (xs !! 0, xs !! 1, xs !! 2)) . chunksOf 3 . lines

priority :: Char -> Int
priority c
  | isLower c = ord c - ord 'a' + 1
  | isUpper c = priority (toLower c) + 26

solve :: [(String, String, String)] -> Int
solve = sum . map (priority . head . intersect3)
  where
    intersect3 (a, b, c) = intersect a $ intersect b c

main :: IO ()
main = interact $ show . solve . parse
