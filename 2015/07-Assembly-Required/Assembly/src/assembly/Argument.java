/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package assembly;

import java.util.Map;

/**
 *
 * @author billaud
 */
public abstract class Argument  {

    abstract int value(Context context);

    static class Variable extends Argument {

        final String name;

        public Variable(String name) {
            this.name = name;
        }

        @Override
        public int value(Context context) {
            return context.value(name);
        }
    }

    static class Constant extends Argument {

        final int value;

        public Constant(int value) {
            this.value = value;
        }

        @Override
        public int value(Context context) {
            return value;
        }
    }
    
    public static Argument of(String string) {
        try {
        return new Constant(Integer.parseInt(string));
        } catch(NumberFormatException ex) {
            return new Variable(string);
        }
    }
}
