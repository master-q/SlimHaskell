{-# OPTIONS -Wall #-}
import Data.Char
import Data.List
import System.Process

fibhss :: String
fibhss = "FibHs0/FibHs"

isUndefSym :: String -> Bool
isUndefSym xs@(x:_) = isSpace x && head (filter isAlpha xs) == 'U'
isUndefSym _     = False

numSort :: String -> String -> Ordering
numSort a b = a' `compare` b'
  where
    a', b' :: Int
    a' = read $ filter isDigit a
    b' = read $ filter isDigit b

sizeMe :: String -> IO String
sizeMe f = do
  size <- readProcess "size" [f] ""
  return $ (map words . lines $ size) !! 1 !! 3

lddMe :: String -> IO String
lddMe f = do
  ldd <- readProcess "ldd" [f] ""
  return $ show . length . lines $ ldd

nmMe :: String -> IO String
nmMe f = do
  nm <- readProcess "nm" [f] ""
  return $ show . length . filter isUndefSym . lines $ nm

main :: IO ()
main = do
  -- get file paths
  files <- readProcess "find" [".", "-name", "FibHs"] ""
  print $ sortBy numSort . lines $ files
  putStrLn =<< sizeMe fibhss
  putStrLn =<< lddMe fibhss
  putStrLn =<< nmMe fibhss
