#include <stdio.h>

int main(){

    char c = 0xFF; // 255
    //this in binary is 111111111
    //char is signed unless you explicity write unsigned char
    //therefore 255 = -1
    //if (char c is less than 0) returns true

    unsigned char uc = 0xFF; //print out as 255 and would interpret it as non negative value
    //any unsigned value can never be 0

    printf("%d\n", c);
    printf("%d\n", uc);

    if (c<0){
        puts("It is negative! Whoooa!");
    }

    if (uc>0){
        puts("It is not negative! Whoooa!");
    }
    
    return 0;
}