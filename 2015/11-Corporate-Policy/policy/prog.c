/*
    Advent of Code 2015 - day 11
    michel billaud
    23 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

char is_forbidden(char c)
{
    return (c=='i') || (c=='o') ||(c=='l');
}

char next_char(char c)
{
    return c == 'z' ? 'a'
           : is_forbidden(c + 1) ? c + 2
           : c + 1;
}

bool has_straight(const char t[], int length)
{
    for (int i = 2; i < length; i++) {
        if ((t[i-2] + 1 == t[i-1])
                && (t[i-1] + 1 == t[i])) {
            return true;
        }
    }
    return false;
}

bool has_two_pairs(const char t[], int length)
{
    int first_pair_index = 0;
    for (int i = 1; i < length; i++) {
        if (t[i - 1] == t[i]) {
            first_pair_index = i;
            break;
        }
    }
    if (first_pair_index == 0) {
        return false;
    }
    char first_letter = t[first_pair_index];

    for (int i = first_pair_index + 2 ; i < length; i++) {
        if ((t[i-1] == t[i]) && (t[i] != first_letter) ) {
            return true;
        }
    }
    return false;
}

bool increment_password(char t[], int length)
{
    int index = length - 1;
    while ((index >= 0) && (t[index] == 'z')) {
        index--;
    }
    if (index < 0) return false;
    t[index] = next_char(t[index]);
    for (int i = index + 1; i < length; i++) {
        t[i] = 'a';
    }
    return true;
}

bool is_valid_password(char t[], int length)
{
    return has_straight(t, length)
           && has_two_pairs(t, length);
}


void clean_password(char password[], int length)
{
    // if password contains a forbidden letter
    // turn it into the next one,
    // and change following letters by a.
    bool found = false;
    for (int i = 0; i < length; i++) {
        if (found) {
            password[i] = 'a';
        } else if (is_forbidden(password[i])) {
            password[i] += 1;
            found = true;
        }
    }
}
void part1(const char old_password[])
{
    printf("# Part 1\n-  old: %s\n", old_password);
    char password[20];

    strcpy(password, old_password);
    int length = strlen(password);
    clean_password(password, length);
    do {
        if (!increment_password(password, length)) {
            printf("NOT FOUND\n");
            return;
        }
        // printf("- try: %s\n", password);
    } while (! is_valid_password(password, length));
    printf("- next: %s\n", password);

    // part 2
    do {
        if (!increment_password(password, length)) {
            printf("NOT FOUND\n");
            return;
        }
    } while (! is_valid_password(password, length));
    printf("- next: %s\n", password);
}


int main(int argc, char *argv[])
{
    printf("AOC 2015 - day 11\n");

    part1("abcdefgh");
    part1("ghijklmn");
    part1("hepxcrrq");

    return EXIT_SUCCESS;
}
