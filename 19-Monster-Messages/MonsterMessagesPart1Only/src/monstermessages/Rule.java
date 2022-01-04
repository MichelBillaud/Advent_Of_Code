package monstermessages;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

abstract class Rule {

    int number;

    public Rule(int number) {
        this.number = number;
    }

    abstract <T> T apply(
            Function<LetterRule, ? extends T> fletter,
            Function<StandardRule, ? extends T> fstandard);

    static Rule parse(String line) {
        var parts = line.split(":");
        var number = Integer.parseInt(parts[0]);
        // System.out.println("Parsing " + line);
        var tmp = parts[1].split("\"");
        if (tmp.length > 1) {
            return new LetterRule(number, tmp[1].charAt(0));
        }
        List<List<Integer>> subs = new ArrayList<>();
        var current = new ArrayList<Integer>();
        for (var item : parts[1].trim().split("\\s")) {
            if ("|".equals(item)) {
                subs.add(current);
                current = new ArrayList<>();
            } else {
                current.add(Integer.parseInt(item));
            }
        }
        subs.add(current);
        return new StandardRule(number, subs);
    }


    static class LetterRule extends Rule {

        final char letter;

        private LetterRule(int number, char letter) {
            super(number);
            this.letter = letter;
        }

        @Override
        public String toString() {
            return String.format("%d: \"%c\"", number, letter);
        }

        @Override
        <T> T apply(Function<LetterRule, ? extends T> fletter,
                Function<StandardRule, ? extends T> fstandard) {
            return fletter.apply(this);
        }
    }

    static class StandardRule extends Rule {

        final List<List<Integer>> subs;

        private StandardRule(int number, List<List<Integer>> subs) {
            super(number);
            this.subs = subs;
        }

        @Override
        public String toString() {

            var r = subs.stream()
                    .map(numbers -> numbers.stream()
                    .map(v -> Integer.toString(v))
                    .collect(Collectors.joining(" ")))
                    .collect(Collectors.joining(" | "));
            return String.format("%d: %s", number, r);
        }

        @Override
        <T> T apply(Function<LetterRule, ? extends T> fletter,
                Function<StandardRule, ? extends T> fstandard) {
            return fstandard.apply(this);
        }
    }
}
