/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package assembly;

import java.util.function.IntBinaryOperator;

/**
 *
 * @author billaud
 */
public enum Operation {
    ASSIGN((l, r) -> l),
    AND((l, r) -> l & r),
    OR((l, r) -> l | r),
    LSHIFT((l, r) -> l << r),
    RSHIFT((l, r) -> l >> r),
    NOT((l, r) -> ~l);

    IntBinaryOperator op;

    private Operation(IntBinaryOperator op) {
        this.op = op;
    }
    
    public int apply(int l, int r) {
        return op.applyAsInt(l, r);
    }

}
