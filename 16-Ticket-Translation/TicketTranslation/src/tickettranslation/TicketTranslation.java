package tickettranslation;

/* 
    Advent of Code 2020 - Day 16 - Ticket Translation
    Michel Billaud, 30 dec 2021
*/ 
import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class TicketTranslation {

    final Pattern RULE_PATTERN = Pattern.compile("^([^:]+):\\s+"
            + "(\\d+)-(\\d+)"
            + "\\s+or\\s+"
            + "(\\d+)-(\\d+)$");
    final String filename;

    record Interval(int first, int last) {

        boolean contains(int value) {
            return (first <= value && value <= last);
        }
    }

    record Rule(String name, Interval... intervals) {

        boolean contains(int value) {
            for (var interval : intervals) {
                if (interval.contains(value)) {
                    return true;
                }
            }
            return false;
        }
    }

    record Ticket(ArrayList<Integer> fields) {

    }

    final List<Rule> rules = new ArrayList<>();
    final int nbFields;
    final Ticket your_ticket;
    final List<Ticket> nearby_tickets;

    // for part 1
    boolean isValidFieldValue(int value) {
        for (var rule : rules) {
            for (var inter : rule.intervals()) {
                if (inter.contains(value)) {
                    return true;
                }
            }
        }
        return false;
    }

    Optional<Integer> invalidField(Ticket ticket) {
        for (var f : ticket.fields()) {
            if (!isValidFieldValue(f)) {
                return Optional.of(f);
            }
        }
        return Optional.empty();
    }

    Ticket parseTicket(String line) {
        return new Ticket(Arrays.asList(line.split(",")).stream()
                .map(Integer::parseInt)
                .collect(Collectors.toCollection(ArrayList::new)));
    }

    public TicketTranslation(String filename) throws IOException {
        this.filename = filename;
        Scanner in = new Scanner(Paths.get(filename));
        while (true) {
            var line = in.nextLine().trim();
            if (line.isEmpty()) {
                break;
            }
            var matcher = RULE_PATTERN.matcher(line);
            if (matcher.matches()) {
//                System.out.format("-> %s\n", matcher.group(1));
                rules.add(new Rule(matcher.group(1),
                        new Interval(Integer.parseInt(matcher.group(2)),
                                Integer.parseInt(matcher.group(3))),
                        new Interval(Integer.parseInt(matcher.group(4)),
                                Integer.parseInt(matcher.group(5)))));
            }
        }
        nbFields = rules.size();
        in.nextLine();

        your_ticket = parseTicket(in.nextLine());

        nearby_tickets = new ArrayList<>();
        in.nextLine(); // empty
        in.nextLine(); // title
        while (in.hasNextLine()) {
            nearby_tickets.add(parseTicket(in.nextLine()));
        }

    }

    private void part1() {
        System.out.format("# Part 1, %s\n", filename);
        int scanning_error_rate = nearby_tickets.stream()
                .map(this::invalidField)
                .filter(Optional::isPresent)
                .mapToInt(Optional::get)
                .sum();
        System.out.format("- scanning error rate = %s\n", scanning_error_rate);
        System.out.println("");
    }

    private void part2() {
        System.out.format("# Part 2, %s\n", filename);
        List<Ticket> validTickets = nearby_tickets.stream()
                .filter(t -> invalidField(t).isEmpty())
                .collect(Collectors.toList());

        final ArrayList<HashSet<Rule>> constraints = new ArrayList<>();

        for (int field = 0; field < nbFields; field++) {
            var vr = new HashSet<>(rules);
            for (var v : validTickets) {
                final int f = field;
                vr.removeIf(rule -> !rule.contains(v.fields.get(f)));
            }
            constraints.add(vr);
        }
        // -----------------------------------

//        for (int field = 0; field < rules.size(); field++) {
//            System.out.format("- field %d \t", field);
//            constraints.get(field).forEach(r -> System.out.print(r.name + ", "));
//            System.out.println("");
//        }
        // resolution
        // pour un rang, une seule regle
        // pour une regle, un seul rang
        resolution(constraints);
    }

    private void resolution(final ArrayList<HashSet<Rule>> originalConstraints) {
        final var constraints = originalConstraints.stream()
                .map(HashSet::new)
                .toList();

        var unknownFields = IntStream.range(0, rules.size()).boxed()
                .collect(Collectors.toSet());
        for (boolean progress = true; progress;) {
            progress = false;
//            System.out.println("--- Résolution");

            var fieldsFound = unknownFields.stream()
                    .filter(f -> constraints.get(f).size() == 1)
                    .toList();
            if (!fieldsFound.isEmpty()) {
                progress = true;

//                System.out.println("--- Found");
//                for (int f : fieldsFound) {
//                    System.out.format("%d -> %s\n", f,
//                            constraints.get(f).iterator().next().name());
//                }
                var rulesFound = fieldsFound.stream()
                        .map(constraints::get)
                        .map(set -> set.iterator().next())
                        .toList();

                unknownFields.removeAll(fieldsFound);

//           System.out.println("--- Simplified");
                for (int f : unknownFields) {
                    constraints.get(f).removeAll(rulesFound);
                }
//                System.out.println("");
            };
        }
        List<Integer> departureFields = IntStream.range(0, nbFields)
                .filter(f -> constraints.get(f).iterator().next().name().startsWith("departure"))
                .boxed()
                .toList();
        System.out.println("- departure fields: " + departureFields);
        var departureValues = departureFields.stream()
                .map(your_ticket.fields::get)
                .toList();
        System.out.println("- departure values: " + departureValues);
        var product = IntStream.range(0, nbFields)
                .filter(f -> constraints.get(f)
                        .iterator().next().name().startsWith("departure"))
                .mapToLong(your_ticket.fields::get)
                .reduce(1L, (a, b) -> a * b);
        System.out.println("- final result: " + product);

    }

    public static void main(String[] args) throws IOException {
        var small = new TicketTranslation("../small.txt");
        small.part1();
//        small.part2();
        var large = new TicketTranslation("../large.txt");
        large.part1();
        large.part2();
    }

}
