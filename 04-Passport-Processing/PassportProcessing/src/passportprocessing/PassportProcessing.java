package passportprocessing;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.function.Predicate;

public class PassportProcessing {

    public static void main(String[] args) throws IOException {
        // part1("../small.txt");
        // part1("../large.txt");    
       
        part2("../valid.txt");
        part2("../invalid.txt");
        part2("../small.txt");
        part2("../large.txt");
    }

    /* refactoring : old part1 turned into a function 
    counting valid passwords in a file.
    Extra parameter: a predicate for passport validation.
    
    part1 and part2 use specific predicates.
    */
    
    /**
     * Returns the number of valid passports in a file
     * @param filename
     * @param isValid    passport validity predicate
     * @return           number of valid passports found
     * @throws IOException 
     */
    private static int numberOfValidPassports(
            String filename,
            Predicate<Passport> isValid)
            throws IOException {
        int[] count = {0};
        final Passport p = new Passport();
        Files.lines(Paths.get(filename))
                .forEach(line -> {
                    if (line.isBlank()) {
                        if (isValid.test(p)) {
                            count[0]++;
                        }
                        // p.display();
                        p.clear();
                    } else {
                        for (var item : line.split(" ")) {
                            var tmp = item.split(":");
                            p.addItem(tmp[0], tmp[1]);
                        };
                    }
                }
                );
        // p.display()
        if (isValid.test(p)) {
            count[0]++;
        }
        return count[0];
    }

    private static void part1(String filename) throws IOException {
        System.out.format("Part 1, file '%s' contains %d valid passports\n",
                filename,
                numberOfValidPassports(filename, Passport::isValidForPart1));
    }

    private static void part2(String filename) throws IOException {
        System.out.format("Part 2, file '%s' contains %d valid passports\n",
                filename,
                numberOfValidPassports(filename, Passport::isValidForPart2));
    }

}
