{-# OPTIONS -Wall #-}
import Data.Char
import Data.List
import System.Process
import Graphics.Rendering.Chart
import Data.Colour
import Data.Colour.Names
import Data.Accessor

isUndefSym :: String -> Bool
isUndefSym xs@(x:_) = isSpace x && head (filter isAlpha xs) == 'U'
isUndefSym _     = False

numSort :: String -> String -> Ordering
numSort a b = a' `compare` b'
  where
    a', b' :: Int
    a' = read $ filter isDigit a
    b' = read $ filter isDigit b

sizeMe :: String -> IO Double
sizeMe f = do
  size <- readProcess "size" [f] ""
  return . read $ (map words . lines $ size) !! 1 !! 3

lddMe :: String -> IO Double
lddMe f = do
  ldd <- readProcess "ldd" [f] ""
  return . read $ show . length . lines $ ldd

nmMe :: String -> IO Double
nmMe f = do
  nm <- readProcess "nm" [f] ""
  return . read $ show . length . filter isUndefSym . lines $ nm

chart :: [(Int, Double)] -> Renderable ()
chart dat = toRenderable layout
  where
    lineStyle col = line_width ^= 2
                    $ line_color ^= col
                    $ defaultPlotLines ^. plot_lines_style
    plot1 = plot_lines_style ^= lineStyle (opaque blue)
            $ plot_lines_values ^= [dat]
            $ plot_lines_title ^= "size"
            $ defaultPlotLines
    bg = opaque white
    fg = opaque black
    layout = layout1_title ^="size/ldd/nm"
           $ layout1_background ^= solidFillStyle bg
 	   $ layout1_plots ^= [Left (toPlot plot1)]
           $ setLayout1Foreground fg
           $ defaultLayout1

addIndex :: [a] -> [(Int, a)]
addIndex = zip [0..]

main :: IO ()
main = do
  -- get file paths
  files <- readProcess "find" [".", "-name", "FibHs"] ""
  let files' = sortBy numSort . lines $ files
  -- draw graph
  sizes <- fmap addIndex . mapM sizeMe $ files'
  renderableToPSFile (chart sizes) 800 600 "output_graph.ps"
