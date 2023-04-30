-- https://adventofcode.com/2022/day/6

import GHC.Data.List.SetOps ( hasNoDups )

solve :: String -> Int
solve xs =
  let (as, xs') = splitAt 13 xs
   in 13 + solve' as xs'
  where
    solve' :: String -> String -> Int
    solve' _ [] = 0
    solve' [] _ = 0
    solve' (a:as) (x:xs)
      | hasNoDups (x:a:as) = 1
      | otherwise = 1 + solve' (as ++ [x]) xs

main :: IO ()
main = interact $ show . solve
