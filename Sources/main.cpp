//-----------------------------------------------------------------------------------
//
//	Program main
//
//	Anton M. Krivtsov
//
//	08.11.2001
//
//-----------------------------------------------------------------------------------
#include <random>
#include <iostream>
#include "mpi.h"

void Run2D_Demo(const int iter, const int rank);

//-----------------------------------------------------------------------------------

int main()	// Please select one program from the following variants:
{
	MPI_Init(NULL, NULL);
	
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
   /* const int maxIters = 1;
    for(int i = 1; i <= maxIters; ++i)
    {
        Run2D_Demo(i, rank);
    }*/
     std::random_device rd;
	srand(rd() * time(0));
   	const int id = rand();
	Run2D_Demo(id, rank);
	
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank ==0){
		std::cout << "BARRIER!" << std::endl;
	}
	MPI_Finalize();
	return 0;
}

//-----------------------------------------------------------------------------------
