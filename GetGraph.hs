{-# OPTIONS -Wall #-}
import Data.Char
import System.Process

fibhss :: String
fibhss = "FibHs0/FibHs"

isUndefSym :: String -> Bool
isUndefSym xs@(x:_) = isSpace x && head (filter isAlpha xs) == 'U'
isUndefSym _     = False

main :: IO ()
main = do
  -- size
  size <- readProcess "size" [fibhss] ""
  putStrLn $ (map words . lines $ size) !! 1 !! 3
  -- ldd
  ldd <- readProcess "ldd" [fibhss] ""
  print . length . lines $ ldd
  -- nm
  nm <- readProcess "nm" [fibhss] ""
  print $ length . filter isUndefSym . lines $ nm
