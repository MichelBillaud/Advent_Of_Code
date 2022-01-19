package passportprocessing;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;

public class PassportProcessing {

    public static void main(String[] args) throws IOException {
        part1("../small.txt");
        part1("../large.txt");
        
        
    }

    private static void part1(String filename) throws IOException {
        final Passport p = new Passport();
        int[] count = {0};
        Files.lines(Paths.get(filename))
                .forEach(line -> {
                    if (line.isBlank()) {
                        if (p.isValid()) {
                            count[0]++;
                        }
                        p.display();
                        p.clear();
                    } else {
                        for (var item : line.split(" ")) {
                            var tmp = item.split(":");
                            p.addItem(tmp[0], tmp[1]);
                        };

                    }
                }
                );
        if (p.isValid()) {
            count[0]++;
        }
        p.display();
        System.out.format("Part 1, file '%s' contains %d valid passports\n",
                filename, count[0]);
    }

    private static class Passport {

        HashMap<String, String> map = new HashMap<>();

        public Passport() {
        }

        private void display() {
            map.forEach((k, v) -> System.out.format("| %s -> %s\n", k, v));
            System.out.println(isValid());

        }

        private void clear() {
            map.clear();
        }

        boolean isEmpty() {
            return map.isEmpty();
        }

        private void addItem(String key, String value) {
            map.put(key, value);
        }

        private boolean isValid() {
            return map.size() == 8 || (map.size() == 7 && !map.containsKey("cid"));
        }
    }

}
