MPICC=mpicc
MPICXX=mpic++

all: hello.out BlockingComm.out Bcast.out MyBcast.out

hello.out: hello.cpp
	${MPICXX} hello.cpp -o hello

BlockingComm.out: BlockingComm.cpp
	${MPICXX} BlockingComm.cpp -o BlockingComm

Bcast.out: Bcast.cpp
	${MPICXX} Bcast.cpp -o Bcast.out

