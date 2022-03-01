#include<stdio.h>    
#include<stdlib.h>  

int** multiplyMatrix(int **mat1, int **mat2, int size){
    
    int **solution = (int**)malloc(size*size*sizeof(int*));
    for(int i = 0; i<size; i++){
        solution[i]= (int*)malloc(size*sizeof(int));
    }
    
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            solution[i][j]=0;
            for(int k = 0; k<size; k++){
                solution[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return solution;
}

void** printMatrix(int **matrix, int size){
    for(int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if (j != 0){
                printf(" ");
            }
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i<size; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

void** printIdentityMatrix(int size){

    int **identitymatrix = (int**)malloc(size*size*sizeof(int*));
    for(int i = 0; i<size; i++){
        identitymatrix[i]= (int*)malloc(size*sizeof(int));
    }

    for(int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if(i==j){
                identitymatrix[i][j]=1;
            }else{
                identitymatrix[i][j]=0;
            }
        }
    }

    printMatrix(identitymatrix, size);

    for(int i = 0; i<size; i++){
        free(identitymatrix[i]);
    }
    free(identitymatrix);
    return 0;
}


int main(int argc, char**argv){
    
    FILE *ptr = fopen(argv[1], "r");

    int k;
    int n;

    fscanf(ptr, " %d", &k);
    
    int **ogmatrix = (int**)malloc(k*k*sizeof(int*));
    for(int i = 0; i<k; i++){
        ogmatrix[i]= (int*)malloc(k*sizeof(int));
    }

    for(int i = 0; i<k; i++){
        for (int j = 0; j<k; j++){
            fscanf(ptr, " %d", &ogmatrix[i][j]);
        }
    }
    fscanf(ptr, " %d", &n);

    if(n==0){
        printIdentityMatrix(k);
    }else if (n==1){
        printMatrix(ogmatrix, k);
    }else if (n==2){
        int **solmatrix = multiplyMatrix(ogmatrix, ogmatrix, k);
        printMatrix(solmatrix, k);
    }else{
        int **solmatrix = multiplyMatrix(ogmatrix, ogmatrix, k);
        int **matrix2 = solmatrix;
        for(int i = 3; i <= n; i++){
            solmatrix = multiplyMatrix(matrix2, ogmatrix, k);
            matrix2 = solmatrix;
        }
        printMatrix(solmatrix, k);
        
    }
    
    for(int i = 0; i<k; i++){
            free(ogmatrix[i]);
        }
        free(ogmatrix);
    return 0;
}