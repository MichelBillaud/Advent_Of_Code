package conwaycubes;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class ConwayCubes {

    public static void main(String[] args) throws IOException {
        System.out.println("# With Part1 adaptated to 4-dim");
        ConwayCubes small = new ConwayCubes("../small.txt");
        small.solvePart1();
        small.solvePart2();

        ConwayCubes large = new ConwayCubes("../large.txt");
        large.solvePart1();
        large.solvePart2();

    }

    record Position(int x, int y, int z, int w) {

    }

    final String filename;
    final Grid grid;

    public ConwayCubes(String filename) throws IOException {
        this.filename = filename;
        var positions = new HashSet<Position>();
        positions = new HashSet<>();
        int y = 0;
        Scanner in = new Scanner(Paths.get(filename));
        while (in.hasNextLine()) {
            var line = in.nextLine();
            int x = 0;
            for (var c : line.toCharArray()) {
                if (c == '#') {
                    positions.add(new Position(x, y, 0, 0));
                }
                x += 1;
            }
            y += 1;
        }
        this.grid = new Grid(positions);

    }

    record Grid(HashSet<Position> positions) {

        int size() {
            return positions.size();
        }

        Grid step3D() {
            var count = new HashMap<Position, Integer>();
            for (var p : positions) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dz = -1; dz <= 1; dz++) {
                            if (dx != 0 || dy != 0 || dz != 0) {
                                var n = new Position(p.x() + dx, p.y() + dy, 
                                        p.z() + dz, 0);
                                count.put(n, count.getOrDefault(n, 0) + 1);
                            }
                        }
                    }
                }
            }
            var newPositions = new HashSet<Position>();
            count.forEach((p, c) -> {
                if (c == 3 || (c == 2 && positions.contains(p))) {
                    newPositions.add(p);
                }
            });

            return new Grid((newPositions));
        }

        Grid step4D() {
            var count = new HashMap<Position, Integer>();
            for (var p : positions) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dz = -1; dz <= 1; dz++) {
                            for (int dw = -1; dw <= 1; dw++) {
                                if (dx != 0 || dy != 0 || dz != 0 || dw != 0) {
                                    var n = new Position(p.x() + dx, p.y() + dy,
                                            p.z() + dz, p.w() + dw);
                                    count.put(n, count.getOrDefault(n, 0) + 1);
                                }
                            }
                        }
                    }
                }
            }
            var newPositions = new HashSet<Position>();
            count.forEach((p, c) -> {
                if (c == 3 || (c == 2 && positions.contains(p))) {
                    newPositions.add(p);
                }
            });

            return new Grid((newPositions));
        }
    }

    void solvePart1() {

        System.out.format("# Part 1 (new), file %s\n", filename);
        var g = grid;
        System.out.format("- Initial = %d\n", g.size());
        for (int times = 1; times <= 6; times++) {
            g = g.step3D();
            System.out.format("- After %d step = %d\n", times, g.size());
        }
        System.out.format("- Result for part 1 is %d\n", g.size());

    }

    void solvePart2() {

        System.out.format("# Part 2 (4D), file %s\n", filename);
        var g = grid;
        System.out.format("- Initial = %d\n", g.size());
        for (int times = 1; times <= 6; times++) {
            g = g.step4D();
            System.out.format("- After %d step = %d\n", times, g.size());
        }
        System.out.format("- Result for part 2 is %d\n", g.size());
    }

}
