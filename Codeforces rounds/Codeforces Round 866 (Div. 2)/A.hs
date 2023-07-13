-- https://codeforces.com/contest/1820/problem/A

parse1 :: String -> String
parse1 = id


split :: Eq a => a -> [a] -> [[a]]
split _ [] = []
split x xs =
    let (l, r) = break (== x) xs
    in l : case r of
        [] -> []
        _:rs -> split x rs


solve1 :: String -> Int
solve1 cs = (sum . map ((+ (-1)) . length) . filter (not . null) . split '^' $ cs) + ends
    where
        ends = case cs of
            [] -> 0
            '_':[] -> 2
            '^':[] -> 1
            _ -> (if head cs == '_' then 1 else 0) + (if last cs == '_' then 1 else 0)


output1 :: Int -> String
output1 = show

parseN :: String -> [String]
parseN cs =
    let l:ls = lines cs
        n = read l
    in map parse1 $ take n ls

outputN :: [Int] -> String
outputN = unlines . map output1

main :: IO ()
main = interact $ outputN . map solve1 . parseN
