#include<stdio.h>

void div(int x, int y, int* res, int* rem){
    *res = x / y;
    *rem = x % y;

}

int main(){
    int res = 0;
    int rem = 0;
    div(13, 5, &res, &rem);
    printf("%d %d",res, rem);
    return 0;
}