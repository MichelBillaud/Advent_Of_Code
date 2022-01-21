/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package assembly;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Assembly {

    final Map<String, Instruction> code;
    final String filename;

    public Assembly(String filename) throws IOException {
        this.filename = filename;
        code = new HashMap<>();
        Scanner in = new Scanner(Paths.get(filename));

        while (in.hasNextLine()) {
            String line = in.nextLine();
            var instruction = Instruction.parse(line);
            code.put(instruction.destination, instruction);
        }
        // code.forEach((dest, inst) -> System.out.format("%s: %s\n",dest,inst));

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        var small = new Assembly("../small.txt");
        small.part1();
        var puzzle = new Assembly("../puzzle.txt");
        puzzle.part1();
        puzzle.part2();

    }

    private void part1() {
        System.out.format("# Part 1 (%s)\n", filename);

        var env = new HashMap<String, Integer>();
        var context = new Context(code, env);
        /*
        for (var d : code.keySet()) {
            System.out.format("%s: %s\n", d, context.value(d));
        }
         */
        Integer result = env.get("a");
        System.out.format("- value of 'a' is %s\n", result);
    }

    private void part2() {
        System.out.format("# Part 1 (%s)\n", filename);

        var env1 = new HashMap<String, Integer>();
        var context1 = new Context(code, env1);
        Integer a = context1.value("a");
        System.out.format("- value of 'a' in first context is %s\n", a);

        var env2 = new HashMap<String, Integer>();
        var context2 = new Context(code, env2);

        // override value of b
        env2.put("b", a);

        // new value for a ?
        Integer a2 = context2.value("a");

        System.out.format("- value of 'a' in second context is %s\n", a2);

    }
}
