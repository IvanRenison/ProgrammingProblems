-- https://codeforces.com/contest/1744/problem/E1

import Data.Maybe (listToMaybe)

parse1 :: String -> (Int, Int, Int, Int)
parse1 xs =
  let [a, b, c, d] = map read $ words xs
   in (a, b, c, d)

parse :: String -> [(Int, Int, Int, Int)]
parse xs =
  let (t : xss) = lines xs
   in map parse1 $ take (read t) xss

solve1 :: (Int, Int, Int, Int) -> Maybe (Int, Int)
solve1 (a, b, c, d) =
  listToMaybe [(x, y) | x <- [a + 1 .. c], y <- [b + 1 .. d], (x * y) `mod` (a * b) == 0]

solve :: [(Int, Int, Int, Int)] -> [Maybe (Int, Int)]
solve = map solve1

output1 :: Maybe (Int, Int) -> String
output1 Nothing = "-1 -1"
output1 (Just (x, y)) = show x ++ " " ++ show y

output :: [Maybe (Int, Int)] -> String
output = unlines . map output1

main :: IO ()
main = interact $ output . solve . parse
