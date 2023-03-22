/*
 * @Author: Suizhi HUANG && sunrisen.huang@gmail.com
 * @Date: 2023-03-22 14:47:25
 * @LastEditors: Suizhi HUANG && sunrisen.huang@gmail.com
 * @LastEditTime: 2023-03-22 15:43:06
 * @FilePath: /MPI_Proj/project2/prime.c
 * @Description: using MPI and The Sieve of Eratosthenes to calculate prime number.
 * Copyright (c) 2023 by $Suizhi HUANG, All Rights Reserved. 
 */

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(id,p,n) (((p)*(id)+1)-1)/(n)
#define MIN(a,b) ((a)<(b)?(a):(b))
int main (int argc, char *argv[])
{
    double start,end;
    int i, j, count, global_count, n, nproc, rank, low, high, size, proc0_size, index, prime, first;
    char *marked;
    MPI_Init (&argc, &argv); 
    MPI_Barrier(MPI_COMM_WORLD); 
    //record starting time
    start = MPI_Wtime(); 
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); 
    MPI_Comm_size (MPI_COMM_WORLD, &nproc);
    //obtain the number of primes to be calculated
    n = atoi(argv[1]);
    //determine the range of numbers to be checked
    low = 2 + BLOCK_LOW(rank,nproc,n-1);
    high = 2 + BLOCK_HIGH(rank,nproc,n-1);
    size = BLOCK_SIZE(rank,nproc,n-1);

    //determine the size of the array
    proc0_size = (n-1)/nproc;
    //check if the number of processes is enough
    if ((2 + proc0_size) < (int) sqrt((double) n)) {
        if (!rank) printf ("Too many processes\n"); 
        MPI_Finalize();
        exit(1);
    }
    //allocate the array
    marked = (char *) malloc (size);
    if (marked == NULL) {
        printf ("Cannot allocate enough memory\n"); 
        MPI_Finalize();
        exit(1);
    }
    //initialize the array
    for (i = 0; i < size; i++) marked[i] = 0; 
    //determine the prime numbers
    if (!rank) index = 0;
    prime = 2;
    do {
        //determine the first multiple of prime
        if (prime * prime > low)
            first = prime * prime - low;
        else if (!(low % prime)) first = 0;
        else first = prime - (low % prime);
        //mark the multiples of prime
        for (i = first; i < size; i += prime) marked[i] = 1; 
        if (!rank) {
            while (marked[++index]);
            prime = index + 2;
        }
        //broadcast the prime number to all processes
        MPI_Bcast (&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } while (prime * prime <= n);
    //count the number of primes
    count = 0;
    for (i = 0; i < size; i++)
        if (!marked[i]) count++;
    //sum the number of primes
    MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD); 
    //record ending time and print the result
    if (!rank) {
        end = MPI_Wtime();
        printf ("%d primes <= %d\n", global_count, n);
        printf ("Total elapsed time: %10.6f\n", end-start); 
    }
    //free the array and finalize MPI
    free (marked);
    MPI_Finalize ();
    return 0; 
}