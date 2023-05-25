// LIBS
#include <stdlib.h>
#include "mt64.h"				// Pseudo Random Number Generation 64bit MT Lib	
#include <math.h>				// math to transform random n from continuos to discrete
#include <time.h>				// time library to initialize random generator with time seed
#include <stdio.h>


#define X_SIZE 256
#define Y_SIZE 256
#define REPLICAS 10


// STRUCTURE with the simulation DATA
struct simulation					//Permite combinar datos de diferente tipo
	{
	int lattice_configuration[X_SIZE][Y_SIZE];      // Latice configuration
	int generation_time;				// generations simulated
	double occupancy;	// lattice occupancy
	double up;
	double down;

	/* Model parameters */
	double birth_rate;					/* Contact Process' birth rate parameter */
	double death_rate;				/* Contact Process' death rate parameter */
	int ising_radius;					/* Manhattan distance (in number of sites) of
																			Ising-like interactions */
	double temperature;	   		
	int coupling;
	} s;						// instance s of the structure to hold the simulation
	

// Función que calcula la energía de un punto 
int compute_energy (int random_x_coor, int random_y_coor)
	{	
	int E0, Et;
	int R = 0;
	int G = 0;
	if (s.ising_radius == 1)
    	{
        if      (s.lattice_configuration[random_x_coor][random_y_coor] == 2){E0 = 1;}
    	else if (s.lattice_configuration[random_x_coor][random_y_coor] == 3){E0 =-1;}
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][random_y_coor] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][random_y_coor] == 3){G++;}
    	}
    else if (s.ising_radius == 2)
        {    
        if      (s.lattice_configuration[random_x_coor][random_y_coor] == 2){E0 = 1;}
    	else if (s.lattice_configuration[random_x_coor][random_y_coor] == 3){E0 =-1;}
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][random_y_coor] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][random_y_coor] == 3){G++;}
    	
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+2)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+2)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-2)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-2)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor-2)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor-2)%X_SIZE)][random_y_coor] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor+2)%X_SIZE)][random_y_coor] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor+2)%X_SIZE)][random_y_coor] == 3){G++;}
    	

        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)] == 3){G++;}
    	
        if      (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 2){R++;}
    	else if (s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)] == 3){G++;}
    	}
        
	Et = s.coupling*E0*(R-G);
	return Et;
	}


// Up Date Function which simulates the stochastic process and updates the lattice configuration
void update_lattice(void)
    {
	long random_number; 
	double random_number1, random_number2;
	int random_neighbor_state;
	long random_neighboor;
	int x, y, E1, E2, dE1, dE2;
	double B1, B2;
	int random_x_coor, random_y_coor, random_x_coor2, random_y_coor2;
	double probabily_of_state = 0.1;
	for (int sites = 0; sites < (int)(Y_SIZE*X_SIZE); sites++)
		{
		//pick a random focal site
		random_x_coor = (int) floor(genrand64_real3()*X_SIZE); 
		random_y_coor = (int) floor(genrand64_real3()*Y_SIZE);
		switch(s.lattice_configuration[random_x_coor][random_y_coor])
			{
			case 0: // if the site is empty
				// chose a random neighboor from the 4 posible ones
				random_neighboor = (long) floor(genrand64_real3()*4);
				switch(random_neighboor)
					{
					case 0: // south
							random_neighbor_state = s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor-1)%Y_SIZE)]; 
							break;
					case 1: // north
							random_neighbor_state =	s.lattice_configuration[random_x_coor][(int)((Y_SIZE + random_y_coor+1)%Y_SIZE)]; 
							break;
					case 2: // east
							random_neighbor_state =	s.lattice_configuration[(int)((X_SIZE + random_x_coor-1)%X_SIZE)][random_y_coor];
							break;
					case 3: // west
							random_neighbor_state =	s.lattice_configuration[(int)((X_SIZE + random_x_coor+1)%X_SIZE)][random_y_coor];
							break;
					}
				// if its random neighbor is occupied: put a 1 copy at the focal site. 
				// Note that when all 4 newighboors are occupied colonization of the focal site happens with probability 1.0.
				if (genrand64_real2() < s.birth_rate)
    				{
    				if(random_neighbor_state == 1)
        				{
        				s.lattice_configuration[random_x_coor][random_y_coor]= 1; s.occupancy++;
        				}
        			else if(random_neighbor_state == 2)
        				{
        				s.lattice_configuration[random_x_coor][random_y_coor]= 2; s.occupancy++;
								s.up++;
        				}
        			else if(random_neighbor_state == 3)
        				{
        				s.lattice_configuration[random_x_coor][random_y_coor]= 3; s.occupancy++;
								s.down++;
        				}
                    }
				break; 
			case 1: // if the site is occupied, células adoptan estado +1 o -1 con cierta probabilidad
				// if a particle is present at the focal site, it can die with probability dead_rate* dt
				if (genrand64_real2() < s.death_rate)
    				{
    				s.lattice_configuration[random_x_coor][random_y_coor]= 0; 
						s.occupancy--;
    				}
				else
    				{
    				if (genrand64_real1() < probabily_of_state)
        				{
        				random_number = (long) floor(genrand64_real3()*2);
        				if (random_number == 0)
                			{
            				s.lattice_configuration[random_x_coor][random_y_coor]= 2;
										s.up++;
                        	}
            			else if (random_number == 1)
                			{
            				s.lattice_configuration[random_x_coor][random_y_coor]= 3;
										s.down++;
            				}
        				}
        			}	
    			
				break;
            }
        for (int MC = 0; MC < 100; MC++)
    		{
      		//pick a second random focal site
      		random_x_coor2 = (int) floor(genrand64_real3()*X_SIZE); 
      		random_y_coor2 = (int) floor(genrand64_real3()*Y_SIZE);
      		switch(s.lattice_configuration[random_x_coor2][random_y_coor2])
      			{
      			case 2: // Calcula la energía de un punto
          			if (genrand64_real2() < s.death_rate)
        				{
        				s.lattice_configuration[random_x_coor2][random_y_coor2]= 0; s.occupancy--;
								s.up--;
        				}
    				else
        				{
          				random_number1 = genrand64_real3(); // r must be a random number such that 0 < r < 1
          				E1 = compute_energy (random_x_coor2, random_y_coor2);
          				dE1 = 2*E1;
          				B1 = exp(-dE1/s.temperature);
          				if (dE1 < 0 || random_number1 < B1)
              				{
              				s.lattice_configuration[random_x_coor2][random_y_coor2] = 3;
											s.up--;
											s.down++;
              				}
              			}	
      				break;
      			case 3: //
          			if (genrand64_real2() < s.death_rate)
        				{
        				s.lattice_configuration[random_x_coor2][random_y_coor2]= 0; s.occupancy--;
								s.down--;
        				}
        			else
            			{	
          				random_number2 = genrand64_real3(); // r must be a random number such that 0 < r < 1
          				E2 = compute_energy (random_x_coor2, random_y_coor2);
          				dE2 = 2*E2;
          				B2 = exp(-dE2/s.temperature);
                          if (dE2 < 0 || random_number2 < B2)
              				{
              				s.lattice_configuration[random_x_coor2][random_y_coor2] = 2;
											s.down--;
											s.up++;
              				}
              			}		
      				break;
      			}
      		}
  		}
	s.generation_time ++;
	}


void init_lattice(void)
	{
	/* Start with an empty lattice */
	int x, y;
	for (x = 0; x < X_SIZE; x++)
    	{
    	for (y = 0; y < Y_SIZE; y++) 
        	{
        	s.lattice_configuration[x][y]=0;	//Crea un latice vacío (lleno de 0s)
        	}
        }
	s.occupancy = 0;
	s.up = 0;
	s.down = 0;
	s.lattice_configuration[(int)(X_SIZE/2)][(int)(Y_SIZE/2)]=1;	//Crea una partícula inicial al medio
	s.occupancy++;
	s.generation_time = 0;
	}


/* */
int main (int argc, char **argv)
	{
	s.birth_rate = 1.0;					/* Contact Process' birth rate parameter */
	s.death_rate = 0.0001;				/* Contact Process' death rate parameter */
	s.ising_radius = 1; 						/* Manhattan distance (in number of sites) of
																			Ising-like interactions */
	s.coupling = -1;
	FILE *run;
	run = fopen (argv[1], "w");
	fprintf (run, "N,lattice_size,temperature,generation_time,occupancy,up,down,average_magnetization\n");
	
	for (double temp = 1.0; temp < 3.6; temp += 0.01)
		{
		s.temperature = temp;
		int N = 0;
		for (int N = 0; N < REPLICAS; N++)
			{
			unsigned long long seed = (unsigned int) time (NULL);
			init_genrand64 (seed);
			init_lattice ();
			while (s.occupancy/(X_SIZE * Y_SIZE) < (1-(s.death_rate/s.birth_rate))*0.95)
				{
				update_lattice ();
				}
			for (int t = 0; t < 100; t++)
				{
				fprintf (run, "%d,%d,%f,%d,%f,%f,%f,%f\n", N, X_SIZE, s.temperature, 
								 s.generation_time, (s.occupancy/(X_SIZE*Y_SIZE)),
								 (s.up/(X_SIZE*Y_SIZE)), 
								 (s.down/(X_SIZE*Y_SIZE)),
								 (s.up - s.down)/(s.up + s.down));
				update_lattice ();
				}
			}
		}
	return 0;
  }