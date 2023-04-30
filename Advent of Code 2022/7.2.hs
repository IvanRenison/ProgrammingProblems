-- https://adventofcode.com/2022/day/7
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use camelCase" #-}

import Data.Foldable.Extra (notNull)
import Data.List.Extra (split, trim)

data FileSystemTree
  = Dir {name :: String, childs :: [FileSystemTree]}
  | File {size :: Word, name :: String}
  deriving (Eq, Show)

isDir :: FileSystemTree -> Bool
isDir Dir {} = True
isDir _ = False

isFile :: FileSystemTree -> Bool
isFile = not . isDir

data DirContentInfo
  = DirInfo String
  | FileInfo Word String
  deriving (Eq, Show)

data Dir
  = Up
  | Home
  | Down String
  deriving (Eq, Show)

data CommandOutput
  = Cd Dir
  | Ls [DirContentInfo]
  deriving (Eq, Show)

parseCommand :: String -> CommandOutput
parseCommand ('c' : 'd' : ' ' : '.' : '.' : _) = Cd Up
parseCommand ('c' : 'd' : ' ' : '/' : _) = Cd Home
parseCommand ('c' : 'd' : ' ' : xs) = Cd $ Down xs
parseCommand ('l' : 's' : '\n' : xs) = Ls $ map parseLsLine $ lines xs
  where
    parseLsLine :: String -> DirContentInfo
    parseLsLine ('d' : 'i' : 'r' : ' ' : xs) = DirInfo xs
    parseLsLine xs =
      let (size, ' ' : name) = break (== ' ') xs
       in FileInfo (read size) name

parse :: String -> [CommandOutput]
parse = map parseCommand . filter notNull . map trim . split (== '$')

data PartialFileSystemTree
  = PDir
      { pname :: String,
        pchilds :: [PartialFileSystemTree],
        parent :: Maybe PartialFileSystemTree
      }
  | PFile {psize :: Word, pname :: String}
  deriving (Eq, Show)

dirContentInfo_to_PartialFileSystemTree :: DirContentInfo -> PartialFileSystemTree
dirContentInfo_to_PartialFileSystemTree (DirInfo name) =
  PDir name [] Nothing
dirContentInfo_to_PartialFileSystemTree (FileInfo size name) =
  PFile size name

commandOutputs_to_FileSystemTree :: [CommandOutput] -> FileSystemTree
commandOutputs_to_FileSystemTree cos =
  partialToFull $ go (cos ++ [Cd Home]) (PDir "/" [] Nothing)
  where
    go :: [CommandOutput] -> PartialFileSystemTree -> PartialFileSystemTree
    go [] pfst = pfst
    go (Cd Up : cos) (PDir pname pchilds (Just parent@(PDir _ pchilds' _))) =
      go cos $ parent {pchilds = PDir pname pchilds Nothing : pchilds'}
    go (Cd Home : cos) pfst@(PDir _ _ Nothing) = go cos pfst
    go (Cd Home : cos) pfst = go (Cd Up : Cd Home : cos) pfst
    go (Cd (Down name) : cos) pfst@(PDir _ pchilds _) =
      let (pchilds1, dir : pchilds2) = break ((== name) . pname) pchilds
       in go cos $ dir {parent = Just pfst {pchilds = pchilds1 ++ pchilds2}}
    go (Ls ls : cos) pfst@(PDir _ pchilds _) =
      go cos $ pfst {pchilds = map dirContentInfo_to_PartialFileSystemTree ls}

    partialToFull :: PartialFileSystemTree -> FileSystemTree
    partialToFull (PDir name pchilds _) =
      Dir name $ map partialToFull pchilds
    partialToFull (PFile size name) = File size name

solve :: FileSystemTree -> Word
solve fst =
  let (total_size, childs_sizes, grandchilds_sizes) = get_dirs_sizes' fst
      space_needed = total_size - (70000000 - 30000000)
   in minimum $ filter (>= space_needed) $ total_size : childs_sizes ++ grandchilds_sizes
  where
    get_dirs_sizes :: FileSystemTree -> [Word]
    get_dirs_sizes fst =
      let (size, childs_sizes, grandchilds_sizes) = get_dirs_sizes' fst
       in size : childs_sizes ++ grandchilds_sizes

    get_dirs_sizes' :: FileSystemTree -> (Word, [Word], [Word])
    get_dirs_sizes' (File _ _) = (0, [], [])
    get_dirs_sizes' (Dir _ childs) =
      let (dir_childs_sizes, dir_grandchilds_sizes) =
            unzip $ map ((\(s, xs, ys) -> (s, xs ++ ys)) . get_dirs_sizes') $ filter isDir childs
          file_childs_size = sum $ map size $ filter isFile childs
       in (sum dir_childs_sizes + file_childs_size, dir_childs_sizes, concat dir_grandchilds_sizes)

main :: IO ()
main = interact $ show . solve . commandOutputs_to_FileSystemTree . parse
