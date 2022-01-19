package conwaycubes;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class ConwayCubesPart1 {

    public static void main(String[] args) throws IOException {
        ConwayCubesPart1 small = new ConwayCubesPart1("../small.txt");
        small.solvePart1();
        
        ConwayCubesPart1 large = new ConwayCubesPart1("../large.txt");
        large.solvePart1();
        
    }

    record Position(int x, int y, int z) {

    }

    final String filename;
    Set<Position> positions;

    public ConwayCubesPart1(String filename) throws IOException {
        this.filename = filename;
        this.positions = new HashSet<>();
        int y = 0, z = 0;
        Scanner in = new Scanner(Paths.get(filename));
        while (in.hasNextLine()) {
            var line = in.nextLine();
            int x = 0;
            for (var c : line.toCharArray()) {
                if (c == '#') {
                    positions.add(new Position(x, y, z));
                }
                x += 1;
            }
            y += 1;
        }

    }

    void step() {

        var count = new HashMap<Position, Integer>();
        for (var p : positions) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dz = -1; dz <= 1; dz++) {
                        if (dx != 0 || dy != 0 || dz != 0) {
                            var n = new Position(p.x() + dx, p.y() + dy, p.z() + dz);
                            count.put(n, count.getOrDefault(n, 0) + 1);
                        }
                    }
                }
            }
        }
        var nextGen = new HashSet<Position>();
        count.forEach((p, c) -> {
            if (c == 3 || (c == 2 && positions.contains(p))) {
                nextGen.add(p);
            }
        });

        positions = nextGen;
    }

    void solvePart1() {

        System.out.format("# Part 1, file %s\n", filename);
        System.out.format("- Initial = %d\n", positions.size());
        for (int times = 1; times <= 6; times++) {
            step();
            System.out.format("- After %d step = %d\n", times, positions.size());
        }
    }

}
