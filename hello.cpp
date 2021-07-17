#include <iostream>
#include <mpi.h>

int main(int argc, char** argv)
{
    // The number of processors
    int size;

    // The "rank" of the processors
    int rank;

    // Initialize the MPI environment 
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    std::cout << "Hello world from rank " << rank << std::endl;

    MPI_Finalize();
}
