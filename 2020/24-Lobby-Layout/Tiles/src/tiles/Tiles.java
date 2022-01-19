/*
 * advent of code 2020 - day 24
 * (c) Michel Billaud
 * michel.billaud@laposte.net   
 */
package tiles;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.List;
import java.util.Map.Entry;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Tiles {

    final String filename;
    final List<Tile> initialBlackTiles;
    final static int[][] D = {
        {0, -1}, {1, 0},
        {-1, -1}, {1, 1},
        {-1, 0}, {0, 1}
    };

    record Tile(int x, int y) {

        static Tile of(String string) {
            int x = 0, y = 0;
            int v = 2;
            for (var c : string.toCharArray()) {
                switch (c) {
                    case 'n' ->
                        v = 0;
                    case 's' ->
                        v = 4;
                    case 'w' -> {
                        x += D[v][0];
                        y += D[v][1];
                        v = 2;
                    }
                    case 'e' -> {
                        x += D[v + 1][0];
                        y += D[v + 1][1];
                        v = 2;
                    }
                }
            }
            return new Tile(x, y);
        }

        Tile[] neighbours() {
            var r = new Tile[6];
            for (int i = 0; i < 6; i++) {
                r[i] = new Tile(x + D[i][0], y + D[i][1]);
            }
            return r;
        }
    }

    public Tiles(String filename) throws IOException {
        this.filename = filename;
        initialBlackTiles = Files.lines(Paths.get(filename))
                .map(Tile::of)
                .collect(Collectors.groupingBy(Function.identity(),
                        Collectors.counting()))
                .entrySet().stream()
                .filter(e -> (e.getValue() % 2) == 1)
                .map(Entry::getKey)
                .toList();
    }

    private void part1() {
        System.out.format("# Part 1 (%s)\n"
                + "- %d black tiles.\n",
                filename,
                initialBlackTiles.size());
    }

    private void part2() {
        var currentBlackTiles = new HashSet<>(initialBlackTiles);
        for (int day = 1; day <= 100; day++) {
            var newBlackTiles = new HashSet<Tile>();
            for (var existingBlack : currentBlackTiles) {
                var count = nbBlackNeighbours(existingBlack, currentBlackTiles);
                if (count == 1 || count == 2) {
                    // stay
                    newBlackTiles.add(existingBlack);
                }
                for (var tile : existingBlack.neighbours()) {
                    if (!currentBlackTiles.contains(tile)) {
                        if (nbBlackNeighbours(tile, currentBlackTiles) == 2) {
                            newBlackTiles.add(tile);
                        }
                    }
                }
            }
            // System.out.format("After Day %d: %d\n", day, newBlackTiles.size());
            currentBlackTiles = newBlackTiles;
        }
            System.out.format("# Part 2 (%s)\n-After Day 100: %d\n", 
                    filename, currentBlackTiles.size());
    }

    private int nbBlackNeighbours(Tile tile, HashSet<Tile> currentBlackTiles) {
        // should we stay or should we go?
        int count = 0;
        for (var n : tile.neighbours()) {
            if (currentBlackTiles.contains(n)) {
                count += 1;
            }
        }
        return count;
    }

    public static void main(String[] args) throws IOException {
        var test = new Tiles("../test.txt");
        test.part1();
        test.part2();
        var puzzle = new Tiles("../puzzle.txt");
        puzzle.part1();
        puzzle.part2();
    }

}
