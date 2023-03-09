-- https://adventofcode.com/2022/day/9
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use camelCase" #-}

import Data.Foldable (foldl')
import Data.List (genericIndex, genericLength, genericReplicate, nub)
import Prelude hiding (Left, Right)

data Movement = L Word | R Word | U Word | D Word deriving (Read, Show)

parse :: String -> [Movement]
parse = map read . lines

data SimpleMovement = Left | Right | Up | Down deriving (Show)

simplifyMovement :: Movement -> [SimpleMovement]
simplifyMovement (L n) = genericReplicate n Left
simplifyMovement (R n) = genericReplicate n Right
simplifyMovement (U n) = genericReplicate n Up
simplifyMovement (D n) = genericReplicate n Down

simplifyMovements :: [Movement] -> [SimpleMovement]
simplifyMovements = (>>= simplifyMovement)

data RopeState = RopeState
  { rope :: [(Int, Int)],
    visited_positions :: [(Int, Int)]
  }
  deriving (Show)

setAt :: Word -> a -> [a] -> [a]
setAt i a ls
  | i < 0 = ls
  | otherwise = go i ls
  where
    go _ [] = []
    go 0 (_ : xs) = a : xs
    go n (x : xs) = x : go (n - 1) xs

moveRope_i :: Word -> RopeState -> RopeState
moveRope_i i rs@(RopeState rope visited_positions) =
  let (head_x, head_y) = rope `genericIndex` (i - 1)
      (tail_x, tail_y) = rope `genericIndex` i
   in if head_x `elem` [tail_x - 1 .. tail_x + 1] && head_y `elem` [tail_y - 1 .. tail_y + 1]
        then rs
        else
          let x_movement
                | tail_x < head_x = 1
                | tail_x > head_x = -1
                | otherwise = 0
              y_movement
                | tail_y < head_y = 1
                | tail_y > head_y = -1
                | otherwise = 0
              _tail_x = tail_x + x_movement
              _tail_y = tail_y + y_movement
              _visited_positions
                | i == genericLength rope - 1 = (_tail_x, _tail_y) : visited_positions
                | otherwise = visited_positions
           in rs
                { rope = setAt i (_tail_x, _tail_y) rope,
                  visited_positions = _visited_positions
                }

moveRope :: RopeState -> RopeState
moveRope rs@(RopeState rope _) = foldl' (flip moveRope_i) rs [1 .. genericLength rope - 1]

moveHead :: RopeState -> SimpleMovement -> RopeState
moveHead ts@(RopeState ((head_x, head_y) : rope) _) Left =
  ts {rope = (head_x - 1, head_y) : rope}
moveHead ts@(RopeState ((head_x, head_y) : rope) _) Right =
  ts {rope = (head_x + 1, head_y) : rope}
moveHead ts@(RopeState ((head_x, head_y) : rope) _) Up =
  ts {rope = (head_x, head_y + 1) : rope}
moveHead ts@(RopeState ((head_x, head_y) : rope) _) Down =
  ts {rope = (head_x, head_y - 1) : rope}

updateRopeState :: RopeState -> SimpleMovement -> RopeState
updateRopeState ts dir = moveRope $ moveHead ts dir

solveSimple :: [SimpleMovement] -> Word
solveSimple =
  genericLength
    . nub
    . visited_positions
    . foldl' updateRopeState (RopeState (replicate 10 (0, 0)) [(0, 0)])

solve :: [Movement] -> Word
solve = solveSimple . simplifyMovements

main :: IO ()
main = interact $ show . solve . parse
