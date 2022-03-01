#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//from mexp
double** multiplyMatrix(double **mat1, double **mat2, int mr1, int mc1, int mc2){

    double **solution = (double**)malloc(mr1*sizeof(double*));
    for(int i = 0; i<mr1; i++){
        solution[i]= (double*)malloc(mc2*sizeof(double));
    }

    for(int i = 0; i<mr1; i++){
        for(int j = 0; j<mc2; j++){
            solution[i][j]=0;
            for(int k = 0; k<mc1; k++){
                solution[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return solution;
}

//from mexp
void printMatrix(double **matrix, int row, int col){
    for(int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            printf("%.0lf\n",matrix[i][j]);
        }
    }
}

double ** transposeMatrix(double** matrix, int row, int col){

    double **transMat = (double**)malloc(col*sizeof(double*));
    for(int i = 0; i<col; i++){
        transMat[i]= (double*)malloc(row*sizeof(double));
    }

    //switch baby switch
    for (int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            transMat[j][i]=matrix[i][j];
        }
    }
    return transMat;
}

//procedure invert(m: n by n matrix)
double ** invert(double ** matrix, int size){
    
    //make identity matrix
    double **identitymatrix = (double**)malloc(size*sizeof(double*));
    for(int i = 0; i<size; i++){
        identitymatrix[i]= (double*)malloc(size*sizeof(double));
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

    double f;
    //for p ←0, 1, ··· , n −1
    for(int p = 0; p<size; p++){
        //f ←Mp,p
        f = matrix[p][p];
        //divide Mp by f
        //divide Np by f
        for(int q = 0; q<size; q++){
            matrix[p][q]/=f;
            identitymatrix[p][q]/=f;
        }

        //for i ←p + 1, ··· , n −1
        for (int i = p+1; i<size; i++){
            // f←Mi,p
            f = matrix[i][p];
            //subtract Mp ×f from Mi
            //subtract Np ×f from Ni
            for(int j = 0; j<size; j++){
                matrix[i][j] -= (matrix[p][j] * f);
                identitymatrix[i][j] -= (identitymatrix[p][j] * f);
            }
        } 
    }
    
    //for p ←n −1, ··· , 0
    for(int p = size -1; p>=0; p--){
        //for i ←p −1, ··· , 0
        for(int i = p-1; i>=0; i--){
            // f←Mi,p
            f = matrix[i][p];
            //subtract Mp ×f from Mi
            //subtract Np ×f from Ni
            for(int j = 0; j<size; j++){
                matrix[i][j] -= (matrix[p][j] * f);
                identitymatrix[i][j] -= (identitymatrix[p][j] * f);
            }
        }
    }
    return identitymatrix;
}


int n;//n is row in n by m matrix
int m;//m is col in n by m matrix
double **matX;
double **matY;

void scanFile(FILE* file){
    char *typefile = (char*)malloc(6*sizeof(char)); //largest amount should be 6 bc train has 5 char + terminator
    fscanf(file, "%5s", typefile);
    fscanf(file, " %d", &m);
    m++; //add 1 for 1 col in index 0 of matX
    fscanf(file, " %d", &n);

    matX = (double**)malloc(n*sizeof(double));
    for(int i = 0; i<n; i++){
        matX[i]= (double*)malloc(m*sizeof(double));
    } //matx = 7x5

    matY= (double**)malloc(n*sizeof(double));
    for(int i = 0; i<n; i++){
        matY[i]= (double*)malloc(1*sizeof(double));
    } //maty = 7x1

    if(strcmp(typefile, "train") == 0){
        free(typefile);
        for(int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                if(j==0){
                    matX[i][j]=1.0;
                }else{
                    fscanf(file, " %lf", &matX[i][j]);
                }
            }
            
            fscanf(file, " %lf", &matY[i][0]);
        }
    }else if(strcmp(typefile, "data") == 0){
        free(typefile);
        for(int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                if(j==0){
                    matX[i][j]=1.0;
                }else{
                    fscanf(file, " %lf", &matX[i][j]);
                }
            }
        }
    }else{
        free(typefile);
        printf("invalid input my dude\n");
        exit(1);
    }
    return;
}

int main(int argc, char**argv){

    FILE *train = fopen(argv[1], "r");
    scanFile(train);

    double ** transmatX = transposeMatrix(matX, n, m); //X^T
    double ** squaremat = multiplyMatrix(transmatX, matX, m, n, m); //(X^T*X)
    double ** inversemat = invert(squaremat, m);//(X^T*X)^-1
    double ** multmat = multiplyMatrix(inversemat, transmatX, m, m, n);//((X^T*X)^-1)*X^T
    double ** matW = multiplyMatrix(multmat, matY, m, n, 1);//W=((X^T*X)^-1)*X^T*Y

    //free stuff i redefine when i scan data
    for(int i = 0; i<n; i++){
        free(matX[i]);
    }
    free(matX);

    for(int i = 0; i<n; i++){
        free(matY[i]);
    }
    free(matY);

    int traink = m;

    FILE *data = fopen(argv[2], "r");
    scanFile(data);

    int datak = m;

    if (traink != datak){ //checking if train and data specify same val k
        printf("error\n");
        exit(1);
    }

    double ** pricemat = multiplyMatrix(matX, matW, n, m, 1);

    printMatrix(pricemat, n, 1);

    //free galore
    for(int i = 0; i<m; i++){
        free(transmatX[i]);
    }
    free(transmatX);

    for(int i = 0; i<m; i++){
        free(squaremat[i]);
    }
    free(squaremat);

    for(int i = 0; i<m; i++){
        free(inversemat[i]);
    }
    free(inversemat);

    for(int i = 0; i<m; i++){
        free(multmat[i]);
    }
    free(multmat);
    
    for(int i = 0; i<m; i++){
        free(matW[i]);
    }
    free(matW);

    for(int i = 0; i<n; i++){
        free(matX[i]);
    }
    free(matX);

    for(int i = 0; i<n; i++){
        free(matY[i]);
    }
    free(matY);

    for(int i = 0; i<n; i++){
        free(pricemat[i]);
    }
    free(pricemat);

    return 0;

}