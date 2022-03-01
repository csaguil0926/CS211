#include <stdio.h>
#include <ctype.h>

void tooMuchMem(int MEMSIZE){ //client requesting more than MEMSIZE
    printf("You are requesting too much memory. You can request at most %d bytes.", MEMSIZE);
    return;
}

int main(int argc, char **argv) {

    char* str = argv[1];
    
    for (int i = 0; str[i]!='\0'; i++){

        int c;

        c=str[i];

        if (islower(c)){
            str[i]=toupper(c);
        }

    }
    
    if (str[0]=='\0'){
        printf ("%s", str);
    } else{
        printf ("%s!!\n", str);
    }

    tooMuchMem(5);

    
    
    return (0);
  
}