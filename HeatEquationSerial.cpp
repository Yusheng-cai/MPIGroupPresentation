#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

template<typename T>
T** allocMemory(int rows, int cols);

template<typename T>
void deallocMemory(T** ptr);

void initializeTemp(double** TEMP, double TEMP_MAX, int N);

void solve(double** TEMP, double** TEMP_, int N, double tol, int max_iter);

int main(int argc, char** argv)
{
    std::stringstream ss;
    int N;
    ss << argv[1];
    ss >> N;    

    double** TEMP = allocMemory<double>(N,N);
    double** TEMP_ = allocMemory<double>(N,N);

    // Set the maximum temperature
    double TEMP_MAX=100;

    initializeTemp(TEMP, TEMP_MAX, N);
    initializeTemp(TEMP_, TEMP_MAX, N);

    double tol = 0.01;
    int max_iter = 4000;

    solve(TEMP, TEMP_, N, tol, max_iter);

    deallocMemory(TEMP);
    deallocMemory(TEMP_);
};

template<typename T>
T** allocMemory(int rows, int cols)
{
    T* data = new T[rows*cols];
    T** data_ptr = new T*[rows];

    for (int i=0;i<rows;i++)
    {
        data_ptr[i] = &data[i*cols];
    }

    return data_ptr;
}

template<typename T>
void deallocMemory(T** ptr)
{
    delete[] ptr[0];
    delete[] ptr;
}

void initializeTemp(double** TEMP, double TEMP_MAX, int N)
{
    // Zero out the temperature 
    for (int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            TEMP[i][j] = 0;
        }
    }

    // Initial condition for the right & bottom boundary 
    for (int i=0;i<N;i++)
    {
        double ratio = (double)(i+1)/N;
        TEMP[0][i] = TEMP_MAX*ratio;
        TEMP[i][N-1] = TEMP_MAX*(1-ratio);
    }
}

void solve(double** TEMP,double** TEMP_, int N, double tol, int max_iter)
{
    double dA = 100000;
    int iter = 1;

    while (dA > tol)
    {
        // Perform the update
        for (int i=1;i<N-1;i++)
        {
            for(int j=1;j<N-1;j++)
            { 
                TEMP[i][j] = 0.25*(TEMP_[i-1][j] + TEMP_[i+1][j] + TEMP_[i][j-1] + TEMP_[i][j+1]); 
            }
        }

        // find the max of the error 
        double max_err = 0;
        for (int i=1;i<N-1;i++)
        {
            for (int j=1;j<N-1;j++)
            {
                double err = std::abs(TEMP[i][j] - TEMP_[i][j]);
                if (err > max_err)
                {
                    max_err = err;
                }

                TEMP_[i][j] = TEMP[i][j];
            }
        }

        dA = max_err;
        std::cout << dA << std::endl;
        iter += 1;
    }
    std::cout << "It converged within " << iter << " number of steps." << std::endl;
}