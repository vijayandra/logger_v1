#include <stdio.h>
int main(void)
{
    int i;
    for(i=0;i<8;i++)
    {
        LED(i,0);
        printf("LED %d On\n",i);
        ms_sleep(100);

        LED(i,1);
        printf("LED %d Off\n",i);
        ms_sleep(100);
    }



    return 0;
}
