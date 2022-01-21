/*
 ! AOC 2017 - Day 7 
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package assembly;

import java.util.ArrayList;
import java.util.Scanner;

public class Instruction {

    final String destination;
    final Operation op;
    final Argument left, right;

    public Instruction(String destination, Operation op, Argument left, Argument right) {
        this.destination = destination;
        this.op = op;
        this.left = left;
        this.right = right;
    }

    public Instruction(String destination, Operation op, Argument left) {
        this(destination, op, left, null);
    }

    int execute(Context context) {
        int l = left.value(context);
        int r = (right == null) ? 0 : right.value(context);

        int result = op.apply(l, r) & 0xFFFF;
        context.env.put(destination, result);
        return result;
    }

    public static Instruction parse(String line) {
        Scanner s = new Scanner(line);
        var l = new ArrayList<String>();
        while (true) {
            var token = s.next();
            if ("->".equals(token)) {
                break;
            }
            l.add(token);
        }
        var destination = s.next();
        if (l.size() == 1) {
            return new Instruction(destination,
                    Operation.ASSIGN,
                    Argument.of(l.get(0)));
        } else if (l.get(0).equals("NOT")) {
            return new Instruction(destination,
                    Operation.NOT,
                    Argument.of(l.get(1)));
        } else {
            return new Instruction(destination,
                    Operation.valueOf(l.get(1)),
                    Argument.of(l.get(0)),
                    Argument.of(l.get(2)));
        }

    }

    @Override
    public String toString() {
        return "Instruction{" + "destination=" + destination + ", op=" + op + ", left=" + left + ", right=" + right + '}';
    }
    

}
