#include <stdio.h>
#include <math.h>

int squareequation (float a, float b, float c, float *x1, float *x2);

int main()
{
    float a,b,c,x1,x2;
    int result;
    scanf ("%f%f%f", &a, &b, &c);

    result = squareequation (a, b, c, &x1, &x2);
    if (result == 3)
    {
        printf ("Any number is the root of the equation.");
    }
    else if (result == 2)
         {
            printf ("The roots of the equation are %lg and %lg.", x1, x2);
         }
         else if (result == 1)
              {
                  printf("The root of the equation is %lg.", x1);
              }
              else if (result == 0)
                   {
                       printf ("There are no roots of the equation over real numbers.");
                   }
                   else
                   {
                       printf ("An error occured. Try again later.");
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
