rows = Array.from(
    [...Array(9).keys()], i => Array.from(
        [...Array(9).keys()], j => 9*i+j
    )
)

cols = Array.from(
    [...Array(9).keys()], i => Array.from(
        [...Array(9).keys()], j => 9*j+i
    )
)

boxs = Array.from(
    [...Array(9).keys()], i => Array.from(
        [...Array(81).keys()].filter(j => 3*(j/27>>0) + (j%9/3)>>0==i)
    )
)

digits = Array.from(Array(9).keys()).map(x => x+1)

s = "000700800006000031040002000024070000010030080000060290000800070860000500002006000"
boardExample = Array.from(s).map(x => x*1)

function legalBoard(board) {
    let groups = [
        ...rows.map(r => r.map(x => board[x])),
        ...cols.map(c => c.map(x => board[x])),
        ...boxs.map(b => b.map(x => board[x])),
    ]
    for (var g of groups) {
        let digitCounts = Array(10).fill(0)
        for (var x of g) { digitCounts[x]++ }
//        console.log(g, digitCounts, Math.max(...digitCounts.slice(1,10)))
        if (Math.max(...digitCounts.slice(1,10)) > 1) return false
    }
    return true
}

function printBoard(board) {
    console.log(
        [...Array(9).keys()].map(
            x => board.slice(9*x, 9*x+9).map(String).join("")
        ).join("\n") + "\n"
    )
}

function solve(board) {
    if (board.indexOf(0) == -1) return board
    let boardCopy = Array.from(board)
    let currentPos = board.indexOf(0)
    for (let i=1; i<=9; i++) {
        board[currentPos] = i
        if (legalBoard(board)) {
            let temp = solve(board)
            if (temp.length > 0) return temp
        }
        board = Array.from(boardCopy)
    }
    return []
}

const fs = require('fs')
fs.readFile("../sudoku_puzzles", 'utf8' , (err, data) => {
    if (err) {
        console.error(err)
        return
    }
    let puzzles = data.split("\n").map(s => Array.from(s).map(Number))
    for (let puzzle of puzzles) {
        printBoard(solve(puzzle))
    }
})



