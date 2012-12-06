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

type Format = [(Int, Double)]

chart :: [Format] -> Renderable ()
chart [sizes, ldds, nms] = toRenderable layout
  where
    lineStyle col = line_width ^= 2
                    $ line_color ^= col
                    $ defaultPlotLines ^. plot_lines_style
    plot1 = plot_lines_style ^= lineStyle (opaque blue)
            $ plot_lines_values ^= [sizes]
            $ plot_lines_title ^= "size"
            $ defaultPlotLines
    plot2 = plot_lines_style ^= lineStyle (opaque red)
            $ plot_lines_values ^= [ldds]
            $ plot_lines_title ^= "ldd"
            $ defaultPlotLines
    plot3 = plot_lines_style ^= lineStyle (opaque green)
            $ plot_lines_values ^= [nms]
            $ plot_lines_title ^= "nm"
            $ defaultPlotLines
    bg = opaque white
    fg = opaque black
    layout = layout1_title ^="size/ldd/nm"
             $ layout1_background ^= solidFillStyle bg
             $ layout1_plots ^= [Left (toPlot plot1),
                                 Left (toPlot plot2),
                                 Left (toPlot plot3)]
             $ setLayout1Foreground fg
             $ defaultLayout1
chart _ = error "Chart should get [a, b, c]."

addIndex :: [Double] -> Format
addIndex = zip [0..]

dumpData :: [String] -> IO [Format]
dumpData files = mapM appl [sizeMe, lddMe, nmMe]
  where
    appl f = fmap addIndex . mapM f $ files

main :: IO ()
main = do
  -- get file paths
  files <- readProcess "find" [".", "-name", "FibHs"] ""
  let files' = sortBy numSort . lines $ files
  -- draw graph
  dats <- dumpData files'
  renderableToPSFile (chart dats) 800 600 "output_graph.ps"
