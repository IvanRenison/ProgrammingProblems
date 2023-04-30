-- https://adventofcode.com/2022/day/3

import Data.Char (isLower, isUpper, ord, toLower)
import Data.List (intersect)

parse :: String -> [(String, String)]
parse = map (\xs -> splitAt (length xs `div` 2) xs) . lines

priority :: Char -> Int
priority c
  | isLower c = ord c - ord 'a' + 1
  | isUpper c = priority (toLower c) + 26

solve :: [(String, String)] -> Int
solve = sum . map (priority . head . uncurry intersect)

main :: IO ()
main = interact $ show . solve . parse
