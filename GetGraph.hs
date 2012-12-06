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
    lineStyle col dash = line_width ^= 2
                         $ line_color ^= col
                         $ line_dashes ^= dash
                         $ defaultPlotLines ^. plot_lines_style
    plot1 = plot_lines_style ^= lineStyle (opaque lightgray) []
            $ plot_lines_values ^= [sizes]
            $ plot_lines_title ^= "Size"
            $ defaultPlotLines
    plot2 = plot_lines_style ^= lineStyle (opaque gray) []
            $ plot_lines_values ^= [ldds]
            $ plot_lines_title ^= "Shared libs"
            $ defaultPlotLines
    plot3 = plot_lines_style ^= lineStyle (opaque black) []
            $ plot_lines_values ^= [nms]
            $ plot_lines_title ^= "Undefined symbols"
            $ defaultPlotLines
    bg = opaque white
    fg = opaque black
    layout = layout1_title ^="Size / Shared libs / Undefined symbols"
             $ layout1_background ^= solidFillStyle bg
             $ layout1_plots ^= [Left (toPlot plot1),
                                 Left (toPlot plot2),
                                 Left (toPlot plot3)]
             $ setLayout1Foreground fg
             $ defaultLayout1
chart _ = error "chart should get [a, b, c]."

addIndex :: [Double] -> Format
addIndex = zip [0..]

normalize :: [Double] -> [Double]
normalize (x:xs) = 1 : fmap (/ x) xs
normalize _ = error "normalize get empty list."

dumpData :: [String] -> IO [Format]
dumpData files = mapM appl [sizeMe, lddMe, nmMe]
  where
    appl f = fmap addIndex . fmap normalize . mapM f $ files

main :: IO ()
main = do
  -- get file paths
  files <- readProcess "find" [".", "-name", "FibHs"] ""
  let files' = sortBy numSort . lines $ files
  -- draw graph
  dats <- dumpData files'
  renderableToPSFile (chart dats) 800 600 "size_graph.ps"
