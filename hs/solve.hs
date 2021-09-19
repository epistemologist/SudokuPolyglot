import Data.Maybe
import Debug.Trace

type Board = [Int]
type Group = [Int]

count :: Int -> [Int] -> Int
count elem array = length (filter (==elem) array)

digits :: [Int]
digits = [1 .. 9]

legalGroup :: Group -> Bool
legalGroup group = (<2) (foldr1 max [count d group | d <- digits])

getGroups :: Board -> [Group]
getGroups board = rows ++ cols ++ boxs
    where
        rows = [ [board !! (9*y+x) | x <- [0..8]]   | y <- [0..8] ]
        cols = [ [board !! (9*x+y) | x <- [0..8]]   | y <- [0..8] ]
        boxs = [ [board !! x | x <- [0..80], 3*(x `div` 27)+(x `mod` 9) `div` 3 == y] | y <- [0..8] ]

legalBoard :: Board -> Bool
legalBoard board = all legalGroup (getGroups board)

getEmptyPosition :: Board -> Int
getEmptyPosition board = getFirstZero board 0 
    where
    getFirstZero :: [Int] -> Int -> Int
    getFirstZero [] n = -1
    getFirstZero (x:xs) n | x == 0 = n
                          | otherwise = (getFirstZero xs (n+1))

spliceElement :: [Int] -> Int -> Int -> [Int]
spliceElement arr index elem = take index arr ++ [elem] ++ drop (index+1) arr



solveBoard :: Board -> [Board]
-- solveBoard board | trace ("current board: " ++ show board) False = undefined
solveBoard board | (pos == -1) = [board]
                 | otherwise = concat (map solveBoard 
                        (filter legalBoard
                             [spliceElement board pos d | d <- digits]
                        )
                    )
                 where pos = getEmptyPosition board

getSolution :: Board -> Maybe Board
getSolution board = getSolutionHelper (solveBoard board)
    where
        getSolutionHelper [] = Nothing
        getSolutionHelper (x:xs) = Just x

board_example :: Board
board_example = [3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 0, 0, 7, 0, 6, 0, 3, 0, 5, 0, 0, 0, 7, 0, 0, 0, 9, 0, 8, 0, 9, 0, 0, 0, 2, 0, 0, 0, 4, 0, 1, 0, 8, 0, 0, 0, 5, 0, 0, 0, 9, 0, 4, 0, 3, 0, 1, 0, 0, 0, 7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 6]


