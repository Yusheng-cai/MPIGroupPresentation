MPICC=mpicc
MPICXX=mpic++

all: hello.out BlockingComm.out Bcast.out HeatEquationSerial.out 

hello.out: hello.cpp
	${MPICXX} hello.cpp -o hello

BlockingComm.out: BlockingComm.cpp
	${MPICXX} BlockingComm.cpp -o BlockingComm.out

Bcast.out: Bcast.cpp
	${MPICXX} Bcast.cpp -o Bcast.out

HeatEquationSerial.out: HeatEquationSerial.cpp
	${MPICXX} HeatEquationSerial.cpp -o HeatEquationSerial.out
