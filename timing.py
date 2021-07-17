import os 
import time
import sys

if __name__ == "__main__":
    exe = sys.argv[1]
    num_times = int(sys.argv[2])
    
    s = time.time()
    for i in range(num_times):
        os.system("{}".format(exe))
    e = time.time()

    print("Average time it took for this executable is {:.3f}".format((e-s)/num_times))  
