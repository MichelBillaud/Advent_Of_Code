package shuttlesearch;

// Advent of code 2020 - Day 13
// michel billaud - 1 jan 2022
import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
import java.util.function.Function;

public class ShuttleSearch {

    public static void main(String[] args) throws IOException {
        part1_tests();

        var small = new ShuttleSearch("../small.txt");
        small.part1();
        var large = new ShuttleSearch("../large.txt");
        large.part1();

        small.part2();
        large.part2();

    }

    // --------------------------------------------------------
    final String filename;
    final long departure;
    final ArrayList<Long> ids;
    final ArrayList<Long> delays;

    private ShuttleSearch(String filename) throws IOException {
        this.filename = filename;
        var in = new Scanner(Paths.get(filename));
        departure = Integer.parseInt(in.nextLine());
        var fields = Arrays.asList(in.nextLine().split(","));
        long delay = 0;
        ids = new ArrayList<>();
        delays = new ArrayList<>();

        for (var f : fields) {
            if (!"x".equals(f)) {
                ids.add(Long.parseLong(f));
                delays.add(delay);
            }
            delay += 1;
        }
    }

    static long[] euclide(long a, long b) {
        if (b == 0) {
            long[] r = {a, 1, 0};
            return r;
        } else {
            var tmp = euclide(b, a % b);
            var u = tmp[1];
            var v = tmp[2];
            tmp[1] = v;
            tmp[2] = u - (a / b) * v;
            return tmp;
        }
    }

    static long inverse(long a, long mod) {
        var tmp = euclide(a, mod);
        return Math.floorMod(tmp[1], mod);
    }

    private static void part1_tests() {
        var ids = List.of(7, 13, 59, 31, 19);
        int departure = 939;
        Function<Integer, Integer> waiting
                = id -> id - (departure + 1) % id + 1;
        ids.stream()
                .min(Comparator.comparing(waiting))
                .ifPresent(id -> System.out.format("Wait %s for Id %d, result %d\n",
                waiting.apply(id), id, id * waiting.apply(id)));
    }

    private void part1() {
        System.out.format("# Part 1, %s\n", filename);
        Function<Long, Long> waiting
                = id -> id - (departure + 1) % id + 1;
        var id = ids.stream()
                .min(Comparator.comparing(waiting))
                .get();
        System.out.format(
                "- wait %s for id %d, result %d\n\n",
                waiting.apply(id), id, id * waiting.apply(id));

    }

    private void part2() {
        System.out.format("Part 2, %s\n", filename);
        var remainders = new ArrayList<Long>();
        for (int i = 0; i < ids.size(); i++) {
            remainders.add(ids.get(i) - delays.get(i));
        }

        long product_of_ids = 1;
        for (var p : ids) {
            product_of_ids *= p;
        }
        long sum = 0;
        for (int i = 0; i < ids.size(); i++) {
            long nn = product_of_ids / ids.get(i);
            long inv = inverse(nn, ids.get(i));
            sum += remainders.get(i) * inv * nn;
        }
        System.out.format("- smallest timestamp = %d\n\n", 
                sum % product_of_ids);
    }

}
