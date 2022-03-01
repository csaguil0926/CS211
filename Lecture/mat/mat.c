#include <stdio.h>
#include <stdlib.h>

void print_matrix(int n, double **m){

for (int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            printf("%6.2f", m[i][j]);
        }
        printf("\n");
    }
}

int main(){

    //FIXME comments are where i should be checking for errors like if the user enters something that isnt a number

    int n, fields;
    double **m;

    printf("Size of matrix?\n");
    fields = scanf("%d", &n); //FIXME
    if (fields != 1 || n < 1){
        puts("Not a correct number!");
        exit(1);
    }

    //dynamic allocation of double-pointer array
    //allocate space for the pointers
    m = malloc(sizeof(double*)*n); //FIXME
    for (int i = 0; i<n; ++i){
        m[i] = malloc(sizeof(double)*n); //allocating each row indepedently
    }

    /* alternatively we can also

    m[0]=malloc(sizeof(double)*n*n); //allocating all the rows as a single chunk
    for (int i = i; i<n; ++i){
        m[i] = m[0]+n; //pointers to the beginning of each row
    }

    */


    //reading data and storing in array
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            printf("(%d %d)?\n", i, j);
            //for double need to use long float in quotes
            fields = scanf("%lf", &m[i][j]); //FIX ME
            if (fields != 1){
                puts("Don't give me bad numbers");
                exit(1);
            }
        }
    }

    print_matrix(n, m);

    for(int i = 0; i<n; ++i){
        free(m[i]); //free each row seperately
    }
    free(m); //free whole thing

    /* for alternative way of allocating

    free(m[0]);
    free m;

    */

    return 0;
}