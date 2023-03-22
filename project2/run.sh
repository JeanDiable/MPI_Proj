#用mpi运行文件夹内.o文件，获取命令行参数并设为进程数
###
# @Author: Suizhi HUANG && sunrisen.huang@gmail.com
# @Date: 2023-03-22 15:44:02
 # @LastEditors: Suizhi HUANG && sunrisen.huang@gmail.com
 # @LastEditTime: 2023-03-22 16:27:35
 # @FilePath: /MPI_Proj/project2/run.sh
# @Description: this is the shell script to run the program
# Copyright (c) 2023 by $Suizhi HUANG, All Rights Reserved. 
### 
mpiexec -n $1 ./prime $2