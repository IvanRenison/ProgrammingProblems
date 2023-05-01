-- https://adventofcode.com/2022/day/5

import Control.Applicative ((<|>))
import Data.List (transpose)
import Data.Maybe (catMaybes, fromJust)
import Parser

type Crane = Char

type Stack = [Crane]

type ShipCargo = [Stack]

data RearrangementOrder = RearrangementOrder
  { amount :: Int,
    from :: Int,
    to :: Int
  }
  deriving (Show)

type RearrangementProcedure = [RearrangementOrder]

parse :: String -> (ShipCargo, RearrangementProcedure)
parse ss =
  let (Just (x, _)) = runParser parser ss
   in x

parser :: Parser (ShipCargo, RearrangementProcedure)
parser = do
  shipCargo <- parseShipCargo
  parseChar '\n'
  rearrangementProcedure <- parseRearrangementProcedure
  return (shipCargo, rearrangementProcedure)

parseShipCargo :: Parser ShipCargo
parseShipCargo = transformShipCargo <$> parseShipCargo'
  where
    transformShipCargo :: [[Maybe Crane]] -> ShipCargo
    transformShipCargo = map catMaybes . transpose

    parseShipCargo' :: Parser [[Maybe Crane]]
    parseShipCargo' = do
      end <- parseString " 1" <|> return "Not end"
      if end /= "Not end"
        then do
          parseLine
          parseChar '\n'
          return []
        else do
          row <- parseShipCargoRow
          parseChar '\n'
          rows <- parseShipCargo'
          return (row : rows)

parseShipCargoRow :: Parser [Maybe Crane]
parseShipCargoRow = do
  c <- parseCrane
  f <- parseChar ' ' <|> return '_'
  if f == '_'
    then return [c]
    else do
      cs <- parseShipCargoRow
      return (c : cs)

parseCrane :: Parser (Maybe Crane)
parseCrane = parseEmptyCrane <|> parseFullCrane
  where
    parseEmptyCrane :: Parser (Maybe Crane)
    parseEmptyCrane = do
      parseString "   "
      return Nothing

    parseFullCrane :: Parser (Maybe Crane)
    parseFullCrane = do
      parseChar '['
      c <- parseAny
      parseChar ']'
      return (Just c)

parseRearrangementProcedure :: Parser RearrangementProcedure
parseRearrangementProcedure = do
  end <- parseEnd <|> return "Not end"
  if end /= "Not end"
    then return []
    else do
      order <- parseRearrangementOrder
      parseChar '\n'
      orders <- parseRearrangementProcedure
      return (order : orders)

parseRearrangementOrder :: Parser RearrangementOrder
parseRearrangementOrder = do
  parseString "move "
  amount <- parseWord
  parseString " from "
  from <- parseWord
  parseString " to "
  to <- parseWord
  return $ RearrangementOrder (read amount) (read from) (read to)

solve :: (ShipCargo, RearrangementProcedure) -> [Crane]
solve (scs, []) = map head scs
solve (scs, order : orders) =
  let scs' = rearrange order scs
   in solve (scs', orders)
  where
    rearrange :: RearrangementOrder -> ShipCargo -> ShipCargo
    rearrange (RearrangementOrder amount from to) scs =
      let (moved, scs_from) = splitAt amount $ scs !! (from - 1)
          scs_to = moved ++ scs !! (to - 1)
       in setAt (from - 1) scs_from $ setAt (to - 1) scs_to scs

setAt :: Int -> a -> [a] -> [a]
setAt i a ls
  | i < 0 = ls
  | otherwise = go i ls
  where
    go _ [] = []
    go 0 (_ : xs) = a : xs
    go n (x : xs) = x : go (n - 1) xs

main :: IO ()
main = interact $ solve . parse
