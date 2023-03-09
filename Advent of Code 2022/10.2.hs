-- https://adventofcode.com/2022/day/10#part2

import Data.Char (toUpper)
import Data.List.Extra (chunksOf)

data Instr = ADDX Int | NOOP deriving (Read, Show)

parse :: String -> [Instr]
parse = map (read . map toUpper) . lines

spritePositions :: Word -> Int -> [Instr] -> [Int]
spritePositions _ _ [] = []
spritePositions i x (instr : instrs) =
  let isAdd = case instr of
        ADDX _ -> True
        NOOP -> False
      thisIsRelevant = (i + 1) `elem` [20, 60, 100, 140, 180, 220]
      nextIsRelevant = (i + 2) `elem` [20, 60, 100, 140, 180, 220]
      isRelevant
        | isAdd = thisIsRelevant || nextIsRelevant
        | otherwise = thisIsRelevant

      _x = case instr of
        ADDX y -> x + y
        _ -> x

      _i = case instr of
        ADDX _ -> i + 2
        NOOP -> i + 1

      recCall = spritePositions _i _x instrs
   in if isAdd then x : x : recCall else x : recCall

renderImage :: [Int] -> [String]
renderImage xs =
  chunksOf 40 $
    map
      (\b -> if b then '#' else '.')
      [(i `mod` 40) `elem` [x - 1, x, x + 1] | (x, i) <- zip xs [0 ..]]

solve :: [Instr] -> [String]
solve = renderImage . spritePositions 1 1

output :: [String] -> String
output = unlines

main :: IO ()
main = interact $ output . solve . parse
