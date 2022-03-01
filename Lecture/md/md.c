#include <stdio.h>

int main(){

    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    m[1][-1] = 800; //m[1] gives second row of array, then [-1] is the number earlier so it changes 3 in the array

    int *p;

    p = &m[1][1]; //pointing at 5

    p[-1] = 99; //[-1] makes it go one before it changing the 4 to 99

    m[0][3] = 100; // [0] gives first row of array but the index only goes up to 2 so 3 gives the first item in the next row
    //changes 4 to 100

    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            printf("%4d", m[i][j]); //print out a number with # spaces to the right of it
            //to make it left alligned "%-4d"
        }
        printf("\n");
    }

    return 0;
}