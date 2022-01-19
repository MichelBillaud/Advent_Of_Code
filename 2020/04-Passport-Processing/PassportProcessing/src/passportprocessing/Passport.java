package passportprocessing;

import java.util.HashMap;
import java.util.List;
import java.util.regex.Pattern;

public class Passport {

    HashMap<String, String> map = new HashMap<>();

    public Passport() {
    }

    void display() {
        map.forEach((k, v) -> System.out.format("| %s -> %s\n", k, v));
    }

    void clear() {
        map.clear();
    }

    boolean isEmpty() {
        return map.isEmpty();
    }

    void addItem(String key, String value) {
        map.put(key, value);
    }

    // --- part 1
    //
    boolean isValidForPart1() {
        return map.size() == 8 || (map.size() == 7 && !map.containsKey("cid"));
    }

    // --- part 2
    //
    boolean isValidForPart2() {
        List<String> mandatoryFields
                = List.of("byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid");
        if (!map.keySet().containsAll(mandatoryFields)) {
            return false;
        }

        var valid = valid_byr(map.get("byr"))
                && valid_iyr(map.get("iyr"))
                && valid_eyr(map.get("eyr"))
                && valid_hgt(map.get("hgt"))
                && valid_hcl(map.get("hcl"))
                && valid_ecl(map.get("ecl"))
                && valid_pid(map.get("pid"));
        // System.out.println("validite = " + valid);
        return valid;
    }

    private boolean valid_byr(String string) {
        // four digits; at least 1920 and at most 2002.
        return numberBetween(string, 1920, 2002);
    }

    private boolean valid_iyr(String string) {
        // four digits; at least 2010 and at most 2020.
        return numberBetween(string, 2010, 2020);
    }

    private boolean valid_pid(String string) {
        // a nine-digit number, including leading zeroes.
        return string.matches("\\d{9}");
    }

    private boolean valid_eyr(String string) {
        // four digits; at least 2020 and at most 2030.
        return numberBetween(string, 2020, 2030);
    }

    static final Pattern CM_PATTERN = Pattern.compile("(\\d+)cm");
    static final Pattern IN_PATTERN = Pattern.compile("(\\d+)in");

    private boolean valid_hgt(String string) {
        /*        a number followed by either cm or in:
    If cm, the number must be at least 150 and at most 193.
    If in, the number must be at least 59 and at most 76.
         */
        var cm = CM_PATTERN.matcher(string);
        if (cm.matches()) {
            return numberBetween(cm.group(1), 150, 193);
        }
        var in = IN_PATTERN.matcher(string);
        if (in.matches()) {
            return numberBetween(in.group(1), 59, 76);
        }
        return false;
    }

    private boolean valid_hcl(String string) {
        // a # followed by exactly six characters 0-9 or a-f.
        return string.matches("#[0-9a-f]{6}");
    }

    private boolean valid_ecl(String string) {
        // exactly one of: amb blu brn gry grn hzl oth.
        return string.matches("amb|blu|brn|gry|grn|hzl|oth");
    }

    // auxiliary string validation functions
    //
    private static boolean numberBetween(String string, int min, int max) {
        if (!string.matches("\\d+")) {
            return false;
        }
        int value = Integer.parseInt(string);
        return min <= value && value <= max;
    }
}
