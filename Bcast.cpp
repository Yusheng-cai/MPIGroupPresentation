#include <iostream>
#include <sstream>
#include <mpi.h>


int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int root=0;
    int rank;
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    int data_size;
    if (rank == root)
    {
        std::stringstream ss(argv[1]);
        ss >> data_size;
    }

    MPI_Bcast(&data_size, 1, MPI_INT, root, MPI_COMM_WORLD);
    std::cout << "This is processor " << rank << ". The data size is " << data_size << std::endl;

    int* data = new int[data_size];

    // set the data to non-empty if we are on root
    if ( rank == root )
    {
        for (int i=0; i< data_size;i++)
        {
            data[i] = 1;
        }
    }

    // std::cout << "Before bcast, data = " << data << std::endl;

    MPI_Bcast(data, data_size, MPI_INT, root, MPI_COMM_WORLD);

    // std::cout << "After bcast, processor = " << rank << ", data = " << data << std::endl;

    delete[] data;
    MPI_Finalize();
}