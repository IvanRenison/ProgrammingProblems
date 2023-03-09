-- https://adventofcode.com/2022/day/9

import Data.Foldable (foldl')
import Data.List (genericLength, genericReplicate, nub)
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
  { head_x :: Int,
    head_y :: Int,
    tail_x :: Int,
    tail_y :: Int,
    visited_positions :: [(Int, Int)]
  }
  deriving (Show)

moveTail :: RopeState -> RopeState
moveTail rs@(RopeState head_x head_y tail_x tail_y visited_positions) =
  if head_x `elem` [tail_x - 1 .. tail_x + 1] && head_y `elem` [tail_y - 1 .. tail_y + 1]
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
       in rs
            { tail_x = _tail_x,
              tail_y = _tail_y,
              visited_positions = (_tail_x, _tail_y) : visited_positions
            }

updateRopeState :: RopeState -> SimpleMovement -> RopeState
updateRopeState ts@(RopeState head_x _ _ _ _) Left =
  moveTail $ ts {head_x = head_x - 1}
updateRopeState ts@(RopeState head_x _ _ _ _) Right =
  moveTail $ ts {head_x = head_x + 1}
updateRopeState ts@(RopeState _ head_y _ _ _) Up =
  moveTail $ ts {head_y = head_y + 1}
updateRopeState ts@(RopeState _ head_y _ _ _) Down =
  moveTail $ ts {head_y = head_y - 1}

solveSimple :: [SimpleMovement] -> Word
solveSimple =
  genericLength . nub . visited_positions . foldl' updateRopeState (RopeState 0 0 0 0 [(0, 0)])

solve :: [Movement] -> Word
solve = solveSimple . simplifyMovements

main :: IO ()
main = interact $ show . solve . parse
