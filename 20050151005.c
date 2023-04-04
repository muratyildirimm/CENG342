
// Murat Duran Yıldırım 20050151005

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


void multiply(double **matrix,double *vector,double *output,int r,int c,int rank,int size){

    double *partial_output = (double *)malloc(r/size * sizeof(double));
    int i, j, first, end;

    first = rank * r/size;
    end = (rank + 1) * r/size;
   double start = MPI_Wtime();
    for(i = first; i<end; i++){
        double sum = 0.0;
        for(j=0; j<c; j++){
            sum += matrix[i][j]*vector[j];
        }
        partial_output[i-first] = sum;
    }

    MPI_Allgather(partial_output, r/size, MPI_DOUBLE, output, r/size, MPI_DOUBLE, MPI_COMM_WORLD);
 
     if(rank == 0){
        double end = MPI_Wtime();
        printf("\nElapsed time is %f seconds for parallel mxv with %d processes\n", end - start, size);
     }
    free(partial_output);
}

int main(int argc, char* argv[]) {

    int r=atoi(argv[1]);
    int c=atoi(argv[2]);

    double** matrix;
    double* output;
    double* vector;
    int i , j, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    matrix = (double**)malloc(r * sizeof(double*));
    for(i = 0; i < r; i++)
        matrix[i] = (double*)malloc(c * sizeof(double));

    vector = (double *)malloc(c * sizeof(double));
    output = (double *)malloc(r * sizeof(double));

    //seed random number of my id
    srand48(20050151005);
    
     for(j = 0; j<c; j++){
        // vector random
        vector[j] = ((double)rand() / RAND_MAX) * 20.0 + 1.0;;
    }

    for(i = 0; i<r; i++){
        for(j = 0; j<c; j++){
            // matrix random
            matrix[i][j]  = ((double)rand() / RAND_MAX) * 99.0 + 1.0;;
        }
    }

   // multiply matrix and vector

    multiply(matrix,vector,output,r,c,rank,size);
    MPI_Barrier(MPI_COMM_WORLD);
    
     if(rank == 0){
   
    FILE *file; 

    file = fopen(argv[3], "w");

           
    if (file == NULL) {
        printf("CANNOT OPEN.\n");
        return 1;
    }
    
    int k;
    fprintf(file, "%s\n", "output");
    for(k = 0; k<r ;k++){
    	// Write output 
    	fprintf(file, "%.2lf\n", output[k]);
}
  
    fclose(file);
}

    free(matrix);
    free(vector);
    free(output);

    MPI_Finalize();

    return 0;
}

