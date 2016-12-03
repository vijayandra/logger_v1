#include<stdio.h>

void main()
{
    int i=100;
    ADC_File("sig.csv");
    while(1)
    {
    ADC_Load_Push(1);
    }
}
