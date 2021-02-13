#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define nx 41
#define ny  41
# include <time.h>

double u_a(double x, double t);
double u_b(double x, double t);

int main (int* argv, char**argc)
{

    //initilise boundary conditions
    double a = -1.0;
    double b = +1.0;


    //initilise looping variabbles
    int i;
    int i_upperbound;
    int i_lowerbound;
    int n = 41;

     //num of steps
    int step;
    int step_num = 80;
    //double t;


     //initilise discristati
    //on steps
    double dt;
    double dx = (b - a) / (double) (step_num);


    //initlisise arrays to fill
    double *u_array;
    double *u_new;
    double *x_array;

    //initilisetimestep variables
    double t_initial = 0;
    int t_max = 1;

    //use the time boundarys to define dt
    dx = (b - a) / (double)(n - 1);
    dt = (t_initial - t_max) / (double)(step_num);


    //since we are initilising arrays to fil in runtime we need to use pointers
    //to allocate suuficent memory
    u_array = (double *)malloc(n * sizeof(double));
    u_new = (double *)malloc(n * sizeof(double));
    x_array = (double *)malloc(n * sizeof(double));


    //we need to initilise a few arrays well initlisise x array and populate it
    //with values from -1 to 1 in increments of 0,05
    if (n == 1)
    {
        x_array[0] = 0.5 * (a + b);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            x_array[i] = ((double)(n - i - 1) * a + (double)(i) * b) / (double)(n - 1);
            //printf("%f,", x_array[i]);
        }
    }

    //this code checks for the boundary conditions as we cannot get nfirst and nlast

    for (i_lowerbound = 0; i_lowerbound < n; i_lowerbound = i_lowerbound + 5)
    {
        if ((i_lowerbound + 5) < (n - 1))
        {
            i_upperbound = i_lowerbound + 5;
        }
        else
        {
            i_upperbound = n -1;
        }

        for (int i = i_lowerbound; i <= i_upperbound; i++)
        {
            //printf(" %14f", x_array[i]);
        }
        //printf("\n");

    }


    //we need to apply the boundar conditions to the first and last nodes
    //as hey cannot be calculates using the update equation, for this we need the analytical
    //solution
    step = 0;
    double t = t_initial;

    //we need an array to set the boundary condition at the first node which is zero
    u_new[0] = 0.5;
    u_new[n - 1] = -0.5;


    //this is the analytical solution of burgers, that we need for the first and last
    //node.
    double pi = 3.141592653589793;
    double q;
    double r;
    double s;
    double ua;
    double ub;

    ua = 0.5;
    ub = -0.5;


    q = 2 * (ua - ub) / pi;
    r = (ua + ub) / 2;


    s = 1;

    for (int i = 0; i < n; i++)
    {
        u_array[i] = -q * atan (s * (2.0 * x_array[i] - x_array[0] - x_array[n - 1]) / (x_array[n - 1] - x_array[0])) + r;
        //printf(" %14f", u_array[i]);
    }


    //implement lax wendoff
    for (step = 1; step <= step_num; step++)
    {
        t = ((double)(step_num - step) * t_initial + (double)(step) * t_max) / (double)(step_num);

        for (int i = 0; i < n - 1; i++)
        {
            u_new[i] = u_array[i];
        }
        for (int i = 1; i < n; i++)
        {
            u_new[i] = u_array[i] - (dt / dx) * (pow(u_array[i + 1], 2) - pow(u_array[i], 2)) + 0.5 * (dt * dt / dx / dx) * 0.5 *((u_array[i+1] + u_array[i]) * (pow(u_array[i+ 1], 2) - pow(u_array[i], 2)) - (u_array[i] + u_array[i - 1]) * (pow(u_array[i - 1], 2)));



        }

        u_new[0] = 0.5;
        u_new[n - 1] = -0.5;

    for (int i = 0; i < n; i++)
    {
         printf(" %14f", u_new[i]);
    }
     printf("\n\n");
    }
    free(u_new);
    free(u_array);
    free(x_array);



}

