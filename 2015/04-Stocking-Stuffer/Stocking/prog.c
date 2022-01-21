/*
    Advent of Code 2015 - Day 4 - parts 1 and 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/md5.h>
#include <string.h>

void compute_md5(const char string[],
                 unsigned char digest[MD5_DIGEST_LENGTH] )
{
    MD5_CTX	context;
    MD5_Init(&context);
    MD5_Update(&context, string, strlen(string));
    MD5_Final(digest, &context);
}

void part1(const char string[])
{
    printf("# Part 1\n- Data: %s\n", string);
    for (int decimal=1; decimal > 0; decimal++) {
        char input[20];
        sprintf(input, "%s%d", string, decimal);
        unsigned char digest[MD5_DIGEST_LENGTH];
        compute_md5(input, digest);
        if ((digest[0] | digest[1] | (digest[2] & 0xF0)) == 0) {
                    printf("- Answer: %d\n", decimal);
                    return;
                } 
        }
    printf("- Not found\n");
}

void part2(const char string[])
{
    printf("# Part 2\n- Data: %s\n", string);
    for (int decimal=1; decimal > 0; decimal++) {
        char input[20];
        sprintf(input, "%s%d", string, decimal);
        unsigned char digest[MD5_DIGEST_LENGTH];
        compute_md5(input, digest);
        if ((digest[0] | digest[1] | digest[2]) == 0) {
                    printf("- Answer: %d\n", decimal);
                    return;
                } 
        }
    printf("- Not found\n");
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        part1(argv[i]);
        part2(argv[i]);   
    }
    return EXIT_SUCCESS;
}
