#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void normalizeText(char *buff, int *lowercase, int *uppercase, int *spaces, int *lowercaseAfter, int *uppercaseAfter, int *spacesAfter){
    int reading = 0;
    int writing = 0;
    int startedWord = 1;
    char lastChar = 0;
    int hadSpaces = 0;

    *lowercase = 0;
    *uppercase = 0;
    *spaces = 0;
    *lowercaseAfter = 0;
    *uppercaseAfter = 0;
    *spacesAfter = 0;

    buff[strcspn(buff, "\r\n")] = '\0';

    for (int i = 0; buff[i] != '\0'; ++i) {
        char ch = buff[i];
        if (ch == ' ') (*spaces)++;
        else if (ch >= 'a' && ch <= 'z') (*lowercase)++;
        else if (ch >= 'A' && ch <= 'Z') (*uppercase)++;
    }

    int wordInfoReady = 0;      
    int wordAllLower  = 0;      // slovo ma vsetky pismenka male
    int wordHasLetter = 0;      // slovo obsahuje pismeno
    int firstLetterDone = 0;    

    while (buff[reading] != '\0'){
        char ch = buff[reading++];

        if (ch == ' '){
            hadSpaces = 1;
            startedWord = 1;
            lastChar = 0;
            // reset per-word stavov
            wordInfoReady = 0;
            firstLetterDone = 0;
            continue;
        }

        // JEDNA medzera len na ZACIATOK ďalsieho slova
        if (hadSpaces && writing > 0 && startedWord) {
            buff[writing++] = ' ';
            (*spacesAfter)++;
            hadSpaces = 0;
        }

        // na zaciatku slova zistime ci je cele male alebo obsahuje velke
        if (startedWord && !wordInfoReady){
            int k = reading - 1;
            int hasU = 0, hasL = 0;
            while (buff[k] && buff[k] != ' ') {
                char c2 = buff[k];
                if (c2 >= 'A' && c2 <= 'Z') hasU = 1;
                else if (c2 >= 'a' && c2 <= 'z') hasL = 1;
                k++;
            }
            wordAllLower  = (hasL && !hasU);
            wordHasLetter = (hasL || hasU);
            wordInfoReady = 1;
            firstLetterDone = 0;
        }

        int isLetter = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));

        if (isLetter && wordHasLetter){
            if (wordAllLower){
                // cele upperCase
                if (ch >= 'a' && ch <= 'z') ch = (char)(ch - ('a' - 'A'));
            } else {
               // prve velke a ostatne male (pismenka)
                if (!firstLetterDone){
                    if (ch >= 'a' && ch <= 'z') ch = (char)(ch - ('a' - 'A'));
                    firstLetterDone = 1;
                } else {
                    if (ch >= 'A' && ch <= 'Z') ch = (char)(ch + ('a' - 'A'));
                }
            }

            startedWord = 0;       

            if (lastChar != 0 && ch == lastChar){
                continue; 
            }

            buff[writing++] = ch;
            lastChar = ch;
            if (ch >= 'a' && ch <= 'z') (*lowercaseAfter)++;
            else if (ch >= 'A' && ch <= 'Z') (*uppercaseAfter)++;
        } else {
            // neni pismenko alebo slovo nema pismenka
            buff[writing++] = ch;
            startedWord = 1;
            lastChar = 0;
            //reset
            wordInfoReady = 0;
            firstLetterDone = 0;
        }
    }
    buff[writing] = '\0';
}


int main(){
   
    char n[32] = {0};
    fgets(n, sizeof n, stdin); 
    int num = atoi(n); //strategicky fix

    char buff[51] = {0};
    
    for (int i = 0; i < num; i++) {          
        if(!fgets(buff, sizeof buff, stdin)){
            break;
        }
        buff[strcspn(buff, "\r\n")] = '\0'; // odstranenie novoradkovych znakov

        // normalizeText(buff, &lowercase, &uppercase, &spaces, &lowercaseAfter, &uppercaseAfter, &spacesAfter);
        int lcB, ucB, spB, lcA, ucA, spA;
        normalizeText(buff, &lcB, &ucB, &spB, &lcA, &ucA, &spA);
       
        //statistiky radku
        puts(buff); 
        printf("lowercase: %d -> %d\n",  lcB, lcA);
        printf("uppercase: %d -> %d\n", ucB, ucA);
        printf("spaces: %d -> %d\n", spB, spA);

        if (i != num - 1) putchar('\n');   // prazdny riadok medzi blokmi
    }   
}