import java.util.*;
import java.util.stream.*;
import java.io.*;

public class solve {
    static final int[][] GROUPS = {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16, 17}, {18, 19, 20, 21, 22, 23, 24, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34, 35}, {36, 37, 38, 39, 40, 41, 42, 43, 44}, {45, 46, 47, 48, 49, 50, 51, 52, 53}, {54, 55, 56, 57, 58, 59, 60, 61, 62}, {63, 64, 65, 66, 67, 68, 69, 70, 71}, {72, 73, 74, 75, 76, 77, 78, 79, 80}, {0, 9, 18, 27, 36, 45, 54, 63, 72}, {1, 10, 19, 28, 37, 46, 55, 64, 73}, {2, 11, 20, 29, 38, 47, 56, 65, 74}, {3, 12, 21, 30, 39, 48, 57, 66, 75}, {4, 13, 22, 31, 40, 49, 58, 67, 76}, {5, 14, 23, 32, 41, 50, 59, 68, 77}, {6, 15, 24, 33, 42, 51, 60, 69, 78}, {7, 16, 25, 34, 43, 52, 61, 70, 79}, {8, 17, 26, 35, 44, 53, 62, 71, 80}, {0, 1, 2, 9, 10, 11, 18, 19, 20}, {3, 4, 5, 12, 13, 14, 21, 22, 23}, {6, 7, 8, 15, 16, 17, 24, 25, 26}, {27, 28, 29, 36, 37, 38, 45, 46, 47}, {30, 31, 32, 39, 40, 41, 48, 49, 50}, {33, 34, 35, 42, 43, 44, 51, 52, 53}, {54, 55, 56, 63, 64, 65, 72, 73, 74}, {57, 58, 59, 66, 67, 68, 75, 76, 77}, {60, 61, 62, 69, 70, 71, 78, 79, 80}};

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

