#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "header.h"
#include "main.h"

#include <unistd.h>  // for getcwd()

#define MAX_SIZE 100  // Define MAX_SIZE for reading from the file

int main(int argc, char **argv)
{
    int NB_MAX = 40;
    char CAR_FIN = '\n';
    int i, nbCar = 0;
    char word[NB_MAX], reverseWord[NB_MAX], car;
    bool areCharSame = true;

    /* Open file */
    FILE* myFile = NULL;
    char sentence[MAX_SIZE];
    myFile = fopen("./build/dictionnaire.txt", "r");
    
    if (myFile != NULL) {
        // Read each line from the file
        while(fgets(sentence, MAX_SIZE, myFile) != NULL) {
            
            // Tokenize the sentence into words
            char *wordPtr = strtok(sentence, " \n");
            while (wordPtr != NULL) {
                // Copy the current word to the word array
                strncpy(word, wordPtr, NB_MAX);
                nbCar = strlen(word);
                word[nbCar] = '\0';  // Ensure null termination

                // Reverse the word
                for (i = 0; i < nbCar; i++) {
                    reverseWord[i] = word[nbCar - 1 - i];
                }
                reverseWord[nbCar] = '\0';  // Null-terminate the reversed word

                // Check if the word is a palindrome
                areCharSame = true;
                for (i = 0; i < nbCar; i++) {
                    if (word[i] != reverseWord[i]) {
                        areCharSame = false;
                        break;
                    }
                }

                // Output result for the current word
                if (areCharSame) {
                    printf("The word \"%s\" is a palindrome\n", word);
                } /*else {
                    printf("The word \"%s\" is not a palindrome\n", word);
                }
                */
                // Move to the next word in the sentence
                wordPtr = strtok(NULL, " \n");
            }
        }
        fclose(myFile);
    } else {
        printf("Dictionnaire.txt cannot be opened\n");
    }

    return 0;
}