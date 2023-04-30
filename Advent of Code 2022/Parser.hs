{-# LANGUAGE InstanceSigs #-}
{-# LANGUAGE LambdaCase #-}

module Parser where

import Control.Applicative (Alternative (empty, (<|>)))
import Data.Char (isSpace)

newtype Parser a = Parser {runParser :: String -> Maybe (a, String)}

instance Functor Parser where
  fmap :: (a -> b) -> Parser a -> Parser b
  fmap f (Parser p) = Parser $ \s -> do
    (a, s') <- p s
    return (f a, s')

instance Applicative Parser where
  pure :: a -> Parser a
  pure a = Parser $ \s -> return (a, s)

  (<*>) :: Parser (a -> b) -> Parser a -> Parser b
  (Parser f) <*> (Parser a) = Parser $ \s -> do
    (f', s') <- f s
    (a', s'') <- a s'
    return (f' a', s'')

instance Monad Parser where
  (>>=) :: Parser a -> (a -> Parser b) -> Parser b
  (Parser p) >>= f = Parser $ \s -> do
    (a, s') <- p s
    runParser (f a) s'

instance Alternative Parser where
  empty :: Parser a
  empty = Parser $ const Nothing

  (<|>) :: Parser a -> Parser a -> Parser a
  (Parser p) <|> (Parser q) = Parser $ \s -> p s <|> q s

parseChar :: Char -> Parser Char
parseChar c = Parser $ \case
  [] -> Nothing
  (x : xs) -> if x == c then Just (c, xs) else Nothing

parseString :: String -> Parser String
parseString = traverse parseChar

parseAny :: Parser Char
parseAny = Parser $ \case
  [] -> Nothing
  (x : xs) -> Just (x, xs)

parseUntil :: (Char -> Bool) -> Parser String
parseUntil p = Parser $ \s -> Just $ break p s

parseLine :: Parser String
parseLine = parseUntil (== '\n')

parseWord :: Parser String
parseWord = parseUntil isSpace

parseEnd :: Parser String
parseEnd = Parser $ \case
  [] -> Just ("", "")
  _ -> Nothing
