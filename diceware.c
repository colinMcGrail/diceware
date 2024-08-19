#define SYNTAXMESSAGE "Bad syntax \n Usage: diceware <wordcount>"
#define ENTROPYMESSAGE "/dev/random could not be opened. Try pressing a bunch of buttons before trying again."
#define ARGMESSAGE "Please enter an integer number of words greater than one.\n Usage: diceware <wordcount>"

#define WORDS _binary_wd_start

#include <stdio.h>
#include <stdlib.h>

void wordgen(void);

FILE* devrandom;

int
main(int argc, char** argv)
{
    long wordcount;
    long i;

    if (argc != 2){
        fprintf(stderr, SYNTAXMESSAGE);
        return -1;
    }
    
    if ((wordcount = strtol(argv[1], 0, 0)) <= 0){
        fprintf(stderr, ARGMESSAGE);
        return -1;
    }

    devrandom = fopen("/dev/random", "r");

    if(devrandom == NULL){
        fprintf(stderr, ENTROPYMESSAGE);
        return -1;
    }

    for(i = 0; i < wordcount; i++){
        wordgen();
        if (i < wordcount - 1){
            fputc('-', stdout);
        }
    }

    return 1;
}

unsigned int genNum(){
    extern FILE* devrandom;
    unsigned int randomNumber;

    fread(&randomNumber, sizeof(unsigned int), 1, devrandom);
    return (randomNumber % 7776);
}


void wordgen(){
    int rand;
    int i;
    extern char WORDS[];
    
    rand = (genNum() * 6);
    for(i = 0; i < 6 && WORDS[rand + i] != '\0'; i++){
        fputc(WORDS[rand + i], stdout);
    }
}
