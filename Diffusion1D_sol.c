# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>


int main ( )
{
    //eqyation to be solved 1D linear advection -- du/dt + c(du/dx) = 0
    //initial conditions u(x,0) = u0(x)

    //after discretisation using forward difference time and backward differemce space
    //update equation becomes u[i] = u0[i] - c * dt/dx * (u0[i] - u[i - 1]);
    FILE *diffusion_file = NULL;
    diffusion_file = fopen("Diffusion1D.txt", "w");
    int nx = 41; //num of grid points
    double sigma = 0.2;
    double dx = 2.0 / (nx - 1.0); //magnitude of the spacing between grid points
    double nt = 20;//nt is the number of timesteps
    double nu = 0.3;
    double dt = sigma * pow(dx, 2); //the amount of time each timestep covers
    int c = 1;  //assume wavespeed
    //double u0_array;

    //initilise arrays
    double* u0_array = (double*)calloc(nx, sizeof(double));
    double* usol_array = (double*)calloc(nx, sizeof(double));


    //set up our initial conditions. The initial velocity u_0
    //is 2 across the interval of 0.5 <x < 1 and u_0 = 1 everywhere else.
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


    //apply numerical scheme forward difference in
    //time an backward difference in space
    //u0_array = usol_array;
    for (int i = 0; i < nt; i++)
    {
        //usol_array[i] = u0_array[i];
        //I use memcpy here to copy the contents of the original array
        //into the temporat solution array so that the next inner for loop
        //can do its thing with the update equation. I have written the script in python
        //and here you can simple call array = array1.copy() to do the same thing python
        //style. But i just dont like using the memcpy, i feel theres a beter way to write
        //this whole loop.
        memcpy(usol_array, u0_array, nx*sizeof(double));


        for (int j = 1; j < nx; j++)
        {
            u0_array[j] = usol_array[j] + nu * (dt/pow(dx, 2)) * (usol_array[j + 1] - 2 * usol_array[j] + usol_array[j - 1]);
            //print array contents to validate program is working
            printf("%f\n", u0_array[j]);

        }

    }

    //print solution for first timestep
    for (int i = 0; i < nx - 1; i++)
    {
        printf("%f\n", u0_array[i]);
        fprintf(diffusion_file, "%f\n", u0_array[i]);
    }

    return EXIT_SUCCESS;
}
