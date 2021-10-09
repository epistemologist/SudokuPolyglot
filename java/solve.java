import java.util.*;
import java.util.stream.*;
import java.io.*;

public class solve {
    
    public static int[][] genGroups() {
        int[][] out = new int[27][9];
        int index;
        // Generate indicies of row
        for (int i = 0; i < 9; i++) {
            index = 0;
            for (int j = 0; j < 81; j++) {
                if (j / 9 == i) {  out[i][index] = j; index++;  }
            }
        }
        // Generate indicies of cols
        for (int i = 0; i < 9; i++) {
            index = 0;
            for (int j = 0; j < 81; j++) {
                if (j % 9 == i) {  out[i+9][index] = j; index++; } 
            }
        }
        // Generate indicies of boxs
        for (int i = 0; i < 9; i++) {
            index = 0;
            for (int j = 0; j < 81; j++) {
                if (3*(j/27) + (j%9)/3 == i) {  out[i+18][index] = j; index++; }
            }
        }
        return out;
    }
    static final int[][] GROUPS = genGroups();
    public static boolean legalBoard(List<Integer> board) {
        for (int[] g: GROUPS) {
            var counts = Arrays.stream(g).map(x -> board.get(x)).boxed()
                .collect(Collectors.groupingBy(
                            x -> x, 
                            Collectors.counting()
                        ));
            Optional<Long> max = Stream.of(1,2,3,4,5,6,7,8,9)
                .map(x -> counts.get(x))
                .filter(Objects::nonNull)
                .max(Long::compare);
            if (max.isPresent() && max.get() > 1) return false;
        }
        return true;
    }
    
    public static boolean isSolved(List<Integer> board) {
        return Collections.frequency(board, 0) == 0;
    }
    
    
    public static List<Integer> solve(List<Integer> board) {
        if (isSolved(board)) return board;
        List<Integer> boardCopy = new ArrayList<>(board);
        int currentPos = board.indexOf(0);
        for (int i = 1; i <= 9; i++) {
            board.set(currentPos, i);
            if (legalBoard(board)) {
                List<Integer> temp = solve(board);
                if (temp.size() > 0) return temp;
            }
            Collections.copy(board, boardCopy);
        }
        return new ArrayList<Integer>();
    }

    public static List<Integer> getBoard(String s) {
        return s.chars().map(x -> x - '0').boxed().collect(Collectors.toList());
    }

    public static void printBoard(List<Integer> board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) System.out.print(board.get(9*i+j));
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("../sudoku_puzzles"));
        while (sc.hasNextLine()) {
            List<Integer> board = getBoard(sc.nextLine());
            printBoard(solve(board));
        }
    }
}

