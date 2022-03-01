#include <stdio.h>

int main(){

    //100 prints out normal decimal because it doesn't start with something to signify it's a base of smth
    //start with 0 means octal
    //start with 0x means hexidecimal
    printf("%d\t%d\t%d\n", 100, 0100, 0x100);

    if (0100 == 64){
        printf("weird!\n");
    }

    //printing out as hexidecimals when using %x
    //100 prints out 64 because 100 = 6(16) + 4 -> 4 -> 6 = 0(16) + 6 -> 64
    //6 16's + 4 = 100
    //0100 = 40 because it means that there are 4 16's in 64
    // 4 16's + 0 = 64
    //0x100 prints out 100 bc hexidecimal 100 = hexidecimal 100
    printf("%x\t%x\t%x\n", 100, 0100, 0x100);

    //prints out as octal using %o
    //100 decimal converts to 144 octal bc 
    //100 = 12(8) + 4 -> 4 -> 12 = 1(8) + 4 -> 44 -> 1 = 0(8) + 1 -> 144
    //0100 print out 100 bc octal 100 = octal 100
    //0x100 hexadecimal or 256 decimal converts to 400 bc
    //256 = 32(8) + 0 -> 0 -> 32 = 4(8) + 0 -> 00 -> 4 = 0(8) + 4 -> 400
    printf("%o\t%o\t%o\n", 100, 0100, 0x100);

    printf("%d\n", 0xFF); //prints out 48879
    printf("%x\n", 48879); //prints out beef

    char x = 0;
    char y = '0';
    char z = '\0';

    if (x!=y&&x==z){
        puts ("true");
    }else{
        puts("false");
    }

    return 0;

}