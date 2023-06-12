#!/bin/bash
#SBATCH -J CPIM_L128
#SBATCH -n 1
#SBATCH -p slims
#SBATCH --output=output_%j.out
#SBATCH --error=errors_%j.err
#SBATCH --mail-user=ajlhomme@uc.cl
#SBATCH --mail-type=ALL

make
./CPIM-NOGUI "CPIM_FSA_128.txt"