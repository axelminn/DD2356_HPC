## Exercise 4 – DFTW, The Fastest DFT in the West

The FFTW is the most famous library to solve a Fourier Transform (FT) using the Fast Fourier Transform algorithm. The FFTW takes its names from the fact that it is the fastest FFT in the West if not in the world. The goal of this exercise is to develop the fastest DFT (Discrete Fourier Transform, a different algorithm to calculate FT) in the west by parallelizing the serial C code that is available here.

Your starting point is a serial code DFTW_1.cPreview the document we have developed to compute a DFT in serial. The code calculates direct and inverse DFTs, timing the total time taken for the computation of the two DFTs. The computational core of the program is the DFT subroutine that takes idft argument as 1 for direct DFT and -1 for inverse DFT.

The code also prints the value of the first element of the DFT computation. This is equal to input size (N). You can use this number to quickly check the correctness of your implementation.

You will  focus on parallelizing the DFT function:

int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N){
    for (int k=0 ; k<N ; k++){
        for (int n=0 ; n<N ; n++{
            // Real part of X[k]
            Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft*xi[n]*sin(n * k * PI2 / N);
            // Imaginary part of X[k]
            Xi_o[k] += -idft*xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
        }
    }
…
# Instructions and Questions: Here the steps you need to follow for the exercise submission:

Note :
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c 

1. Parallelize the DFTW code with OpenMP. You can develop different strategies; the important point is that the code produces the correct results and it is fast!

'''code

	int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N){
		#pragma omp parallel for
	  	for (int k=0 ; k<N ; k++)
	    {
	    	for (int n=0 ; n<N ; n++)  {
	        	// Real part of X[k]
	            Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft*xi[n]*sin(n * k * PI2 / N);
	            // Imaginary part of X[k]
	            Xi_o[k] += -idft*xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
	            
	        } 
	    }
	    
	    // normalize if you are doing IDFT
		#pragma omp critical
	    if (idft==-1){
	    	for (int n=0 ; n<N ; n++){
	    	Xr_o[n] /=N;
	    	Xi_o[n] /=N;
	    }
	    }
	  return 1; 
	}

'''
initial run before:
DFTW calculation with N = 8000 
DFTW computation in 3.954107 seconds
Xre[0] = 8000.000000 

initial run after: (with 4 threads "export OMP_NUM_THREADS=4")
DFTW calculation with N = 8000 
DFTW computation in 1.634363 seconds
Xre[0] = 8000.000000 

2. Measure the performance on Beskow 32 cores reporting the average values and standard deviation for DFTW using an input size equal to 10000 (N=10000).

I'm using my own computer but I ran with N=10000 on 32 threads and got:

DFTW calculation with N = 10000 
DFTW computation in 2.536979 seconds
Xre[0] = 10000.000000 

DFTW calculation with N = 10000 
DFTW computation in 2.534565 seconds
Xre[0] = 10000.000000 

DFTW calculation with N = 10000 
DFTW computation in 2.615169 seconds
Xre[0] = 10000.000000 
 
DFTW calculation with N = 10000 
DFTW computation in 2.540761 seconds
Xre[0] = 10000.000000 

DFTW calculation with N = 10000 
DFTW computation in 2.552958 seconds
Xre[0] = 10000.000000 

[TO-DO] standard deviation and average...

3. Prepare a speed-up plot varying the number of threads: 1, 2, 4, 8, 12, 16, 20, 24, 28 and 32.

Done! all in .txt
[TO-DO] plot

4. Which performance optimizations would be suitable for DFT, other than parallelization with OpenMP? Explain, no need for implementing the optimizations.

[TO-DO] see plot

Example:

output:

DFTW calculation with N = 10000
DFTW computation in 2.107117 seconds
Xre[0] = 8000.000000