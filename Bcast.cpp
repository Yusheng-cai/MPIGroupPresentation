#include <iostream>
#include <mpi.h>


int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data;
    int root=0;


    // set the data to non-empty if we are on root
    if ( rank == root )
    {
        data = 1;
    }

    // std::cout << "Before bcast, data = " << data << std::endl;

    MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);

    // std::cout << "After bcast, processor = " << rank << ", data = " << data << std::endl;

    MPI_Finalize();
}