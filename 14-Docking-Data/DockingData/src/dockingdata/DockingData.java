/*
 * Advent Of Code 2020 - Day 14 - Docking Data  
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package dockingdata;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

public class DockingData {

    static final Pattern MASK_PATTERN = Pattern.compile("mask = ([01X]*)");
    static final Pattern MEM_PATTERN = Pattern.compile("mem\\[(\\d+)\\] = (\\d+)");

    public static void main(String[] args) throws IOException {

        tests();
        part1("../small.txt");
        part1("../large.txt");
        part2("../second.txt");
        part2("../large.txt");
    }

    private static void tests() {
        System.out.println("# tests");
        System.out.println("Variantes de 33");
        long or_mask = 18;
        for (var v : variants(33)) {
            System.out.println("-> " + v + " " + Long.toBinaryString(v));
        }
    }

    private static void part1(String filename) throws IOException {
        System.out.format("# Part 1, %s\n", filename);
        var memory = new HashMap<Integer, Long>();

        try (java.util.Scanner in = new Scanner(Paths.get(filename))) {
            long and_mask = 0, or_mask = 0;
            while (in.hasNextLine()) {
                var line = in.nextLine();
                var m = MASK_PATTERN.matcher(line);
                if (m.matches()) {
                    String mask = m.group(1);
//                    System.out.format("mask\t%s\n", mask);
                    and_mask = 0;
                    or_mask = 0;
                    for (var c : mask.toCharArray()) {
                        and_mask <<= 1;
                        or_mask <<= 1;
                        if (c == '1') {
                            or_mask |= 1;
                        }
                        if (c != '0') {
                            and_mask |= 1;
                        }
                    }
//                    System.out.format("- and = %s, or = %s\n", 
//                           Long.toBinaryString(and_mask),
//                           Long.toBinaryString(or_mask));
//                           
                    continue;
                }
                m = MEM_PATTERN.matcher(line);
                if (m.matches()) {
                    int address = Integer.parseInt(m.group(1));
                    long value = Long.parseLong(m.group(2));
//                   System.out.format("mem\t%d\t%d\n", address, value);
                    final long result = (value & and_mask) | or_mask;
//                    System.out.format("- value %d\n", result); 
                    memory.put(address, result);
                    continue;
                }
                System.out.format("BAD LINE IGNORED %s\n", line);
            }
        }
        Long sum = memory.values().stream()
                .reduce(0L, (a, b) -> a + b);
        System.out.format("- Sum for %s = %d\n", filename, sum);
        System.out.println();
    }

    private static void part2(String filename) throws IOException {
        System.out.format("# Part 2, %s\n", filename);
        var memory = new HashMap<Long, Long>();

        try (java.util.Scanner in = new Scanner(Paths.get(filename))) {
            long floating_mask = 0, or_mask = 0;
            while (in.hasNextLine()) {
                var line = in.nextLine();
                var m = MASK_PATTERN.matcher(line);
                if (m.matches()) {
                    String mask = m.group(1);
//                    System.out.format("mask\t%s\n", mask);
                    floating_mask = 0;
                    or_mask = 0;
                    for (var c : mask.toCharArray()) {
                        floating_mask <<= 1;
                        or_mask <<= 1;
                        if (c == '1') {
                            or_mask |= 1;
                        }
                        if (c == 'X') {
                            floating_mask |= 1;
                        }
                    }
//                    System.out.format("- floating = %s, or = %s\n",
//                            Long.toBinaryString(floating_mask),
//                            Long.toBinaryString(or_mask));

                    continue;
                }
                m = MEM_PATTERN.matcher(line);
                if (m.matches()) {
                    long address = Integer.parseInt(m.group(1));
                    long value = Long.parseLong(m.group(2));
//                    System.out.format("mem\t%d\t%d\n", address, value);
                    for (long variant : variants(floating_mask)) {
                        var addr = (address & ~floating_mask)
                                | variant | or_mask;
//                        System.out.format("- addr %d := %d\n", addr, value);
                        memory.put(addr, value);
                    }
                    continue;
                }
                System.out.format("BAD LINE IGNORED %s\n", line);
            }
        }
        Long sum = memory.values().stream()
                .reduce(0L, (a, b) -> a + b);
        System.out.format("- Sum for %s = %d\n", filename, sum);
        System.out.println();
    }

    private static List<Long> variants(long floating_mask) {
        if (floating_mask == 0) {
            return List.of(0L);
        }
        var list = new ArrayList<Long>();
        for (long v : variants(floating_mask >> 1)) {
            list.add(v << 1);
            if ((floating_mask & 1) == 1) {
                list.add(v << 1 | 1);
            }
        }
        return list;

    }
}
