#include <stdio.h>
#include <TXLib.h>
#include <math.h>

struct TestData
{
double a, b, c;
double x1, x2;
int nRoots;
};


int EquationSolver(double a, double b, double c, double* x1, double* x2, int* nRoots);
void PassedCount();
int OneTest(TestData test);
void AllTests();


void PassedCount()
{
    int passed = 0;
    AllTests();
    printf("Count of correctly passed tests: %d\n", passed);
}


int OneTest(TestData test)
{
    double x1, x2 = 0;

    if (EquationSolver(test.a, test.b, test.c, &x1, &x2, &nRoots) == TwoRoots ||
    EquationSolver(test.a, test.b, test.c, &x1, &x2, &nRoots) == OneRootOfDoubleMultiplicity)
    {
        if (test.x1 == x1 && test.x2 == x2)    //  (if_equal(tests[i].x1, x1) && if_equal(tests[i].x2, x2));
        {
             return 1;
        }
        return 0;
    }


    if (EquationSolver(test.a, test.b, test.c, &x1, &x2, &nRoots) == NoRoots)
    {
        if (isnan(x1) && isnan(x2))
        {
             return 1;
        }
        return 0;
    }


    if (EquationSolver(test.a, test.b, test.c, &x1, &x2, &nRoots) == LinearEquation)
    {
        if (test.x1 == x1 && isnan(x2))   //  if_equal(tests[i].x1, x1);
        {
             return 1;
        }
        return 0;
    }

    return 0;
}


void AllTests()
{
    int passed = 0;

    TestData tests[] = {
    {.a = 1, .b = -5, .c = 6, .x1 = 2, .x2 = 3},
    {.a = 1, .b = 2, .c = 1, .x1 = -1, .x2 = -1},
    {.a = 1, .b = -2, .c = 1, .x1 = 1, .x2 = 1},
    {.a = 1, .b = -11, .c = 30, .x1 = 5, .x2 = 6},
    };


    int size = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < size; i++)
    {
        passed += OneTest(tests[i]);
        if (!OneTest(tests[i]))
        {
            printf("FAILED TEST ¹%d: a: %lf, b: %lf, c: %lf.\n", i, tests[i].a, tests[i].b, tests[i].c);
        }
    }
}

