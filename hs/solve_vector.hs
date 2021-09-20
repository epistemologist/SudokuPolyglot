import Data.Maybe
import qualified Data.Vector as Vector
import Debug.Trace

type Board = Vector.Vector Int
type Group = Vector.Vector Int

count :: Int -> Vector.Vector Int -> Int
count elem array = Vector.length (Vector.filter (==elem) array)

digits :: [Int]
digits = [1 .. 9]

legalGroup :: Group -> Bool
legalGroup group = (<2) (foldr1 max [count d group | d <- digits])


getGroups :: Board -> [Group]
getGroups board = map Vector.fromList (rows ++ cols ++ boxs)
    where
        rows = [ [board Vector.! (9*y+x) | x <- [0..8]]   | y <- [0..8] ]
        cols = [ [board Vector.! (9*x+y) | x <- [0..8]]   | y <- [0..8] ]
        boxs = [ [board Vector.! x | x <- [0..80], 3*(x `div` 27)+(x `mod` 9) `div` 3 == y] | y <- [0..8] ]


legalBoard :: Board -> Bool
legalBoard board = all legalGroup (getGroups board)

solveBoard :: Board -> [Board]
-- solveBoard board | trace ("current board" ++ show board) False = undefined
solveBoard board | (pos == Nothing) = [board]
                 | otherwise = concat (map solveBoard 
                        (filter legalBoard
                             [board Vector.// [((fromJust pos),d)] | d <- digits]
                        )
                    )
                 where pos = Vector.elemIndex 0 board

getSolution :: Board -> Maybe Board
getSolution board = getSolutionHelper (solveBoard board)
    where
        getSolutionHelper [] = Nothing
        getSolutionHelper (x:xs) = Just x

board_example :: Board
board_example = Vector.fromList [3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 0, 0, 7, 0, 6, 0, 3, 0, 5, 0, 0, 0, 7, 0, 0, 0, 9, 0, 8, 0, 9, 0, 0, 0, 2, 0, 0, 0, 4, 0, 1, 0, 8, 0, 0, 0, 5, 0, 0, 0, 9, 0, 4, 0, 3, 0, 1, 0, 0, 0, 7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 6]


