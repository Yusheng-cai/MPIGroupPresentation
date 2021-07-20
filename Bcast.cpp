#include <iostream>
#include <sstream>
#include <mpi.h>

void my_bcast(void* data, int count, MPI_Datatype type, int root, MPI_Comm communicator);

int main(int argc, char** argv)
{
    // Initialize MPI
    MPI_Init(&argc, &argv);
    int root=0;
    int rank;
    int size;

    // get the size & rank 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // get the data size from user input
    int data_size;
    if (rank == root)
    {
        std::stringstream ss(argv[1]);
        ss >> data_size;
    }

    // broadcast the number of data size to all the processors
    MPI_Bcast(&data_size, 1, MPI_INT, root, MPI_COMM_WORLD);

    int* data = new int[data_size];

    // set the data to non-empty if we are on root
    if ( rank == root )
    {
        for (int i=0; i< data_size;i++)
        {
            data[i] = 1;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double start = MPI_Wtime(); 
    MPI_Bcast(data, data_size, MPI_INT, root, MPI_COMM_WORLD);
    double end = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "End - start = " << end-start << " from rank " << rank << " for MPI_Bcast." << std::endl;


    MPI_Barrier(MPI_COMM_WORLD);

    start = MPI_Wtime();
    my_bcast(data, data_size, MPI_INT, root, MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "End - start = " << end-start << " from rank " << rank << " for my_bcast." << std::endl;

    delete[] data;

    MPI_Finalize();
}

void my_bcast(void* data, int count, MPI_Datatype type, int root, MPI_Comm communicator)
{
    int rank;
    int size;

    MPI_Comm_size(communicator, &size);
    MPI_Comm_rank(communicator, &rank);

    int recv_data;

    if ( rank == root )
    {
        for (int i =0; i< size; i++)
        {
            if (i != root)
                MPI_Send(data, count, type, i, 0, communicator);
        }
    }
    else 
    {
        MPI_Recv(data, count, type, root, MPI_ANY_TAG, communicator,MPI_STATUS_IGNORE);
    }
}