/*
 * (c) Michel Billaud
* Advent Of Code 2020 - Day21 - Allergic Assessment
 * michel.billaud@laposte.net
 */
package allergia;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.Set;
import java.util.stream.Collectors;


public class Allergia {

    final String filename;

    record Food(Set<String> ingredients, Set<String> allergens) {

    }
    final List<Food> foods = new ArrayList<>();

    public Allergia(String filename) throws IOException {
        this.filename = filename;
        var in = new Scanner(Paths.get(filename));
        while (in.hasNextLine()) {
            var line = in.nextLine();
            var ingredients = new HashSet<String>();
            var allergens = new HashSet<String>();
            var set = ingredients;
            for (var s : line.split("[\\p{Punct}\\s]+")) {
                if ("contains".equals(s)) {
                    set = allergens;
                } else {
                    set.add(s);
                }
            }
            foods.add(new Food(ingredients, allergens));
        }

    }

    void solve() {
        final Set<String> allIngredients = new HashSet<>();
        final Set<String> allAllergens = new HashSet<>();
        final Map<String, Set<Food>> foodByAllergen = new HashMap<>();

        // index data
        for (var food : foods) {
            allIngredients.addAll(food.ingredients);
            allAllergens.addAll(food.allergens);
        }
        for (var a : allAllergens) {
            foodByAllergen.put(a, new HashSet<>());
        }
        for (var food : foods) {
            for (var a : food.allergens) {
                foodByAllergen.get(a).add(food);
            }
        }

        // compute possibilities
        var possibilities = new HashMap<String, Set<String>>();
        for (var a : allAllergens) {
            System.out.format("%3d %s\n", foodByAllergen.get(a).size(), a);
            var interAllergens = new HashSet<String>(allAllergens);
            var interIngredients = new HashSet<String>(allIngredients);

            for (var food : foodByAllergen.get(a)) {
                interAllergens.retainAll(food.allergens);
                interIngredients.retainAll(food.ingredients);
            }
            possibilities.put(interAllergens.iterator().next(),
                    interIngredients);
            System.out.format("- %s %s\n", interAllergens, interIngredients);
        }
        // solve
        var ingredient_for = new HashMap<String, String>();
        while (!possibilities.isEmpty()) {
            System.out.println("-  start turn");
            var allergensFound = new HashSet<String>();
            var ingredientsFound = new HashSet<String>();
            possibilities.forEach((allergen, ingredients) -> {
                if (ingredients.size() == 1) {
                    var ingredient = ingredients.iterator().next();
                    System.out.format("- %s <-> %s\n", allergen, ingredient);
                    allergensFound.add(allergen);
                    ingredientsFound.add(ingredient);
                    ingredient_for.put(allergen, ingredient);
                }
            });
            possibilities.keySet().removeAll(allergensFound);
            possibilities.forEach((allergen, ingredients) -> {
                ingredients.removeAll(ingredientsFound);
            });
        }
        // count
        int count = 0;
        for (var food : foods) {
            var ingredients = new HashSet<>(food.ingredients);
            ingredients.removeAll(ingredient_for.values());
            count += ingredients.size();
        }
        System.out.format("- part 1 : %d ingredients without allergens\n", count);

        // part 2
        var list = ingredient_for.entrySet().stream()
                .sorted(Comparator.comparing(Entry::getKey))
                .map(Entry::getValue)
                .collect(Collectors.joining(","));
        System.out.format("- part 2 : %s\n", list);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        System.out.println("# Test");
        var small = new Allergia("../small.txt");
        small.solve();
        System.out.println("# Puzzle");
        (new Allergia("../puzzle.txt")).solve();
    }

}
