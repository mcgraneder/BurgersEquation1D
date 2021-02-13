# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>
#include <stdbool.h>


//to do ---make array function inistise all arrays, make a working function for the FTBS method for both linear and non linear
char get_valid_user_input();
double *initialize_array(nx, dx);

//double apply_FTBS(int nt, int nx, int c, double u0_array, double* usol_array);

//This program is the same as the no func version only i have added a choice to run the program
//to solve the 1D linear convection equation or the non linear one

int main ( )
{
    //eqyation to be solved 1D linear advection -- du/dt + c(du/dx) = 0
    //initial conditions u(x,0) = u0(x)

    //after discretisation using forward difference time and backward differemce space
    //update equation becomes u[i] = u0[i] - c * dt/dx * (u0[i] - u[i - 1]);

    //get user input

    FILE *fpointer = NULL;
    fpointer = fopen("a.txt", "w");

    FILE *f1pointer = NULL;
    f1pointer = fopen("ConvectionD1.txt", "w");

    FILE *initial_file = NULL;
    initial_file = fopen("ConvectionInitial.txt", "w");


    char Choose_operation = get_valid_user_input();
    int nx = 41; //num of grid points
    double dx = 2.0 / (nx - 1.0); //magnitude of the spacing between grid points
    double nt = 25;//nt is the number of timesteps
    double sigma = 0.5;
    double dt = sigma * dx; //the amount of time each timestep covers
    int c = 1;  //assume wavespeed

    //double u0_array;


    //initilise arrays
    //double* u0_array = (double*)calloc(nx, sizeof(double));
    double* usol_array = (double*)calloc(nx, sizeof(double));
    double* initial_conditions = (double*)calloc(nx, sizeof(double));
    double* u0_array;


    //set up our initial conditions. The initial velocity u_0
    //is 2 across the interval of 0.5 <x < 1 and u_0 = 1 everywhere else.
    u0_array = initialize_array(nx, dx);

    memcpy(initial_conditions, u0_array, nx * sizeof(double));

    for (int i  = 0; i < nx - 1; i++)
    {
        fprintf(initial_file, "%f\n", initial_conditions[i] );
    }


    //apply numerical scheme forward difference in
    //time an backward difference in space
    //u0_array = usol_array;

    for (int i = 0; i < nt; i++)
    {
        printf("\n");
        memcpy(usol_array, u0_array, nx*sizeof(double));
        printf("timestep %d\n", i);
        printf("\n");

        for (int j = 1; j < nx; j++)
        {
            if (Choose_operation == 'l')
            {
                u0_array[j] = usol_array[j] - c * (dt/dx) * (usol_array[j] - usol_array[j - 1]);
                //print array contents to validate program is working
                printf("%f\n", u0_array[j]);

                //prinysts eac elements array
                //fprintf(fpointer, "%f\n", u0_array[j] );
            }
            else
            {
                u0_array[j] = usol_array[j] - usol_array[j] * (dt/dx) * (usol_array[j] - usol_array[j - 1]);
                printf("%f\n", u0_array[j]);


            }

        }

    }

    printf("The results of the first timestep\n\n");
    //printnts and writes to file the solution of one output
    for (int i = 0; i < nx - 1; i++)
    {
        printf("%f\n", u0_array[i]);
        fprintf(fpointer, "%f\n", u0_array[i]);

    }

    return EXIT_SUCCESS;
}


char get_valid_user_input()
{
    char user_input;
    //prompr user to decide between linear or non liear convection
    printf("Do you want Linear or non-linear convection?. Type(l or n): ");
    scanf("%c", &user_input);
    //get char gets rid of the \n from the press of the enter key important to
    //call this when getting user input.
    getchar();
    tolower(user_input);
    printf("\n");

    //while loop to make sure user input is valid
    while (user_input != 'l' && user_input != 'n')
    {
        printf("Inavlid choice, choose 'l' for linear or 'n' for non linear: " );
        scanf("%c", &user_input);
        tolower(user_input);
        printf("\n");

    }
    return user_input;

}

double *initialize_array(int nx, double dx)
{
    double* u0_array = (double*)calloc(nx, sizeof(double));

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

    return u0_array;
}

void introduction()
{
    printf("This program solves 1D Convection fluid flow equation\n");
    printf("There is two variations of this program, a linear and\n");
    printf("Nonlinear version. Choose which version you would like\n");

}
