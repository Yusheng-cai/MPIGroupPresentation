MPICC=/usr/local/bin/mpicc
MPICXX=/usr/local/bin/mpic++

all: hello

hello.out: hello.cpp
	${MPICXX} hello.cpp -o hello

BlockingComm.out: BlockingComm.cpp
	${MPICXX} BlockingComm.cpp -o BlockingComm

MyBcast.out: MyBcast.cpp
	${MPICXX} MyBcast.cpp -o MyBcast.out

Bcast.out: Bcast.cpp
	${MPICXX} Bcast.cpp -o Bcast.out

