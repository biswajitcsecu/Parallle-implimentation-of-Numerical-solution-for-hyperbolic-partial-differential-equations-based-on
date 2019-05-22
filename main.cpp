

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <mpi.h>


#define PI 3.142578

using namespace std;
using namespace MPI;


int main(int argc, char** argv) {
    
    try{
        int P, my_rank, i, j;
        int M = 50000;
        int M_p;
        int r;
        double local_norm2, global_norm2;
        double L = 30.0;
        double h;
        double t;
       
        MPI_Init(&argc, &argv);        
        MPI_Comm_size(MPI_COMM_WORLD, &P);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        
        // only the master process should read input 
        if (my_rank==0 && argc>1)
            M = atoi(argv[1]);
        
        //broadcast the length to the other processes        
        MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
        M_p = M/P;
        r = M%P;
        
        if (my_rank < P-1){
            r = 0;
        }
        
        //create the vector segment on this process 
        double* vector = (double*)malloc((M_p+r)*sizeof(double));       
        
        double nu = 0.0;
        
        double* u = (double*)malloc((M_p+r)*sizeof(double)); 
        // the solution
        double* uNew = (double*)malloc((M_p+r)*sizeof(double)); 
        // for updating
        double* F = (double*)malloc((M_p+r)*sizeof(double)); 
        
        h = (4*L/M);
        double uMax = 0.0;
        
        //initialize vector
        for (j = 0; j < M_p + r; j++) {            
            i = j + 1 + my_rank * M_p;
            vector[j]= sin(PI*i/2 + 0.25);       
        }
        
        // initial distribution
        for(i=0;i<M;i++){
            double x = i*h;
            u[i] = x + vector[i];
            
            if(abs(u[i]) > uMax)
                uMax = abs(u[i]);
        }
        
        // initiall condition
        t = h/uMax;
        std::cout<<"t = " << t << std::endl;
        int steps = 50000;
        int count = 0;
        
        while(count < steps){
            for( j=0; j<M; j++)
                F[j] = u[j]*u[j]/2.0;
            //inner loop
            for(j=0; j<M; j++){
                int jMinus1 = j > 0 ? j-1 : M-1;
                int jPlus1 = j < M-1 ? j+1 : 0;
                int jPlus2 = jPlus1 < M-1 ? jPlus1+1 : 0;
                uNew[j] =(u[j] + u[jPlus1] )/2.0 -
                        (t/(2.0*h))*(F[jPlus1]-F[j])+
                        (nu*t/(2.0*h*h))*((u[jPlus1]+u[jMinus1]-2.0*u[j])/2.0+
                        (u[jPlus2]+u[j]-2.0*u[jPlus1])/2.0);
                // end j loop
                for(j=0;j<M;j++) 
                    F[j] = uNew[j]*uNew[j]/2.0;
                
                for(j=0;j<M;j++){
                    int jMinus1 = j > 0 ? j - 1 : M-1;
                    int jPlus1 = j < M-1 ? j+1 : 0;
                    uNew[j] = u[j] - (t/h)*(F[j]-F[jMinus1]) +
                            (nu*t/(h*h))*(u[jPlus1]+u[jMinus1]-2.0*u[j]);
                }
                
                for(i=0;i<M;i++) 
                    u[i] = uNew[i];
                
                count++;
                
            } // end while
        }
        
        // vectore norm
        local_norm2 = 0.0;        
        for (j = 0; j < M_p+r; j++){
            local_norm2 += vector[j]*vector[j];
        }
        
         // Lax-Wenderoff PDE solution
        if (my_rank==0){
        MPI_Reduce( &uNew, &u, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);   
            for(i = 0; i< M; i++){
                std::cout<< "u[" << i << "] = " <<  u[i] << std::endl;
            }
        }
        else
        {
            MPI_Reduce(&local_norm2, &global_norm2, 1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
            printf("\nThe norm of v(i)= sin(5*i/PI + 2.25), i = (1,...., %d) is %g\n",
                    M, sqrt(global_norm2));  
        }
        
        // dealocate memory  
        free (vector);      
        MPI_Finalize();  
    
    }catch(...){
        
      exit(0);  
    }  
        
    return EXIT_SUCCESS;
}

