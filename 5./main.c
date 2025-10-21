#include <stdio.h>
#include <stdlib.h>

/* funkcie pohybu 
*   r, c - riadok, stlpec
*   rows, cols - rozmer mriezky
*/

void turtle_right(int *r , int *c, int rows, int cols){
    *c = (*c + 1) % cols;
}
void turtle_left(int *r, int *c, int rows, int cols){
    *c = (*c - 1 + cols) % cols;
}
void turtle_up(int *r, int *c, int rows, int cols){
    *r = (*r - 1 + rows) % rows;
}
void turtle_down(int *r, int *c, int rows, int cols){
    *r = (*r + 1) % rows;
}

/*
*   indexovanie: [i, j] -> i * cols + j
*   
*/
void print_array(const char *pole, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", pole[i * cols + j]);
        }
        printf("\n");
    }
}

int main(void){
    int rows = 0, cols = 0;
    scanf("%d %d", &rows, &cols); // rozmer mriezky

    char *pole = malloc(rows * cols); //dynamicky alokovana pamat

    for (int i = 0; i < rows * cols; i++){
         pole[i] = '.';
    }

    int n = 1; //pocet aktivnych korytnaciek
    int r1 = 0, c1 = 0, dir1 = 0; //poloha a smer prvej korytnacky
    int r2 = 0, c2 = 0, dir2 = 0; //druha korytnacka
    int r3 = 0, c3 = 0, dir3 = 0; // tretia korytnacka

     /*
     *  prikazy:
     *   'x' -> print mriezky a ukoncenie programu
     *   'f' -> pridanie dalsej korytnacky maximalne 3
     *   'r' -> smer doprava (dir = (dir+1)%4)
     *   'l' -> smer dolava (dir = (dir+3)%4)
     *   'm' -> posunutie korytnaciek podla ich smeru
     *   'o' -> '.' <-> 'o'
     */
    char cmd;
    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'x') {
            print_array(pole, rows, cols);
            free(pole);
            return 0;
        }
        if (cmd == 'f') { //pridanie korytnaciek
            if (n < 3) {
                n++;
                if (n == 2) { r2 = 0; c2 = 0; dir2 = 0; } //inicializacia dalsej korytnacky
                if (n == 3) { r3 = 0; c3 = 0; dir3 = 0; }
            }
            continue;
        }
        if (cmd == 'r') { //doprava
            if (n >= 1) dir1 = (dir1 + 1) % 4; 
            if (n >= 2) dir2 = (dir2 + 1) % 4;
            if (n >= 3) dir3 = (dir3 + 1) % 4;
            continue;
        }
        if (cmd == 'l') { //dolava
            if (n >= 1) dir1 = (dir1 + 3) % 4;
            if (n >= 2) dir2 = (dir2 + 3) % 4;
            if (n >= 3) dir3 = (dir3 + 3) % 4;
            continue;
        }
        if (cmd == 'm') { //pohyb vsetkych aktivnych o 1
            if (n >= 1) {
                if (dir1 == 0){ 
                    turtle_right(&r1, &c1, rows, cols); 
                } else if (dir1 == 1) {
                    turtle_down(&r1, &c1, rows, cols);
                } else if (dir1 == 2){ 
                    turtle_left(&r1, &c1, rows, cols);
                } else {
                    turtle_up(&r1, &c1, rows, cols);
                }
            }
            if (n >= 2) {
                if (dir2 == 0) {
                    turtle_right(&r2, &c2, rows, cols);
                } else if (dir2 == 1) {
                     turtle_down(&r2, &c2, rows, cols);
                } else if (dir2 == 2) { 
                    turtle_left(&r2, &c2, rows, cols);
                } else  {
                    turtle_up(&r2, &c2, rows, cols);
                }
            }
            if (n >= 3) {
                if (dir3 == 0) {
                    turtle_right(&r3, &c3, rows, cols);
                } else if (dir3 == 1) { 
                    turtle_down(&r3, &c3, rows, cols);
                } else if (dir3 == 2) {
                    turtle_left(&r3, &c3, rows, cols);
                } else {
                    turtle_up(&r3, &c3, rows, cols);
                }
            }
            continue;
        }

        if (cmd == 'o') { // z bodky na o
            if (n >= 1) {
                int id1 = r1 * cols + c1; //pozicia v poli
                pole[id1] = (pole[id1] == '.') ? 'o' : '.';
            }
            if (n >= 2) {
                int id2 = r2 * cols + c2;
                pole[id2] = (pole[id2] == '.') ? 'o' : '.';
            }
            if (n >= 3) {
                int id3 = r3 * cols + c3;
                pole[id3] = (pole[id3] == '.') ? 'o' : '.';
            }
            continue;
        }
    }

    //uvolnenie pamate
    free(pole);
    return 0;
}