#include <iostream>
#include <mpi.h>

void my_bcast(void* data, int count, MPI_Datatype type, int root, MPI_Comm communicator);


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

    my_bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);

    // std::cout << "After bcast, processor = " << rank << ", data = " << data << std::endl;

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