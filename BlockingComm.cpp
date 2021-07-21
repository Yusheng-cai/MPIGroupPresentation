#include <iostream>
#include <mpi.h>

int main(int argc, char** argv)
{
    int size;
    int rank;


    MPI_Init(&argc, &argv);

    // The status struct used by the receiver
    MPI_Status stat;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int NUM_BUFFER=3;
    int root_rank=0;

    // contiguous array of data (important)
    int sent_number[NUM_BUFFER];
    int receive_buffer[NUM_BUFFER];

    if ( rank == 0 ) 
    {
        for (int i=1; i<size; i++)
        {
            for (int j=0;j<NUM_BUFFER;j++)
            {
                sent_number[j] = i;
            }
            MPI_Send(&sent_number, NUM_BUFFER, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&receive_buffer, NUM_BUFFER, MPI_INT, root_rank, rank, MPI_COMM_WORLD, &stat);
        std::cout << "This is rank " << rank << ". The error code is "  << stat.MPI_ERROR << std::endl;

        for (int k = 0; k< NUM_BUFFER; k++)
        {
            std::cout << receive_buffer[k] << std::endl;
        }
    }

    MPI_Finalize();
}