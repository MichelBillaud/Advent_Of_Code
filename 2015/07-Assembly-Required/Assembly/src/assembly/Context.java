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
public class Context {
    final Map<String, Instruction> code; 
    final Map<String, Integer> env;

    public Context(Map<String, Instruction> code, Map<String, Integer> env) {
        this.code = code;
        this.env = env;
    }
   
    int value(String name) {
        Integer result = env.get(name);
        if (result == null) {
            result = code.get(name).execute(this);
        }
        return result;
    }

  
   
}
