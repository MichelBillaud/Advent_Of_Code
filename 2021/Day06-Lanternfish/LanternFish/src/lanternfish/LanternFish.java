package lanternfish;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

/**
 *
 * @author billaud
 */
public class LanternFish {

    public static void main(String[] args) throws FileNotFoundException {
        part1("../small.txt", 80);
        part1("../large.txt", 256);
    }

    private static void part1(String filename, int nbDays) throws NumberFormatException, FileNotFoundException {
        // var initialData = "3,4,3,1,2";
        var in = new Scanner(new File(filename));
        var initialData = in.nextLine();

        long[] state = new long[9];
        for (var s : initialData.split(",")) {
            var n = Integer.parseInt(s);
            state[n] += 1;
        }
        System.out.println("" + Arrays.toString(state));
        for (int day = 1; day <= nbDays; day++) {
            long[] newState = new long[9];
            newState[8] = state[0];
            newState[6] = state[0];
            for (int j = 1; j <= 8; j++) {
                newState[j - 1] += state[j];
            }
            state = newState;

        }
        System.out.format("File %s, Day #%d:\t%d lanterfish %s\n",
                filename, nbDays,
                LongStream.of(state).sum(),
                Arrays.toString(state));
    }

    private static void part2() throws NumberFormatException, FileNotFoundException {
        var initialData = "3,4,3,1,2";

        /*var in = new Scanner(new File("../large.txt"));
        var initialData = in.nextLine();
         */
        int[] state = new int[9];
        for (var s : initialData.split(",")) {
            var n = Integer.parseInt(s);
            state[n] += 1;
        }
        System.out.println("" + Arrays.toString(state));
        for (int day = 1; day <= 80; day++) {
            int[] newState = new int[9];
            newState[8] = state[0];
            newState[6] = state[0];
            for (int j = 1; j <= 8; j++) {
                newState[j - 1] += state[j];
            }
            state = newState;
            System.out.format("Day #%d :  lanterfish\t%s\n",
                    day, IntStream.of(state).sum(),
                    Arrays.toString(state));
        }
    }

}
