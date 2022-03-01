#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){
    
    char* str = argv[1];
    
    int ogLength = strlen(str);

    for (int i = 0; i < ogLength; i++){
        int c;
        c = str[i];
        if (isdigit(c)){
            printf("error\n");
            break;
        }else {
            continue;
        }
    }
    
    char* compressedString = (char*) malloc((2*ogLength)+1);
    char* buffer = (char*) malloc((2*ogLength)+1);

    int buflen = strlen(str);

    char prev = str[0];
    int counter = 1;
    int j = 0;

    for (int i = 1; i<ogLength; i++){
        if (prev == str[i]){
            counter++;
        } else {
            sprintf(buffer, "%c%d", prev, counter);
            strcat(compressedString, buffer);
            for(int i = 0; i<buflen; i++){
                j++;
            }
            prev = str[i];
            counter = 1;
        }
    }
    sprintf(buffer, "%c%d", prev, counter);
    strcat(compressedString, buffer);
    for(int i = 0; i<buflen; i++){
        j++;
    }
    compressedString[j]='\0';

    int newLength = strlen(compressedString);
    
    if (newLength > ogLength){
        printf("%s\n", str);
    } else {
        printf("%s\n", compressedString);
    }

    free(compressedString);
    free(buffer);

    return (0);
}
