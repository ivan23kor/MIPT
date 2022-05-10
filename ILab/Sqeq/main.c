#include <stdio.h>
#include <math.h>
#define ANYROOT 3
#define TWOROOTS 2
#define ONEROOT 1
#define NOROOTS 0
#define ERROR -1

int squareequation (char in, float *x1, float *x2);

int main()
{
    float a,b,c,x1,x2;
    string in;
    int result;
    cout << "Input the coefficients of an equation you want to solve.";
    cin >> in;

    result = squareequation (in, &x1, &x2);
    switch (result)
    {
        case  ANYROOT:
        printf ("Any number is the root of the equation.");
        break;
        case TWOROOTS:
        printf ("The roots of the equation are %lg and %lg.", x1, x2);
        break;
        case ONEROOT:
        printf("The root of the equation is %lg.", x1);
        break;
        case NOROOTS:
        printf ("There are no roots of the equation over real numbers.");
        break;
        default:
        printf ("An error occured. Try again later.");
        break;
    }
}


int squareequation (char in, float *x1, float *x2)
{
    float D = 0.0;
    float sqrtofD = 0.0;
    int i;

    if (a == 0.0)
    {
        if (b == 0.0)
        {
            if (c == 0.0)
            {
                return ANYROOT;
            }
            else
            {
                return NOROOTS;
            }
        }
        else
        {
            *x1 = -c/b;
            return ONEROOT;
        }
    }
    else
    {
        D = b*b - 4*a*c;
        if (D < 0)
        {
            return NOROOTS;
        }
        else if (D == 0)
                {
                    *x1 = -b/(2*a);
                    return ONEROOT;
                }
                else
                {

                    sqrtofD = sqrt(D);
                    *x1 = (-b - sqrtofD)/(2*a);
                    *x2 = (-b + sqrtofD)/(2*a);
                    return TWOROOTS;
                }
    }
    return ERROR;
}
