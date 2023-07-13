-- https://codeforces.com/contest/1820/problem/B

parse1 :: String -> String
parse1 = id



-- Get size of longest sequence of 1s in a string
-- The end and start are conected
longest1s :: String -> Int
longest1s cs =
    let
        (us, cs') = break (/= '1') cs
        f :: Int -> Int -> String -> Int
        f maxLength currentLength [] = max maxLength (currentLength + length us)
        f maxLength currentLength (c:cs'')
            | c == '1' = f maxLength (currentLength + 1) cs''
            | otherwise = f (max maxLength currentLength) 0 cs''
    in f 0 0 cs'


solve1 :: String -> Int
solve1 cs =
    let l1s = longest1s cs
    in if length cs == l1s then l1s^2
       else if odd l1s then (l1s `div` 2 + 1)^2
       else (l1s `div` 2)*(l1s `div` 2 + 1)



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
