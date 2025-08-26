#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

double DiscriminantSolver(double a, double b, double c, double* discriminant);
int EquationSolver(double a, double b, double c, double* x1, double* x2, int* nRoots);
int if_equal(double num1, double num2);
void Input(double* a, double* b, double* c);

const double EPSILON = 0.000001;


int main()
{
    double a, b, c = NAN;
    double x1, x2 = NAN;
    int nRoots = NAN;

    Input(&a, &b, &c);
    EquationSolver(a, b, c, &x1, &x2, &nRoots);

    if (if_equal(a, 0) && if_equal(b, 0) && !if_equal(c, 0))
    {
        printf("Incorrect identity entered.\n");
        return 0;
    }

    if (if_equal(a, 0) && if_equal(b, 0) && if_equal(c, 0))
    {
        printf("The roots of the equation are any real numbers.\n");
        return 0;
    }

    if (!if_equal(a, 0) && if_equal(b, 0) && if_equal(c, 0))
    {
        printf("The equation has a single root. x = 0\n");
        return 0;
    }

    if (if_equal(nRoots, 1) && isnan(x2))
    {
        printf("The equation is linear. x = %lf\n", x1);
        return 0;
    }

    if isnan(x1)
    {
        printf("The equation has no real roots.\n");
        return 0;
    }

    if (if_equal(x1, x2))
    {
        printf("The equation has one root of double multiplicity. x = %lf\n", x1);
        return 0;
    }

    if (if_equal(nRoots, 2))
    {
        printf("The equation has two different real roots. x1 = %lf, x2 = %lf\n", x1, x2);
        return 0;
    }
}


void Input(double* a, double* b, double* c)
{
    int CoeffCount = 0;

    printf("Square Equation Solver.\nEnter the coefficients of x one by one, separated by a space.\n");
    CoeffCount = scanf("%lf %lf %lf", a, b, c);

    if (!(CoeffCount == 3))
    {
        printf("Apparently you entered the equation coefficients incorrectly. Sorry, the program doesn't work.");
    }
}


enum results
{
    LinearEquation,
    NoRoots,
    OneRootOfDoubleMultiplicity,
    TwoRoots,
    AnotherCase
};


int EquationSolver(double a, double b, double c, double* x1, double* x2, int* nRoots)
{

    assert(x1);
    assert(x2);

    double discriminant = NAN;
    enum results res;


    if (if_equal(a, 0) && !if_equal(b, 0))
    {
        *x1 = -c / b;
        *x2 = NAN;
        *nRoots = 1;
        res = LinearEquation;
        return 0;
    }

    DiscriminantSolver(a, b, c, &discriminant);

    if (discriminant < 0)
    {
        *x1 = NAN;
        *x2 = NAN;
        *nRoots = 0;
        res = NoRoots;
        return 0;
    }

    if (if_equal(discriminant, 0) && !if_equal(a, 0))
    {
        *x1 = *x2 = -b / (2*a);
        *nRoots = 1;
        res = OneRootOfDoubleMultiplicity;
        return 0;
    }

    if (discriminant > 0 && !if_equal(a, 0))
    {
        double sqrt_discriminant = sqrt(discriminant);
        *x1 = (-b + sqrt_discriminant) / (2*a);
        *x2 = (-b - sqrt_discriminant) / (2*a);
        *nRoots = 2;
        res = TwoRoots;
        return 0;
    }

    res = AnotherCase;
    return 0;
}


double DiscriminantSolver(double a, double b, double c, double* discriminant)
{
    *discriminant = ((b * b) - 4 * a * c);
    return 0;
}


int if_equal(double num1, double num2)
{
    return fabs(num1 - num2) < EPSILON;
}
