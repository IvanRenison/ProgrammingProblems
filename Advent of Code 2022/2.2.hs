-- https://adventofcode.com/2022/day/2

data Shape = Rock | Paper | Scissors deriving (Show, Eq)

data Result = Win | Draw | Loss deriving (Show, Eq)

instance Read Shape where
  readsPrec _ ('A' : xs) = [(Rock, xs)]
  readsPrec _ ('B' : xs) = [(Paper, xs)]
  readsPrec _ ('C' : xs) = [(Scissors, xs)]

instance Read Result where
  readsPrec _ ('X' : xs) = [(Loss, xs)]
  readsPrec _ ('Y' : xs) = [(Draw, xs)]
  readsPrec _ ('Z' : xs) = [(Win, xs)]

points :: Shape -> Int
points Rock = 1
points Paper = 2
points Scissors = 3

shapeFor :: Shape -> Result -> Shape
shapeFor Rock Loss = Scissors
shapeFor Paper Loss = Rock
shapeFor Scissors Loss = Paper
shapeFor Rock Win = Paper
shapeFor Paper Win = Scissors
shapeFor Scissors Win = Rock
shapeFor x Draw = x

resultPoints :: Result -> Int
resultPoints Win = 6
resultPoints Draw = 3
resultPoints Loss = 0

parse :: String -> [(Shape, Result)]
parse = map ((\(a : y : _) -> (read a, read y)) . words) . lines

solve :: [(Shape, Result)] -> Int
solve = sum . map score
  where
    score :: (Shape, Result) -> Int
    score (a, y) = points (shapeFor a y) + resultPoints y

main :: IO ()
main = interact $ show . solve . parse
