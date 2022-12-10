-- https://adventofcode.com/2022/day/10

import Data.Char (toUpper)

data Instr = ADDX Int | NOOP deriving (Read, Show)

parse :: String -> [Instr]
parse = map (read . map toUpper) . lines

sumRelevants :: Int -> Word -> Int -> [Instr] -> Int
sumRelevants acc _ _ [] = acc
sumRelevants acc i x (instr : instrs)
  | i > 220 = acc
  | otherwise =
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

          _acc
            | thisIsRelevant = acc + (fromIntegral i + 1) * x
            | isAdd && nextIsRelevant = acc + (fromIntegral i + 2) * _x
            | otherwise = acc

          _i = case instr of
            ADDX _ -> i + 2
            NOOP -> i + 1
       in sumRelevants _acc _i _x instrs

solve :: [Instr] -> Int
solve = sumRelevants 0 1 1

main :: IO ()
main = interact $ show . solve . parse
