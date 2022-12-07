-- https://adventofcode.com/2022/day/6

import GHC.Data.List.SetOps ( hasNoDups )

solve :: String -> Int
solve (a:b:c:xs) = 3 + solve' a b c xs
  where
    solve' :: Char -> Char -> Char -> String -> Int
    solve' _ _ _ [] = 0
    solve' a b c (x:xs)
      | hasNoDups [x, a, b, c] = 1
      | otherwise = 1 + solve' b c x xs

main :: IO ()
main = interact $ show . solve
