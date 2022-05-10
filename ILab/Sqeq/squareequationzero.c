#include <stdio.h>
#include <math.h>

int squareequation (float a, float b, float c, float *x1, float *x2);

int main()
{
    float a,b,c,x1,x2;
    char decision = '+';
    int result;
    scanf ("%f%f%f", &a, &b, &c);
    while (decision == '+')
    {
        result = squareequation (a, b, c, &x1, &x2);
        if (result == 3)
        {
            printf ("Any number is the root of the equation.\nIf you want to run the program again, input +.");
            scanf ("%c", &decision);
        }
        else if (result == 2)
             {
                printf ("The roots of the equation are %lg and %lg.\nIf you want to run the program again, input +.", x1, x2);
                scanf ("%c", &decision);
             }
             else if (result == 1)
                  {
                      printf("The root of the equation is %lg.\nIf you want to run the program again, input +.", x1);
                      scanf ("%c", &decision);
                  }
                  else if (result == 0)
                       {
                           printf ("There are no roots of the equation over real numbers.\nIf you want to run the program again, input +.");
                           scanf ("%c", &decision);
                       }
                       else
                       {
                           printf ("An error occured. Try again later.\nIf you want to run the program again, input +.");
                           scanf ("%c", &decision);
                       }

    }
}
int squareequation (float a, float b, float c, float *x1, float *x2)
{
    float D = 0;
    float sqrtofD = 0;

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                return 3;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            *x1 = -c/b;
            return 1;
        }
    }
    else
    {
        D = b*b - 4*a*c;
        if (D < 0)
        {
            return 0;
        }
        else if (D == 0)
                {
                    *x1 = -b/(2*a);
                    return 1;
                }
                else
                {

                    sqrtofD = sqrt(D);
                    *x1 = (-b - sqrtofD)/(2*a);
                    *x2 = (-b + sqrtofD)/(2*a);
                    return 2;
                }
    }
    return -3;
}
