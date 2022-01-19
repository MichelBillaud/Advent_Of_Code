package testsolver;

/*
    Test for Advent of Code 2020 Day 16 puzzle.
 */
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class TestSolver {

    static List<List<String>> data = List.of(
            List.of("duration", "arrival track", "zone", "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "row", "zone", "departure location", "departure station",
                    "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "departure time", "departure track", "row", "zone",
                    "departure platform",
                    "departure location", "departure station",
                    "arrival platform", "departure date"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "row", "zone", "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "class",
                    "train", "departure time",
                    "departure track", "row", "zone", "departure platform",
                    "price", "departure location", ""
                    + "departure station", "arrival platform", "departure date"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "row", "zone", "departure location",
                    "arrival platform"),
            List.of("duration", "arrival track"),
            List.of("duration"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "row", "zone", "departure platform", "departure location",
                    "departure station", "arrival platform"),
            List.of("duration", "arrival track", "zone"),
            List.of("seat", "duration", "arrival track", "train", "row",
                    "zone", "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "departure time", "row", "zone", "departure platform",
                    "departure location", "departure station",
                    "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "class", "train",
                    "departure time", "departure track", "arrival location",
                    "route", "row", "zone", "departure platform", "price",
                    "departure location", "departure station", "wagon",
                    "arrival platform", "departure date"),
            List.of("seat", "type", "duration", "arrival track", "class", "train",
                    "departure time", "departure track", "row", "zone",
                    "departure platform", "price", "departure location",
                    "departure station", "wagon", "arrival platform",
                    "departure date"),
            List.of("seat", "duration", "arrival track", "train", "zone",
                    "arrival platform"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "departure time", "row", "zone", "departure platform",
                    "departure location", "departure station",
                    "arrival platform", "departure date"),
            List.of("arrival station", "seat", "type", "duration",
                    "arrival track", "class", "train", "departure time",
                    "departure track", "arrival location", "route", "row",
                    "zone", "departure platform", "price", "departure location",
                    "departure station",
                    "wagon", "arrival platform", "departure date"),
            List.of("seat", "type", "duration", "arrival track", "class", "train",
                    "departure time", "departure track", "arrival location",
                    "row", "zone", "departure platform",
                    "price", "departure location", "departure station",
                    "wagon", "arrival platform", "departure date"),
            List.of("seat", "type", "duration", "arrival track", "train",
                    "departure time", "departure track", "row", "zone",
                    "departure platform", "price", "departure location",
                    "departure station", "arrival platform", "departure date"),
            List.of("duration", "arrival track", "train", "zone",
                    "arrival platform")
    );

    public static void main(String[] args) {
        var constraints = data.stream().map(HashSet::new)
                .collect(Collectors.toCollection(ArrayList::new));
        var remaining = IntStream.range(0, constraints.size()).boxed()
                .collect(Collectors.toCollection(ArrayList::new));
        for (var progress = true; progress;) {
            progress = false;
            // les indices où il ne reste qu'une possibilité
            var indices = remaining.stream()
                    .filter(i -> constraints.get(i).size() == 1)
                    .toList();
            if (!indices.isEmpty()) {
                progress = true;
                System.out.println("# Found");
                for (int i : indices) {
                    System.out.format("%d -> %s\n", i, constraints.get(i));
                }
                List<String> values = indices.stream()
                        .map(i -> constraints.get(i).iterator().next())
                        .toList();

                remaining.removeAll(indices);

                System.out.println("- removing values : " + values);
                System.out.println("- Simplified system");
                for (var i : remaining) {
                    constraints.get(i).removeAll(values);
                    System.out.format("%d -> %s\n", i, constraints.get(i));
                }

            }
        }
        System.out.println("- Resultat");
        for (var i = 0; i < constraints.size(); i++) {
            System.out.format("%d -> %s\n", i, constraints.get(i));
        }
    }
}
