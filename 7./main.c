#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day;
    char *stonk;
    float start_value;
    float end_value;
    int number;
    int is_match;  // ci to je ten spravny ticker ?
} Row;

int read_lines(char *buffer){
    // nacitanie riadku zo stdin
    if (fgets(buffer, 100, stdin)){
        buffer[strcspn(buffer, "\r\n")] = '\0';
        return 1;
    } else{
        return 0;
    }
}

void format_number(int num, char *output){
    // formatovanie cisla s podtrznikmi medzi trojicami
    char temp[20];
    sprintf(temp, "%d", num);
    int len = (int)strlen(temp);
    int pos = 0;

    for(int i=0; i < len; i++){
        if(i > 0 && (len - i) % 3 == 0){
            output[pos++] = '_';
        }
        output[pos++] = temp[i];
    }
    output[pos] = '\0';
}

// html - maximum uz mame vypocitane
void print_html(Row *rows, int total, const char *symbol, int max_idx){
    printf("<html>\n");
    printf("<body>\n");
    printf("<div>\n");

    if(max_idx != -1){
        char vol_str[30];
        format_number(rows[max_idx].number, vol_str);

        printf("<h1>%s: highest volume</h1>\n", symbol);
        printf("<div>Day: %d</div>\n", rows[max_idx].day);
        printf("<div>Start price: %.2f</div>\n", rows[max_idx].start_value);
        printf("<div>End price: %.2f</div>\n", rows[max_idx].end_value);
        printf("<div>Volume: %s</div>\n", vol_str);
    } else{
        printf("Ticker %s was not found\n", symbol);
    }

    printf("</div>\n");
    printf("<table>\n");
    printf("<thead>\n");
    printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf("</thead>\n");
    printf("<tbody>\n");

    // vypisanie tabulky odzadu
    for(int i = total - 1; i >= 0; i--){
        float diff = rows[i].end_value - rows[i].start_value;
        char vol_str[30];
        format_number(rows[i].number, vol_str);

        printf("<tr>\n");
        if(rows[i].is_match){
            // tucne pismo pre matchujuce tickery
            printf("\t<td><b>%d</b></td>\n", rows[i].day);
            printf("\t<td><b>%s</b></td>\n", rows[i].stonk);
            printf("\t<td><b>%.2f</b></td>\n", rows[i].start_value);
            printf("\t<td><b>%.2f</b></td>\n", rows[i].end_value);
            printf("\t<td><b>%.2f</b></td>\n", diff);
            printf("\t<td><b>%s</b></td>\n", vol_str);
        } else{
            printf("\t<td>%d</td>\n", rows[i].day);
            printf("\t<td>%s</td>\n", rows[i].stonk);
            printf("\t<td>%.2f</td>\n", rows[i].start_value);
            printf("\t<td>%.2f</td>\n", rows[i].end_value);
            printf("\t<td>%.2f</td>\n", diff);
            printf("\t<td>%s</td>\n", vol_str);
        }
        printf("</tr>\n");
    }

    printf("</tbody>\n");
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main(int argc, char *argv[]){
    // kontrola parametrov
    if(argc < 3){
        printf("Wrong parameters\n");
        return 1;
    }

    const char *symbol = argv[1];
    int n = atoi(argv[2]);

    // alokovanie pola
    Row *rows = (Row*)malloc(n * sizeof(Row));
    
    int total = 0;
    char line[100];

    int max_idx = -1;     // index maxima
    int max_volume = -1;  // hodnota maxima

    // nacitanie dat a hladanie maxima v jednom prechode
    for(int i=0; i < n && read_lines(line); i++){
        Row r;
        char temp_stonk[50];

        // parsovanie riadku
        // %[^,] - nacita retazec az do ciarky
        if(sscanf(line, "%d,%[^,],%f,%f,%d",
                  &r.day, temp_stonk, &r.start_value, &r.end_value, &r.number) == 5){
            r.stonk = (char*)malloc(strlen(temp_stonk) + 1);
            strcpy(r.stonk, temp_stonk);

            r.is_match = (strcmp(temp_stonk, symbol) == 0);

            // update maxima pre hladany ticker
            if(r.is_match && r.number > max_volume){
                max_volume = r.number;
                max_idx = total;
            }

            rows[total++] = r;
        }
    }

    // vypis html
    print_html(rows, total, symbol, max_idx);

    // uvolnenie pamate
    for(int i=0; i < total; i++){
        free(rows[i].stonk);
    }
    free(rows);

    return 0;
}