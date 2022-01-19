package handyhaversacks;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

/**
 * advent of code 2020 - Day 7.
 * @date   16 dec 2021
 * @author billaud
 */
public class HandyHaversacks {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
     
        part1("../small.txt");
        part1("../large.txt");
        
        part2("../small.txt");
        part2("../medium.txt");
        part2("../large.txt");
    }

    private static void part1(String filename) throws IOException {
        var regulations = new Regulations(filename);
        int nb = regulations.question1();
        System.out.format("Part 1, '%s' bag colors "
                + "can contain %d *shiny gold bags*\n",
                filename, nb);
    }

  private static void part2(String filename) throws IOException {
        var regulations = new Regulations(filename);
        int nb = regulations.question2();
        System.out.format("Part 2, '%s' a *shiny gold bag* " 
                + "contains %d bags\n",
                filename, nb);
    }

}
