-- https://adventofcode.com/2022/day/2

data Shape = Rock | Paper | Scissors deriving (Show, Eq)

instance Read Shape where
  readsPrec _ ('A' : xs) = [(Rock, xs)]
  readsPrec _ ('B' : xs) = [(Paper, xs)]
  readsPrec _ ('C' : xs) = [(Scissors, xs)]
  readsPrec _ ('X' : xs) = [(Rock, xs)]
  readsPrec _ ('Y' : xs) = [(Paper, xs)]
  readsPrec _ ('Z' : xs) = [(Scissors, xs)]

points :: Shape -> Int
points Rock = 1
points Paper = 2
points Scissors = 3

wins :: Shape -> Shape -> Bool
wins Rock Scissors = True
wins Paper Rock = True
wins Scissors Paper = True
wins _ _ = False

gamePoints :: (Shape, Shape) -> Int
gamePoints (x, y)
  | x == y = 3
  | wins y x = 6
  | otherwise = 0

parse :: String -> [(Shape, Shape)]
parse = map ((\(x : y : _) -> (read x, read y)) . words) . lines

solve :: [(Shape, Shape)] -> Int
solve = sum . map score
  where
    score :: (Shape, Shape) -> Int
    score (x, y) = points y + gamePoints (x, y)

main :: IO ()
main = interact $ show . solve . parse
