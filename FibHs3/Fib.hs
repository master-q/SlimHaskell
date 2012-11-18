module Fib where
import Foreign.C.Types

foreign export ccall fib :: CInt -> IO CInt

fib :: CInt -> IO CInt
fib _ = return 0 -- Simplify
