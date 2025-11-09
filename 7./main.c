#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_lines(char *line){
    fgets(line, 100, stdin);
    line[strcspn(line, "\r\n")] = '\0'; // remove newline
}

void print_html_stats(int day, char stonk, float start_value, float end_value, int number){
    printf("<html>\n");
    printf("<head><title>Stock Report</title></head>\n");
    printf("<body>\n");
    printf("<h1>Stock Report for Day %d</h1>\n", day);
    printf("<p>Stock: %c</p>\n", stonk);
    printf("<p>Start Value: %.2f</p>\n", start_value);
    printf("<p>End Value: %.2f</p>\n", end_value);
    printf("<p>Number of Transactions: %d</p>\n", number);
    printf("</body>\n");
    printf("</html>\n");
}

int contains_stonk(char *line, char stonk) {
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] == stonk) {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Wrong parameters \n");
        return 1;
    }

    int n = atoi(argv[2]);
    char line[100];

    for(int i = 0; i < n; i++) {
        read_lines(line);
        int day = atoi(&line[0]);

        char stonk = line[1];
        if(!contains_stonk(line, stonk)) {
            printf("No transactions for stock %c on day %d\n", stonk, day);
            continue;
        } else {
            printf("Transactions found for stock %c on day %d\n", stonk, day);
        }
    
    }
    
    return 0;
}