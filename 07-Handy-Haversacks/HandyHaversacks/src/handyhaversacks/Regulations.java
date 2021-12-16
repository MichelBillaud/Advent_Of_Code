package handyhaversacks;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 *
 * @author billaud
 */
public class Regulations {

    static record ColorCode(String adjective, String color) {

    }

    static record Rule(ColorCode colorCode, Map<ColorCode, Integer> map) {

    }
    final Map<ColorCode, Rule> rules;


    static Rule lineToRule(String line) {
        var array = line.split("[ ,\\.]+");
        var cc = new ColorCode(array[0], array[1]);
        var map = new HashMap<ColorCode, Integer>();
        if (!"no".equals(array[4])) {
            for (int p = 4; p < array.length; p += 4) {
                int quantity = Integer.parseInt(array[p]);
                String adjective = array[p + 1];
                String color = array[p + 2];
                map.put(new ColorCode(adjective, color), quantity);
            }
        }
        return new Rule(cc, map);
    }

    public Regulations(String filename) throws IOException {
        rules = Files.lines(Paths.get(filename))
                .map(Regulations::lineToRule)
                .collect(Collectors.toMap(Rule::colorCode, Function.identity()));
    }

    /**
     * Number of bag colors that can contain shiny gold bags
     */
    int question1() { 
        // compute the symmetric graph
        final var predecessors = new HashMap<ColorCode, Set<ColorCode>>();
        
        rules.keySet().forEach(cc -> predecessors.put(cc, new HashSet<>()));
        rules.values().forEach(r -> {
            r.map.keySet().forEach(e -> predecessors.get(e).add(r.colorCode()));
        });
        
        // explore from shiny gold as root.
        var reachable = new HashSet<ColorCode>();
        var todo = new Stack<ColorCode>();
        todo.add(new ColorCode("shiny", "gold"));

        while (!todo.isEmpty()) {
            ColorCode c = todo.pop();

            Set<ColorCode> v = predecessors.get(c);
            v.removeAll(reachable);
            todo.addAll(v);
            reachable.addAll(v);
        }
        return reachable.size();
    }

    /**
     * How many individual bags are required inside your single shiny gold bag.
     * We memoize the results to avoid repeating computations.
     */
    int question2() {
        var cc = new ColorCode("shiny", "gold");
        var memo = new HashMap<ColorCode, Integer>();
        return nb_bags(cc, memo);
    }

    private int nb_bags(ColorCode cc, HashMap<ColorCode, Integer> memo) {

        if (memo.containsKey(cc)) {
            return memo.get(cc);
        } else {
            int s = 
              rules.get(cc).map.entrySet().stream()
                    .mapToInt(p -> p.getValue() * (1 + nb_bags(p.getKey(), memo)))
                    .sum();
            memo.put(cc, s);
            return s;
        }
    }
}
