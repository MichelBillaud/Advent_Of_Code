/*
	Ce programme imite, en gros, le script

	for word in $* ; do 
	   echo "Data: " word
	   echo -n "$word" | md5sum
	done

	Le but : mettre en oeuvre les fonctions md5
	Bilan;
	   - creer un contexte
	   - s'en servir pour mouliner les bouts du message 
	   - y récuperer le digest

	Compilation : utiliser libcrypto
	     gcc proc.c -lcrypto
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

void display_md5(const char string[])
{
    printf("Data: %s\n", string);
    unsigned char digest[MD5_DIGEST_LENGTH];
    compute_md5(string, digest);
    printf("Digest: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        display_md5(argv[i]);
    }
    return EXIT_SUCCESS;
}
