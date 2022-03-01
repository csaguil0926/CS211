#include <stdio.h>

int main(){
    
    printf("%u\n", (unsigned int) -1);
    //prints out 4294967295
    //casting to make signed int into unsigned int
    //not changing the actual bits, just changing what they represent
    //%u is for unsigned int
    printf("%x\n", (unsigned int) -1);
    //prints out ffffffff
    printf("%d\n", 4294967295U); //use U at end to make it signed int
    //prints out -1
    printf("%x\n", (signed int) 4294967295); //or explicitly cast to signed int
    //prints out ffffffff

    char s = -'A';
    unsigned char u = s;

    //%08x prints out hexidecimal with 8 spaces
    printf("%08x\n", s);
    //prints out ffffffbf
    printf("%08x\n", u);
    //prints out 000000bf

    return 0;
}