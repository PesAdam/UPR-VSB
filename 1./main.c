#include<stdio.h>

int x;
int j; 
int i;

int main() {    
    x = 8600; //penazie
    j = (x / 100) * 100; // zaokruhlenie penazi na 100

    int hodnoty_bankovky[] = {5000, 2000, 1000, 500, 200, 100}; //nase bankovky
    int z; //pocet bankoviek

    for(i=0; i < 6; i++){
        z = j / hodnoty_bankovky[i];
        j = j % hodnoty_bankovky[i]; 
        printf("Bankovka %d: %dx\n", hodnoty_bankovky[i], z);
    }
    return 0;
}