#include "drawing.h"
#include <stdio.h>

static void move_right_n(int n){ for(int i=0;i<n;i++) move_right(); }
static void move_left_n (int n){ for(int i=0;i<n;i++) move_left(); }
static void move_down_n (int n){ for(int i=0;i<n;i++) move_down(); }
static void move_up_n   (int n){ for(int i=0;i<n;i++) move_up(); }

void prerusovana_cara(int length){
    if(length <= 0) return;
    for(int i=0; i < length; i++){
        draw_pixel();
        if(i < length - 1){
            move_right();
            move_right();
        }
    }
}

void schody(int length){
    if(length <= 0) return;
    for(int i=0; i < length; i++){
        move_right(); 
        draw_pixel();
        move_down();
        draw_pixel();
        move_right();
        draw_pixel();
        move_down();
    }
}

void kvetinka(int wide, int length) {
    if (wide <= 0 || length <= 0) return;
    int side = (wide < length) ? wide : length;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int on_border = (i == 0 || j == 0 || i == side - 1 || j == side - 1); // sme na kraji ?
            if (on_border) {
                int p;
                if (i == 0) { // horny okraj 
                    p = j;
                } else if (j == side - 1) { // pravy okraj 
                    p = (side - 1) + i;
                } else if (i == side - 1) { //spodny okraj
                    p = (side - 1) + (side - 1) + (side - 1 - j);
                } else { // j == 0, lavy okraj 
                    p = (side - 1) + (side - 1) + (side - 1) + (side - 1 - i);
                }
                if ((p & 1) == 0) {
                    set_white_color();
                } else {                    // chceme striedat farby
                    set_black_color(); 
                }
            } else {
                set_yellow_color();
            }
            draw_pixel();
            if (j < side - 1) move_right();
        }
        for (int back = 0; back < side - 1; back++) {
            move_left();
        }
        if (i < side - 1) move_down();
    }
        int stem_len = wide - length; // vypocet dlzky stonky
        if (stem_len > 0) {
            int cx = side / 2;      // stred kvietku
            for (int r = 0; r < cx; r++) {   
                move_right(); 
            }
            move_down(); 
            for (int k = 0; k < stem_len; k++) { // kreslenie stonky
                set_green_color();
                draw_pixel();
                if (k < stem_len - 1){
                    move_down();
                } 
            }
        }
}

void kvetinka_animated(int wide, int length, int delay_ms){
    if (wide <= 0 || length <= 0) return;
    int side = (wide < length) ? wide : length;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int on_border = (i == 0 || j == 0 || i == side - 1 || j == side - 1);
            if (on_border) {
                int p;
                if (i == 0) {                
                    p = j;
                } else if (j == side - 1) {  
                    p = (side - 1) + i;
                } else if (i == side - 1) {  
                    p = (side - 1) + (side - 1) + (side - 1 - j);
                } else {                     
                    p = (side - 1) + (side - 1) + (side - 1) + (side - 1 - i);
                }
                if ((p & 1) == 0) set_white_color(); else set_black_color();
                draw_pixel();
                animate_ms(delay_ms);
            } 
            if (j < side - 1) move_right();
        }
        for (int back = 0; back < side - 1; back++) move_left();
        if (i < side - 1) move_down();
    }

    for (int up = 0; up < side - 1; up++) move_up();

    for (int i = 0; i < side; i++) { // vykreslujeme vnutro kvetinky animaciou
        for (int j = 0; j < side; j++) {
            int on_border = (i == 0 || j == 0 || i == side - 1 || j == side - 1);
            if (!on_border) {
                set_yellow_color();
                draw_pixel();
                animate_ms(delay_ms);
            }
            if (j < side - 1) move_right();
        }
        for (int back = 0; back < side - 1; back++) move_left();
        if (i < side - 1) move_down();
    }

    int stem_len = wide - length;
    if (stem_len > 0) {
        int cx = side / 2;
        for (int r = 0; r < cx; r++) move_right();
        move_down();
        for (int k = 0; k < stem_len; k++) {
            set_green_color();
            draw_pixel();
            animate_ms(delay_ms);
            if (k < stem_len - 1) move_down();
        }
    }
}

int main(){
    clear_screen();
    int drawing = 0;
    scanf("%d", &drawing);

    if (drawing == 0){
        set_red_color();    prerusovana_cara(10);
        move_down(); move_left();    
        set_blue_color();   prerusovana_cara(20);
        move_down(); move_left();
        set_green_color();  prerusovana_cara(8);
        move_down(); move_left();
        set_yellow_color(); prerusovana_cara(18);

    } else if (drawing == 1){
        set_blue_color();   schody(6);
        move_down_n(2); move_left_n(20);
        set_red_color();    schody(10);
        move_down_n(2); move_left_n(25);
        set_green_color();  schody(8);

    } else if (drawing == 2){
        kvetinka(8,5);
        move_down_n(4); move_right_n(3); kvetinka(4,3);
        move_right_n(3); kvetinka(5, 3);
        move_right_n(6); move_up_n(5); kvetinka(9, 5);
    } else if (drawing == 3){
        int rows = 2;
        int cols = 6;

        //parametre kvetu
        int wide   = 5;
        int length = 4;

        int side = (wide < length) ? wide : length;       //stvorec
        int cx   = side / 2;                               // posun do stredu (x)
        int stem = (wide > length) ? (wide - length) : 0;  //stonka

        int gap_x = 2;   // horizontalna medzera medzi kvetmi
        int gap_y = 2;   // vertikalna medzera medzi riadkami

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                kvetinka(wide, length);
                move_up_n(stem + (side - 1));
                move_left_n(cx);
                if (c < cols - 1) {
                    move_right_n(side + gap_x);
                }
            }
            if (r < rows - 1) {
                move_left_n((side + gap_x) * (cols - 1));    
                move_down_n(side + stem + gap_y);        
            }
        } 
    } else if (drawing == 4){
        kvetinka_animated(8, 5, 100);   
        move_right_n(2);
        kvetinka_animated(6, 4, 100);
    } else {
        printf("neznamy input");
    }

    end_drawing();
    return 0;
}
