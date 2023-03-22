/*
 * @Author: Suizhi HUANG && sunrisen.huang@gmail.com
 * @Date: 2023-03-21 19:58:17
 * @LastEditors: Suizhi HUANG && sunrisen.huang@gmail.com
 * @LastEditTime: 2023-03-22 15:26:46
 * @FilePath: /MPI_Proj/project1/pi.c
 * @Description: Using Monte Carlo method to calculate pi.
 * Copyright (c) 2023 by $Suizhi HUANG, All Rights Reserved. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define N 1000000000
int main(int argc, char *argv[])
{
    int rank, nproc, namelen;
    int i, count = 0;
    double x, y, z, pi;
    //clock_t start_t = clock();
    char pro_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double start = MPI_Wtime();
    MPI_Get_processor_name(pro_name,&namelen);
    srand((unsigned)time(NULL));
    for (i = rank; i < N; i += nproc)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1)
            count++;
    }
    MPI_Reduce(&count, &i, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
    {
        pi = (double)i / N * 4;
        printf("pi=%f\n", pi);
        double end = MPI_Wtime();
        //printf("time=%fs", (double)(clock() - start_t)/CLOCKS_PER_SEC);
        printf("time = %fs\n",end-start);
    }
    MPI_Finalize();
    return 0;
}