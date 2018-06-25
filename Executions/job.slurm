#!/bin/bash
#SBATCH -n 50
#SBATCH -J cr2D
#SBATCH -o cr2D-%j.out
#SBATCH -e cr2D-%j.err
#SBATCH -t 30:00:00

mkdir -p ./Results

mpiexec.hydra ./Executions/task
