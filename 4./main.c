#include <stdio.h>

//funkcia na ratanie poctu cislic
int pocet(int n){
    int i;
    for(i=0; n != 0 || i == 0; i++) n /= 10;
    return i;
}

// horizontalny histogram
void horizontal_hist(const int *hist, int m, int invalid ){
    int sirka = pocet(m+8);
    for(int i=0; i < 9; i++){
        printf("%*d", sirka, m + i);
        for(int j=0; j < hist[i]; j++){
            if(j == 0){
                printf(" #");
            }else{
                printf("#");
            }
        }
        printf("\n");
    }
    if(invalid >= 1){
        printf("invalid: ");
        for (int x = 0; x < invalid; x++) {
            printf("#");
        }
        printf("\n");
    }
}

// vertikalny histogram
void vertical_hist(const int *hist, int m, int invalid){

}

int main(){
    int n = 0; // udava pocet z kolkatich bude pocitany histogram
    int m = 0; // udava rozsah m + 8
    int hist[9] = {0};
    int invalid = 0;
    char ch;
    
    scanf(" %c", &ch);
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        int idx = x - m;
        if (idx >= 0 && idx < 9) {
            hist[idx]++;
        } else {
            invalid++;
        }
    }
    
    if(ch == 'h'){
        horizontal_hist(hist, m, invalid);
    } else if (ch == 'v'){
    
    } else {
        printf("Neplatny mod vykresleni\n");
        return 1;
    }
    
    return 0;
}