/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 * Advent of code 2019 - day 19
 */


package monstermessages;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.function.BinaryOperator;

/**
 *
 * @author billaud
 */
public final class MonsterMessages {

    final String filename;
    final HashMap<Integer, Rule> rules;

    // final ArrayList<Integer> minSize, maxSize;
    final Map<Character, HashMap<Integer, Set<List<Integer>> >> delta;
    final ArrayList<String> strings;

    
    public static void main(String[] args) throws IOException {
        var small = new MonsterMessages("../small.txt");
        // small.showRules();
        // small.showDerivatives();
        small.part1();
        
        var large = new MonsterMessages("../large.txt");
        // large.showRules();
        // large.showDerivatives();
        large.part1();
        //var test = new MonsterMessages("../test.txt");
        // test.showRules();
        // test.showDerivatives();
        //
        var medium = new MonsterMessages("../medium.txt");
        medium.part1();
        
        var medium_updated = new MonsterMessages("../medium-updated.txt");
        medium_updated.part1();
                
         var large_updated = new MonsterMessages("../large-updated.txt");
        large_updated.part1();
                
    }

    
    private void showRules() {
        for (var r : rules.values()) {
            System.out.println(r);
        }
    }

    private void showDerivatives() {
        for (var r : rules.values()) {

            System.out.format("Rule %d"
                    // + " (%d-%d)"
                    + "\n" + "a |> %s\n" + "b |> %s\n",
                    r.number,
                    //minSize.get(i), maxSize.get(i),
                    derivatives('a').get(r.number),
                    derivatives('b').get(r.number));
        }
    }

    /*
    ArrayList<Integer> ruleSize(BinaryOperator<Integer> op) {
        var array = new ArrayList<Integer>();
        var memo = new HashMap<Integer, Integer>();
        for (var r : rules.values()) {
            array.add(computeRuleSize(r.number, op, memo));
        }
        return array;
    }

    private Integer computeRuleSize(int i,
            BinaryOperator<Integer> op,
            HashMap<Integer, Integer> memo) {
        var result = memo.get(i);
        if (result == null) {
            result = rules.get(i).apply(
                    letterRule -> 1,
                    standardRule -> standardRule.subs.stream()
                            .map(sub -> sub.stream()
                            .map(id -> computeRuleSize(id, op, memo))
                            .mapToInt(n -> n)
                            .sum())
                            .reduce(op)
                            .get());

            memo.put(i, result);
        }
        return result;
    }
*/
    HashMap<Integer, Set<List<Integer>>> derivatives(char letter) {
        var map = new HashMap<Integer, Set<List<Integer>>>();
        
        for (var r : rules.values()) {
            map.put(r.number, compute_derivative(r.number, letter, map));
        }
        return map;
    }

    private Set<List<Integer>> compute_derivative(int number, char letter,
            HashMap<Integer, Set<List<Integer>>> memo) {
        var result = memo.get(number);
        if (result == null) {
            result = new HashSet<>(
                    rules.get(number).apply(asLetterRule
                            -> (letter == asLetterRule.letter)
                            ? List.of(List.of())
                            : List.of(),
                            asStandartRule -> {
                                var tmp = new ArrayList<List<Integer>>();
                                for (var sub : asStandartRule.subs) {
                                    var derivatives = compute_derivative(sub.get(0), letter, memo);
                                    for (var d : derivatives) {
                                        var seq = new ArrayList<>(d);
                                        seq.addAll(sub.subList(1, sub.size()));
                                        tmp.add(seq);
                                    }
                                }
                                return tmp;
                            }
                    ));
            memo.put(number, result);
        }
        return result;
    }

    public MonsterMessages(String filename) throws IOException {
        this.filename = filename;
        rules = new HashMap<>();
        try ( Scanner data = new Scanner(Paths.get(filename))) {
            while (true) {
                String line = data.nextLine();
                if (line.isBlank()) {
                    break;
                }
                var r = Rule.parse(line);
                rules.put(r.number, r);
            }
         
            delta = Map.of('a', derivatives('a'), 'b', derivatives('b'));
            //minSize = ruleSize(Integer::min);
            // maxSize = ruleSize(Integer::max);

            strings = new ArrayList<>();
            while (data.hasNextLine()) {
                strings.add(data.nextLine());
            }
        }
    }

    boolean accepts(String string) {
        // System.out.println("## Testing " + string);

        var stacks = new HashSet<ArrayList<Integer>>();
        stacks.add(new ArrayList<>(List.of(0)));
        for (int i = 0; i < string.length(); i++) {
            char letter = string.charAt(i);
            // System.out.println("Letter " + letter + ", Stacks " + stacks);
            var newStacks = new HashSet<ArrayList<Integer>>();
            for (var stack : stacks) {
                if (!stack.isEmpty()) {
                    for (var top : delta.get(letter).get(stack.get(0))) {
                        var nstack = new ArrayList<>(top);
                        nstack.addAll(stack.subList(1, stack.size()));
                        newStacks.add(nstack);
                        // possibilité ajouter contrôle de taille
                    }
                }
            }
            stacks = newStacks;
            if (stacks.isEmpty()) break;
        }
        // System.out.println("Stacks " + stacks);
        return stacks.contains(new ArrayList<Integer>());
    }

    private void part1() {
        int nbAccepted = 0;
        for (var string : strings) {
            boolean ok = accepts(string);
            // System.out.format("%6s - %s\n", ok, string);
            if (ok) {
                nbAccepted += 1;
            }
        }
        System.out.format("# Part 1 %s\n - %s strings accepted\n",
                filename, nbAccepted);
    }

    
}
