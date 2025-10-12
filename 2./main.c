#include<stdio.h>

int main(){
    int obrazec = 0; 
    int a = 0;
    int b = 0;

    scanf("%d%d%d", &obrazec, &a, &b);

    if(obrazec == 0){ //stvorec
        for(int i=0; i < b; i++){
            for(int j=0; j < a; j++){
                printf("x");
            }
            printf("\n");
        }
    } else if (obrazec == 1){ //duty stvorec
          for(int i=1; i <= b; i++){
            for(int j=1; j <= a; j++){
                if(j==1 || j==a || i == 1 || i == b){
                    printf("x");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if (obrazec == 2 ){ //stvorec s cislami
        int k=0;
         for(int i=1; i <= b; i++){
            for(int j=1; j <= a; j++){
                if(j==1 || j==a || i == 1 || i == b){
                    printf("x");
                } else {
                    if (k==10){
                        k=0;
                    }
                    printf("%d", k);
                    k++;
                }
            }
            printf("\n");
        }
    } else if (obrazec == 3){ //diagonala
        for(int i=1; i <= a; i++){
            for(int j=2; j <= i; j++){ //zaciname 2 kvoli testom aby sme nevypisovali prvy symbol medzeru
                printf(" ");
            }
            printf("x");
            printf("\n");
        }
    } else if (obrazec == 4) { //diagonala naopak
        for(int i=1; i <= a; i++){
            for(int j=a-1; j >= i; j--){ 
                printf(" ");
            }
            printf("x");
            for (int j=0; j < i-1; j++) {
                printf(" ");
            }
            printf("\n");
        }
    } else if (obrazec == 5){ //trojuholnik
        int sirka = 1;
        for(int i=1; i <= a; i++){ 
            for(int j=1; j <= a-i; j++){ 
                printf(" ");
            } 
            if(i==1){
                printf("x");
                for(int k = i; k < a ; k++){
                    printf(" ");
                }
            } else if(i==a){
                for (int j=1; j <= sirka; j++) {
                    printf("x");
                }
            } else {
                printf("x");
                for (int j=1; j <= sirka-2; j++) {
                    printf(" ");
                }
                printf("x");
                for(int k = i; k < a ; k++){
                    printf(" ");
                }
            }
            printf("\n");
            sirka += 2;
        }
    } else if (obrazec == 6){ //T
          for(int i=1; i <= b; i++){
            if(i == 1){
                for(int j=1; j <= a; j++){
                    printf("x");
                }
            } else {
                for(int j=1; j <= a/2; j++){
                    printf(" ");
                }
                printf("x");
            }
            printf("\n");
        }
    } else if (obrazec == 7){ //P
        for(int i=1; i <= b; i++){
            if(i==1 || i == (b/2 + 1)){
                for(int j=1; j <= a; j++){
                    printf("x");
                }
            } else if(i > 1 && i <= b/2){
                printf("x");
                for(int j=1; j <= a-2; j++){
                    printf(" ");
                }
                if(a>1){
                    printf("x");
                }
            }else{
                printf("x");
                for (int j=1; j <= a-1; j++){
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if (obrazec == 9){ //stvorec s cislami bonus
         for(int i=1; i <= b; i++){
            for(int j=1; j <= a; j++){
                if(j==1 || j==a || i == 1 || i == b){
                    printf("x");
                } else {
                    printf("%d", (((j - 2) * (b - 2)) + (i - 2)) % 10); //b-2 vyska vnutra, i-2 riadok vnutorneho pola, 
                                                                        // j-2 stlpec vo vnutornom poli, 
                }
            }
            printf("\n");
        }
    } else {
        printf("Neznamy obrazec\n");
    }    
}