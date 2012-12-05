module Fib where
import Foreign.C.Types

foreign export ccall fib :: Int -> IO Int

fibonacci :: [Int]
fibonacci = 1:1:zipWith (+) fibonacci (tail fibonacci)

fib :: Int -> IO Int
fib n | 0 <= n && n <= 40 = return $ fibonacci !! fromIntegral n
      | otherwise = return 0
