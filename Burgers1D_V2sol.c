# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>
#define PI (3.141592653589793)

double initial_conditions(double nx, double x, double t);


int main()
{
    double nx = 101;
    double nt = 100;
    double dx = 2.0 * PI / (nx - 1.0);
    double nu = 0.7;
    double t = 0.0;
    double dt = dx * nu;
    double x = 4.0;

    double* u_arr = (double*)malloc(nx * sizeof(double));
    double* x_arr = (double*)malloc(nx * sizeof(double));
    double* un = (double*)malloc(nx * sizeof(double));

    double ics = initial_conditions(nu, x, t);
    printf("%f\n", ics);

    for (int i = 0; i <= 101; i++)
    {
        x_arr[i] = (double)(i) / (22.358
                                   - 2 * PI);
        printf("%f\n", x_arr[i]);
    }

    memcpy(u_arr, x_arr, nx * sizeof(double));

    for (int i = 0; i <= 101; i++)
    {
        u_arr[i] = (double)(initial_conditions(nu, x_arr[i], t));
        printf("%d,   %f\n", i, u_arr[i]);
    }

    return EXIT_SUCCESS;
}


double initial_conditions(double nu, double x, double t)
{
    double u = -2*nu*((-8*t + 2*x) * exp(-pow((-4*t + x), 2) / (4 * nu*(t + 1)))
                / (4*nu*(t + 1)) - (-8*t + 2*x - 4*PI)*exp(-pow((-4*t + x - 2*PI), 2)
                / (4*nu*(t + 1))) / (4*nu*(t+1))) / (exp(-pow((-4*t+x-2*PI),2) /
                (4*nu*(t+1))) + exp(-pow((-4*t+x),2) / (4*nu*t*(t+1)))) + 4;
    return u;

}
