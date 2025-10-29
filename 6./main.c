#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void normalizeText(char *buff){
    int reading = 0; //pomocmne premene na pracu s riadkom  
    int writing = 0;
    int startedWord = 1;
    char lastChar = 0; //null
   

    while(buff[reading] != '\0'){
        char ch = buff[reading++];
        if(ch == ' '){
            //chcem odstranit medzeru
        }

        int isLetter = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')); // kontrola ci je pismeno (ASCII)
        
        if(isLetter){
            if(startedWord){
                if(ch >= 'a' && ch <= 'z'){
                    ch = ch - ('a' - 'A'); // zmena na velke pismeno
                    startedWord = 0;
                } else {
                    ch = ch;
                }
            } else {
                if(ch >= 'A' && ch <= 'Z'){
                    ch +=  ('a' - 'A'); // zmena na male pismeno
                }
            }

            if(lastChar != 0 && ch == lastChar){
                continue; //preskocenie duplikatu
            }

            buff[writing++] = ch;
            lastChar = ch; 
        } else {
            startedWord = 1; //nastavenie flagu na zaciatok noveho slova
            buff[writing++] = ch;
        }
    }
    buff[writing] = '\0'; 
}


int main(){
    int lowercase = 0;
    int uppercase = 0;
    int spaces = 0;
    int lowercaseAfter = 0;
    int uppercaseAfter = 0;
    int spacesAfter = 0;
    

    char n[2] = {0};
    fgets(n, sizeof n, stdin); 
    int num = atoi(n) + 1; //strategicky fix

    char buff[50] = {0};

    for (int i = 0; i < num; i++) {          
        if(!fgets(buff, 50, stdin)){
            break;
        }
        normalizeText(buff);
        puts(buff); 
        //statistiky radku
        printf("lowercase %d -> %d \n", lowercase, lowercaseAfter);
        printf("uppercase %d -> %d \n", uppercase, uppercaseAfter);
        printf("spaces %d -> %d \n", spaces, spacesAfter);
    }   
}