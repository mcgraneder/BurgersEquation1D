# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>

//this is the program for linear convection in its simplest form without functions

int main ( )
{
   //Look up the linear convection equation in 1D to see whats being solved

    //here Im just initialising two files to be opened. A file to hold the solution
    //for the initial conditions and a file to hold the solution to the equation itself
    FILE *fpointer = NULL;
    fpointer = fopen("ConvectionD.txt", "w");

    FILE *f1pointer = NULL;
    f1pointer = fopen("ConvectionD1.txt", "w");

    FILE *initial_file = NULL;
    initial_file = fopen("ConvectionInitial.txt", "w");


    //Here im just declaring the variables that we need to solve such as grid points etc
     //num of grid points
    int nx = 41;
    //magnitude of the spacing between grid points
    double dx = 2.0 / (nx - 1.0);
    //nt is the number of timesteps
    double nt = 25;
    //the amount of time each timestep covers
    double dt = 0.025;
    //assume wavespeed of 1. Note that c is just a non dimensional value that is defined by
    //c * dx / dt. For this problem im just defining it as 1 for simplicity
    int c = 1;


    //Here im initialising the arrays that ill need to store the solution. I am defining
    //to solution arrays and one initial condition array. The reason we need to solution
    //arays is that when we update out points in time and space we need to copy the solution
    //from one array into the other as i + 1, we would not be able to do this with just one array
    double* u0_array = (double*)calloc(nx, sizeof(double));
    double* usol_array = (double*)calloc(nx, sizeof(double));
    double* initial_conditions = (double*)calloc(nx, sizeof(double));
    //double *u0_array;

    //bool is_linear;


    //set up our initial conditions. The initial velocity u_0
    //is 2 across the interval of 0.5 <x < 1 and u_0 = 1 everywhere else.
    //this for loop populates the array as such

    for (int i = 0; i < nx-1; i++)
    {
        if (i * dx >= 0.5 && i * dx <= 1)
        {
            u0_array[i] = 2;
        }else
        {
             u0_array[i] = 1;
        }
    }

    //since the above for loop populates the solution array with the initial
    //conditions i am calling memcpy to copy the sol arrays contents to the
    //initial condition array then writing these to the initial condition data file
    memcpy(initial_conditions, u0_array, nx * sizeof(double));

    for (int i  = 0; i < nx - 1; i++)
    {
        fprintf(initial_file, "%f\n", initial_conditions[i] );
    }


    //apply numerical scheme forward difference in
    //time an backward difference in space


    for (int i = 0; i < nt; i++)
    {
        //usol_array[i] = u0_array[i];
        //I use memcpy here to copy the contents of the original array
        //into the temporat solution array after each time step so that
        //the sol array can be updated so that the next inner for loop
        //can do its thing with the update equation.

        //NOTE USING usol_array[i] = u0_aray[i]  will not work due
        //to the way C handles memory. I spent a whole day figuring this out
        memcpy(usol_array, u0_array, nx*sizeof(double));


        //the second loop iterated through space and applys the numerical method
        //forward difference in time backward difference in space
        for (int j = 1; j < nx; j++)
        {
            u0_array[j] = usol_array[j] - c * (dt/dx) * (usol_array[j] - usol_array[j - 1]);

            //print array contents to validate program is working. This
            //line prints the solution for all timesteps
            printf("%f\n", u0_array[j]);
            //prinysts eac elements array
            fprintf(fpointer, "%f\n", u0_array[j] );
        }

    }

    //this for loop prints the solution for the first time step
    for (int i = 0; i < nx; i++)
    {
        printf("%f\n", u0_array[i]);
    }

    return EXIT_SUCCESS;
}


