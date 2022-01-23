/*
* AOC 2015 - day 12
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package abacus;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.json.simple.*;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Abacus {

    String filename;
    Object tree;

    public Abacus(String filename) throws FileNotFoundException, ParseException, IOException {
        this.filename = filename;
        JSONParser p = new JSONParser();
        this.tree = p.parse(new FileReader(filename));
    }

    static int part1Sum(Object object) {
        int s = 0;

        switch (object) {
            case JSONArray a -> {
                for (var x : a) {
                    s += part1Sum(x);
                }
            }
            case JSONObject o -> {
                for (var x : o.values()) {
                    s += part1Sum(x);
                }
            }
            case Long n -> {
                s += n;
            }
            case String string -> {
            }

            default -> {
                System.out.format("unknown " + object + object.getClass());
                System.exit(1);
            }
        }
        return s;
    }

    static int part2Sum(Object object) {
        int s = 0;

        switch (object) {
            case JSONArray a -> {
                for (var x : a) {
                    s += part2Sum(x);
                }
            }
            case JSONObject o -> {
                if (o.values().stream().noneMatch(v -> "red".equals(v))) {
                    for (var x : o.values()) {
                        s += part2Sum(x);
                    }
                }
            }
            case Long n -> {
                s += n;
            }
            case String string -> {
            }
            default -> {
                System.out.format("unknown " + object + object.getClass());
                System.exit(1);
            }
        }
        return s;
    }

    public static void main(String[] args) 
            throws FileNotFoundException, IOException, ParseException {
        var puzzle = new Abacus("../puzzle.txt");
        puzzle.solve();
    }

    private void solve() {
        System.out.format("- part 1 sum = %d\n", part1Sum(tree));
        System.out.format("- part 2 sum = %d\n", part2Sum(tree));

    }

}
