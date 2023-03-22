/*
 * @Author: Suizhi HUANG && sunrisen.huang@gmail.com
 * @Date: 2023-03-21 19:58:12
 * @LastEditors: Suizhi HUANG && sunrisen.huang@gmail.com
 * @LastEditTime: 2023-03-21 20:06:38
 * @FilePath: /project1/hello.c
 * @Description: In this file we use mpi as a tool to print "Hello World" in parallel.
 * Copyright (c) 2023 by $Suizhi HUANG, All Rights Reserved. 
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char *argv[] ) {
    int nproc, rank, namelen;
    //clock_t start_t = clock();
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init (&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();
    MPI_Get_processor_name(processor_name,&namelen);
    printf("Hello World from process %d at processor %s\n", rank,processor_name);
    MPI_Barrier(MPI_COMM_WORLD);
    double end = MPI_Wtime();
    MPI_Finalize();
    if(rank == 0){
        //printf("time = %fs\n",(double)(clock()-start_t)/CLOCKS_PER_SEC);
        printf("time = %fs\n",end-start);
    }
    return 0;
}