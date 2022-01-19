package spherical;

/*
Advent of Code 2015 - Day 3
*/

import java.io.IOException;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Scanner;

public class Spherical {

    private final String filename;
    final String line;

    public Spherical(String filename) throws IOException {
        this.filename = filename;
        try (Scanner in = new Scanner(Paths.get(filename))) {
            line = in.nextLine();
        }
    }

   
    public static void main(String[] args) throws IOException {
        Spherical test = new Spherical("../test4.txt");
        test.part1();
        var puzzle = new Spherical("../puzzle.txt");
        puzzle.part1();
        puzzle.part2();
    }

    record Position(int x, int y) {
    }

    private void part1() {
        var visited = new HashSet<Position>();
        int x = 0, y = 0;
        visited.add(new Position(x, y));
        for (var c : line.toCharArray()) {
            switch (c) {
                case '>' ->
                    x++;
                case '<' ->
                    x--;
                case '^' ->
                    y++;
                case 'v' ->
                    y--;
            }
            visited.add(new Position(x, y));
        }
        System.out.format("Part 1 (%s)\n ", filename);
        System.out.format("- visited houses: %d\n ", visited.size());
        
        
    }
    
    
    private void part2() {
        var visited = new HashSet<Position>();
        int[] x = {0,0}, y = {0,0};
        int turn = 0;
        visited.add(new Position(x[turn], y[turn]));
        for (var c : line.toCharArray()) {
            switch (c) {
                case '>' ->
                    x[turn]++;
                case '<' ->
                    x[turn]--;
                case '^' ->
                    y[turn]++;
                case 'v' ->
                    y[turn]--;
            }
            visited.add(new Position(x[turn], y[turn]));
            turn = 1 - turn;
        }
        System.out.format("Part 2 (%s)\n ", filename);
        System.out.format("- visited houses: %d\n ", visited.size());
        
        
    }

}
