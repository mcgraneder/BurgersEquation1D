# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>
#define PI (3.141592653589793)

double initial_conditions(double nx, double x, double t);


int main()
{
    //open file for writing the analytical sol
    FILE *AnalyticalFile = NULL;
    AnalyticalFile = fopen("Burgers_Analytical.txt", "w");

    //open file for writing numerical sol
    FILE *NumericalFile = NULL;
    NumericalFile = fopen("Burgers_Numerical.txt", "w");

    //error handle for file

    //declare variables
    double NT = 101.0;
    int NX= 101;
    double TMAX = 0.5;
    double XMAX = 2.0 * PI;
    double NU = 0.1;
    double phi;
    double dphi;

    //declare increments in time and space
    double DT = TMAX / (NT - 1);
    double DX = XMAX / (NX - 1);

    //declare and initilise datastructures
    //and solution arrays
    //analytical solution array
    double** u_analytical = (double **)calloc(NX, sizeof(double *));
    for (int i = 0; i < NT; i++)
    {
        u_analytical[i] = (double *)calloc(NT, sizeof(double));
        //printf("%f", u_analytical[i]);
    }

   double** u_sol = (double **)calloc(NX, sizeof(double *));
    for (int i = 0; i < NT; i++)
    {
        u_sol[i] = (double *)calloc(NT, sizeof(double));
        //printf("%f", u_analytical[i]);
    }


    //memcpy(u_sol, u_analytical, NX * sizeof(double));

    //insert test code of u array

    double* x = (double *)calloc(NX, sizeof(double));
    double* t = (double *)calloc(NT, sizeof(double));
    int* ipos = (double *)calloc(NT, sizeof(double));
    int* ineg = (double *)calloc(NT, sizeof(double));

    //apply periodic boundary conditions
    for (int i = 0; i< NX; i++)
    {
        x[i] = i * DX;
        ipos[i] = i + 1;
        ineg[i] = i - 1;
        //printf("%f\n", ineg[i]);
    }

    ipos[NX - 1] = 0;
    ineg[0] = 1;

    //set first and last entries
    for (int i = 0; i < NX; i++)
    {
        //printf("%f\n", ipos[i]);
    }


    //generate analytical solution


    for (int j = 0; j < NX; j++)
    {
        phi = exp(  (-pow(-x[j], 2.0) / (4.0*NU)))
                 + exp(  (-pow(x[j]-2.0*PI, 2.0)) / (4.0*NU));

        dphi = -(0.5*x[j]/NU) * exp((-pow(x[j],2)) / (4*NU)) -
                (0.5*(x[j]-2*PI) / NU) * exp((-pow(x[j]-2*PI,2)) / (4*NU));


        u_analytical[j][0] = -2*NU*(dphi/phi)+4;
        u_analytical[j][NX-1] = -2*NU*(dphi/phi)+4;

        //printf("%f\n", u_analytical[j][0]);

    }

    //write analytical to file
    for (int i = 0; i < NX ; i++)
    {
        for (int j = 0; j< NX; j++)
        {
            //printf("%f\n", u_analytical[j][0]);
            fprintf(AnalyticalFile, "%f\n", u_analytical[j][0]);
        }
    }

    //Numerical solution
    for (int n = 0; n < NT - 1; n++)
    {
        memcpy(u_sol, u_analytical, NX * sizeof(double*));

        for (int i = 0; i < NX; i++)
        {
            u_sol[i][n+1] = (u_sol[i][n] - u_sol[i][n] * (DT/DX)
                             * (u_sol[i][n] - u_sol[ineg[i]][n]))
                            + NU * (pow(DT/DX, 2)) * (u_sol[ipos[i]][n]
                            - 2 * u_sol[i][n] + u_sol[ineg[i]][n]);
            //printf("%f\n", u_sol[i][n+ 1]);
        }
    }

    //write solution to file
    for (int i = 0; i < NT - 1; i++)
    {
        for (int j = 0; j< NX; j++)
        {
            printf(" %14f\n", u_sol[j][i+1]);
            fprintf(NumericalFile, "%f\n", u_sol[j][i + 1]);
        }
    }


    return EXIT_SUCCESS;
}

/* test code for u_analyticAL ARRAY
    for (int i = 0; i < NX; i++)
    {
        for (int j = 0; j < NT; j++)
        {
            u_analytical[i][j] = 1;
            printf(" %14f,", u_analytical[i][j]);
        }
    }
*/
