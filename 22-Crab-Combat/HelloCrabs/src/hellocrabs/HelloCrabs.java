/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package hellocrabs;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.stream.Collectors;

public class HelloCrabs {

    final String filename;

    private int points(ArrayList<Integer> deck) {
        int total = 0;
        int weight = deck.size();
        for (var c : deck) {
            total += c * weight;
            weight += -1;
        }
        return total;
    }

    record Configuration(ArrayList<Integer> deck1, ArrayList<Integer> deck2) {

        void print() {
            String l1 = deck1.stream()
                    .map(i -> i.toString())
                    .collect(Collectors.joining(", "));
            String l2 = deck2.stream()
                    .map(i -> i.toString())
                    .collect(Collectors.joining(", "));

            System.out.format("Player 1's deck: %s\nPlayer 2's deck: %s\n",
                    l1, l2);
        }
    }

    record GameResult(int winner, int points) {

    }

    final Configuration start;

    public HelloCrabs(String filename) throws IOException {
        this.filename = filename;
        Scanner in = new Scanner(Paths.get(filename));

        var d1 = new ArrayList<Integer>();

        in.nextLine(); // ignore header
        while (true) {
            var line = in.nextLine().trim();
            if (line.isEmpty()) {
                break;
            }
            d1.add(Integer.parseInt(line));
        }

        var d2 = new ArrayList<Integer>();

        in.nextLine(); // ignore header
        while (in.hasNextLine()) {
            var line = in.nextLine().trim();
            d2.add(Integer.parseInt(line));
        }
        start = new Configuration(d1, d2);

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {

        var small = new HelloCrabs("../small.txt");
        small.part1();
        small.part2();

        var large = new HelloCrabs("../large.txt");
        large.part1();
        large.part2();
    }

    private void part1() {
        int round = 1;
        int winner = 0;
        var configuration = start;

        int winnerPoints = 0;
        while (true) {
            System.out.format("-- Round %d --\n", round);
            configuration.print();

            var h1 = configuration.deck1.get(0);
            var h2 = configuration.deck2.get(0);
            System.out.format("Player 1 plays: %d\n", h1);
            System.out.format("Player 2 plays: %d\n", h2);
            var t1 = new ArrayList<>(configuration.deck1.subList(1,
                    configuration.deck1.size()));
            var t2 = new ArrayList<>(configuration.deck2.subList(1,
                    configuration.deck2.size()));
            if (h1 > h2) {
                System.out.format("Player 1 wins the round!\n");
                t1.add(h1);
                t1.add(h2);
            } else {
                System.out.format("Player 2 wins the round!\n");
                t2.add(h2);
                t2.add(h1);
            }
            configuration = new Configuration(t1, t2);
            if (configuration.deck2.isEmpty()) {
                winner = 1;
                winnerPoints = points(configuration.deck1);
                break;
            }
            if (configuration.deck1.isEmpty()) {
                winner = 2;
                winnerPoints = points(configuration.deck2);
                break;
            }
            System.out.println();
            round++;
        }
        System.out.format("# Part 2, %s\n", filename);
        System.out.format("Winner is player %d with %d points!\n",
                winner, winnerPoints);

    }

    private GameResult playSubgame(Configuration start) {
        var previousRounds = new HashSet<Configuration>();
        var c = start;
        while (true) {
            if (previousRounds.contains(c)) {
                return new GameResult(1, points(c.deck1));
            }
            previousRounds.add(c);

            int roundWinner = 0;

            var h1 = c.deck1.get(0);
            var h2 = c.deck2.get(0);
            if ((c.deck1.size() > h1) && (c.deck2.size() > h2)) {
                // prepare and run subgame
                var d1 = new ArrayList<>(c.deck1.subList(1, h1 + 1));
                var d2 = new ArrayList<>(c.deck2.subList(1, h2 + 1));
                roundWinner = playSubgame(new Configuration(d1, d2)).winner;
            } else {
                roundWinner = h1 > h2 ? 1 : 2;
            }
            var t1 = new ArrayList<>(c.deck1.subList(1,
                    c.deck1.size()));
            var t2 = new ArrayList<>(c.deck2.subList(1,
                    c.deck2.size()));
            if (roundWinner == 1) {
                t1.add(h1);
                t1.add(h2);
                if (t2.isEmpty()) {
                    return new GameResult(1, points(t1));
                }
            } else {
                t2.add(h2);
                t2.add(h1);
                if (t1.isEmpty()) {
                    return new GameResult(2, points(t2));
                }
            }
            c = new Configuration(t1, t2);
        }
    }

    private void part2() {
        var end = playSubgame(start);
        System.out.format("# Part 2, %s\n", filename);
        System.out.format("Player %d wins with %d points\n",
                end.winner, end.points);
    }

}
