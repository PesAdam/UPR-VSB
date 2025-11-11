#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int day;
    char stonk[50];
    float start_value;
    float end_value;
    int number;
} Row;

int read_lines(char *buffer){
    if (fgets(buffer, 100, stdin)){
        buffer[strcspn(buffer, "\r\n")] = '\0'; // remove newline
        return 1;
    } else{
        return 0;
    }
}

void print_html_stats(const Row *row, int count)
{
    float diff = row->end_value - row->start_value;

    printf("<html>\n");
    printf(" <body>\n");
    printf(" <div>\n");
    printf(" <h1>%s: highest volume</h1>\n", row->stonk);
    printf(" <div>Day: %d</div>\n", row->day);
    printf(" <div>Start price: %.2f</div>\n", row->start_value);
    printf(" <div>End price: %.2f</div>\n", row->end_value);
    printf(" <div>Volume: %d</div>\n", row->number);
    printf(" </div>\n");

    printf(" <table>\n");
    printf(" <thead>\n");
    printf(" <tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf(" </thead>\n");
    printf(" <tbody>\n");

    for (int i = 0; i < count; ++i) {
        float diff = row[i].end_value - row[i].start_value;
        printf(" <tr><td>%d</td><td>%s</td><td>%.2f</td><td>%.2f</td><td>%.2f</td><td>%d</td></tr>\n",
            row[i].day, row[i].stonk, row[i].start_value, row[i].end_value, diff, row[i].number);
    }


    printf(" </tbody>\n");
    printf(" </table>\n");
    printf(" </body>\n");
    printf("</html>\n");
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Wrong parameters\n");
        return 1;
    }

    const char *symbol = argv[1];  
    int n = atoi(argv[2]);        
    Row *rows = malloc(n * sizeof(Row)); 
    int  total = 0;                        
    int *match_idx = malloc(n * sizeof(int)); 
    int  mcount = 0;                           

    char line[100];

    for (int i = 0; i < n && read_lines(line); ++i) {
        Row r;
        if (sscanf(line, "%d,%49[^,],%f,%f,%d",
                &r.day, r.stonk, &r.start_value, &r.end_value, &r.number) == 5) {

            rows[total] = r;                 
            if (strcmp(r.stonk, symbol) == 0) {
                match_idx[mcount++] = total; 
            }
            total++;
        }
    }

    print_html_stats(rows, mcount);

    return 0;
}
