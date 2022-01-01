/*
 * (c) Michel Billaud
 * michel.billaud@laposte.net
 */
package fr.mbillaud.chineseremainder;

public class FrMbillaudChineseRemainder {

    /**
     * @param args the command line arguments
     */
    static long[] euclide(long a, long b) {
        if (b == 0) {
            long[] r = {a, 1, 0};
            return r;
        } else {
            var tmp = euclide(b, a % b);
            var u = tmp[1];
            var v = tmp[2];
            tmp[1] = v;
            tmp[2] = u - (a / b) * v;
            return tmp;
        }
    }

    static long inverse(long a, long mod) {
        var tmp = euclide(a, mod);
        return Math.floorMod(tmp[1], mod);
    }

    public static void main(String[] args) {
        test1();
        test2();

    }

    private static void test1() {
        // There are certain things whose number is unknown.
        // If we count them by threes, we have two left over;
        // by fives, we have three left over;
        // and by sevens, two are left over.
        // How many things are there?

        int size = 3;
        long[] packets = {3, 5, 7};
        long[] remainders = {2, 3, 2};

        long r = smallestChineseResult(packets, size, remainders);

        System.out.format("smallest -> %d\n", r);
    }

    private static void test2() {

        int size = 5;
        long[] ids = {7, 13, 59, 31, 19};
        long[] delays = {0, 1, 4, 6, 7};
        long[] remainders = {0, 12, 55, 25, 12};
        
        long r = smallestChineseResult(ids, size, remainders);

        System.out.format("smallest timestamp -> %d\n", r);
    }

    private static long smallestChineseResult(long[] packets, int size, long[] remainders) {
        int n = 1;
        for (var p : packets) {
            n *= p;
        }
        long sum = 0;
        for (int i = 0; i < size; i++) {
            long nn = n / packets[i];
            long inv = inverse(nn, packets[i]);
            sum += remainders[i] * inv * nn;
        }
        var r = sum % n;
        return r;
    }

}
