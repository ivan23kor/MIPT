#include <iostream>
#include <fstream>
#define N 1000

using namespace std;
int main ()
{
    setlocale (LC_ALL, "Russian");

    double array[N];
    unsigned char amount = 0;
    unsigned char i = 0;
    double negative = 0.0;
    double max = 0.0;
    double min = 0.0;
    double mul = 0.0;
    char max_number = 0;
    char min_number = 0;

    cout << "??????? ???-?? ??-??? ? ???????." << endl;
    cin >> &amount;
    cout << "??????? ??-??." << endl;

    do {
        cin >> array[i];
        i++;
    } while (i < amount - 1);

    for (i = 0; i < amount; i++)
        if (array[i] < 0)
            negative += array[i];

    i = 0;
    while (i < amount)
    {
        if (array[i] < min)
        {
            min = array[i];
            min_number = i;
        }
        else if (array[i] > max)
             {
                max = array[i];
                max_number = i;
             }
        i++;
    }

    if (min_number > max_number)
    {
        char temp = min_number;
        min_number = max_number;
        max_number = temp;
    }

    for (i = min_number + 1; i < max_number; i++)
        mul = mul * array[i];

    for (int j = amount - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (array[i] > array[i + 1])
            {
                double temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }

    cout << "????? ????????????? ????? ??????? ???? %lf: " << negative << endl;
    cout << "???????????? ???? ????? ????? ??????????? ? ???????????? ???? %lf: " << mul << endl;
    cout << "??????????????? ?? ??????????? ??????:" << endl;

    i = 0;
    do {
        cout << "%lf" << array[i] << endl;
        i++;
    } while (i < amount);

    return 0;
}
