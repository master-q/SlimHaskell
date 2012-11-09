module Foo where
import Foreign.C.Types

foreign export ccall foo :: CInt -> IO CInt
 
fibonacci :: [CInt]
fibonacci = 1:1:zipWith (+) fibonacci (tail fibonacci)

foo :: CInt -> IO CInt
foo n
  | 0 <= n && n <= 40 = return $ fibonacci !! (fromIntegral n)
  | otherwise = return 0
